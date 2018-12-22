/**********************************************************************/
/**                       Microsoft Windows NT                       **/
/**                Copyright(c) Microsoft Corp., 1993                **/
/**********************************************************************/

/*
    main.cxx

    This module contains the main startup code for the W3 Service.


    FILE HISTORY:
        KeithMo     07-Mar-1993 Created.
        JohnL   ????
        MuraliK     11-July-1995 Used Ipc() functions from Inetsvcs.dll

*/

#define CHICAGO	1

#include "w3p.hxx"


//
// RPC related includes
//
extern "C" {

#include "inetinfo.h"
#include <timer.h>

# include "w3svci_s.h"

}

//
//  Private constants.
//

//
//  Private globals.
//

DEFINE_TSVC_INFO_INTERFACE();
																		

DECLARE_DEBUG_PRINTS_OBJECT();
DECLARE_DEBUG_VARIABLE();


//
//  Private prototypes.
//

APIERR InitializeService( LPVOID pContext );
APIERR TerminateService( LPVOID pContext );


//
//  Public functions.
//

int WINAPI DllMain( HINSTANCE hDll, DWORD dwReason, LPVOID lpvReserved )
{
    BOOL  fReturn = TRUE;

    switch ( dwReason )
    {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_PROCESS_DETACH:

	break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    default:
        break ;
    }

    return ( fReturn);

}  // main()

/*******************************************************************

    NAME:       ServiceEntry

    SYNOPSIS:   This is the "real" entrypoint for the service.  When
                the Service Controller dispatcher is requested to
                start a service, it creates a thread that will begin
                executing this routine.

    ENTRY:      cArgs - Number of command line arguments to this service.

                pArgs - Pointers to the command line arguments.

                pGlobalData - Points to global data shared amongst all
                    services that live in TCPSVCS.EXE.

    EXIT:       Does not return until service is stopped.

    HISTORY:
        KeithMo     07-Mar-1993 Created.
        KeithMo     07-Jan-1994 Modified for use as a DLL.

********************************************************************/
VOID
ServiceEntry( DWORD                cArgs,
              LPWSTR               pArgs[],
              PTCPSVCS_GLOBAL_DATA pGlobalData )
{
    APIERR err = NO_ERROR;

	//
	// On Windows 95 we use cArgs as an indicator of starting/stopping
	// service. Value of -1 indicates stopping
	//
	if ( (DWORD)-1 != cArgs) {

		CREATE_DEBUG_PRINT_OBJECT( W3_MODULE_NAME);
		SET_DEBUG_FLAGS( 0);

	#if DBG
		if ( err = DBG_OPEN_LOG_FILE( "w3dbg.log", "c:\\" ) )
		{
			TCP_PRINT(( DBG_CONTEXT,
						"Unable to open log file!  Error %d\n",			
						err ));
		}
	#endif


		//
		//  Save the global data pointer.
		//

		pTcpsvcsGlobalData = pGlobalData;

		//
		//  Initialize the service status structure.
		//

		g_pTsvcInfo = new TSVC_INFO( W3_SERVICE_NAME,
									 W3_MODULE_NAME,
									 W3_PARAMETERS_KEY,
									 W3_ANONYMOUS_SECRET_W,
									 W3_ROOT_SECRET_W,
									 INET_HTTP,
									 InitializeService,
									 TerminateService );

		//
		//  If we couldn't allocate memory for the service info struct, then the
		//  machine is really hosed
		//

		if ( !g_pTsvcInfo ||
			 !g_pTsvcInfo->IsValid() )
		{
			delete g_pTsvcInfo;
			return;
		}

		// save the global pointer for rpc thread
		g_pTsvcInfo->SetTcpsvcsGlobalData( pTcpsvcsGlobalData);

		//
		//  This blocks until the service is shutdown
		//

		err = g_pTsvcInfo->StartServiceOperation( SERVICE_CTRL_HANDLER() );

		if ( err )
		{
				//
				//  The event has already been logged
				//

				TCP_PRINT(( DBG_CONTEXT,
						   "HTTP ServiceEntry: StartServiceOperation returned %d\n",
						   err ));
		}

	}
	else {

		// If global object is present - delete it
		if(g_pTsvcInfo) {

			g_pTsvcInfo->ServiceCtrlHandler(SERVICE_CONTROL_SHUTDOWN);
			delete g_pTsvcInfo;
		}

		g_pTsvcInfo = NULL;

		DBG_CLOSE_LOG_FILE();
		DELETE_DEBUG_PRINT_OBJECT();

	}

}   // ServiceEntry

//
//  Private functions.
//


/*******************************************************************

    NAME:       InitializeService

    SYNOPSIS:   Initializes the various W3 Service components.

    EXIT:       If successful, then every component has been
                successfully initialized.									

    RETURNS:    APIERR - NO_ERROR if successful, otherwise a Win32
                    status code.

    HISTORY:
        KeithMo     07-Mar-1993 Created.

********************************************************************/
APIERR InitializeService( LPVOID pContext )
{
    APIERR err;
    LPTSVC_INFO ptsi = (LPTSVC_INFO ) pContext;
    BOOL        fAnySecureFilters = FALSE;


    IF_DEBUG( SERVICE_CTRL )
    {
        TCP_PRINT(( DBG_CONTEXT,
                   "initializing service\n" ));
    }

    //
    //  Initialize various components.  The ordering of the
    //  components is somewhat limited.  Globals should be
    //  initialized first, then the event logger.  After
    //  the event logger is initialized, the other components
    //  may be initialized in any order with one exception.
    //  InitializeSockets must be the last initialization
    //  routine called.  It kicks off the main socket connection
    //  thread.
    //

    InitializeSecondsTimer();

    if( ( err = InitializeGlobals() )             ||
        ( err = CLIENT_CONN::Initialize() )       ||
        ( err = InitializeDirBrowsing() )         ||
        ( err = ReadExtMap() )                    ||
        ( err = HTTP_REQUEST::Initialize() )      ||
        ( ( err = ptsi->InitializeIpc( (UCHAR *) "ncacn_np",
                                     (UCHAR *) W3_NAMED_PIPE,
                                     w3svc_ServerIfHandle))
        != NO_ERROR) ||
      //  ( err = InitializeOleHack())                        ||
        ( err = InitializeFilters(&fAnySecureFilters) )             ||
        ( err = InitializeExtensions() )          ||
        //( err = g_pTsvcInfo->InitializeDiscovery( NULL))    ||
        ( err = InitializeSockets() ))

    {
#if DBG

        TCP_PRINT(( DBG_CONTEXT,
                   "cannot initialize service, error %lu\n",
                    err ));

#endif  // DBG

        return err;
    }

    //
    //  Don't listen on the secure port if there aren't any filters to
    //  handle it
    //

    if ( !fAnySecureFilters )
    {
        SecurePort = 0;
    }

    if ( !g_pTsvcInfo->InitializeConnections( &W3OnConnect,
                                              &W3OnConnectEx,
                                              &W3Completion,
                                              SecurePort,
                                              DEF_ACCEPTEX_RECV_BUFFER_SIZE,
                                              "http" ))
    {
        err = GetLastError();
        g_pTsvcInfo->LogEvent( W3_EVENT_CANNOT_INITIALIZE_WINSOCK,
                               0,
                               (const CHAR **)NULL,
                               err );

        TCP_PRINT(( DBG_CONTEXT,
                   "InitializeConnections failed, error %d\n",
                    err ));

        return err;
    }

    //
    //  Success!
    //

    IF_DEBUG( SERVICE_CTRL )
    {
        TCP_PRINT(( DBG_CONTEXT,
                   "service initialized\n" ));
    }

    return NO_ERROR;

}   // InitializeService

/*******************************************************************

    NAME:       TerminateService

    SYNOPSIS:   Terminates the various W3 Service components.

    EXIT:       If successful, then every component has been
                successfully terminated.

    HISTORY:
        KeithMo     07-Mar-1993 Created.

********************************************************************/
APIERR TerminateService( LPVOID pContext )
{
    LPTSVC_INFO ptsi = (LPTSVC_INFO ) pContext;
    DWORD err;

    IF_DEBUG( SERVICE_CTRL )
    {
        TCP_PRINT(( DBG_CONTEXT,
                   "terminating service\n" ));
    }
						
    //
    //  Components should be terminated in reverse
    //  initialization order.
    //

    g_pTsvcInfo->CleanupConnections();
    TerminateSockets();

    TerminateExtensions();
    TerminateFilters();

    //TerminateOleHack();


//    if ( (err = ptsi->TerminateDiscovery()) != NO_ERROR) {
//        TCP_PRINT(( DBG_CONTEXT, "TerminateDiscovery() failed. Error = %u\n",
//                   err));
//    }

    if ( (err = ptsi->CleanupIpc( w3svc_ServerIfHandle)) != NO_ERROR) {
        TCP_PRINT(( DBG_CONTEXT, "CleanupIpc() failed. Error = %u\n",
                   err));
    }

    CLIENT_CONN::Terminate();

    HTTP_REQUEST::Terminate();
    TerminateExtMap();
    TerminateDirBrowsing();

    TerminateGlobals();

    IF_DEBUG( SERVICE_CTRL )
    {
        TCP_PRINT(( DBG_CONTEXT,
                   "service terminated\n" ));
    }

    return NO_ERROR;

}   // TerminateService


