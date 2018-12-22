;/*************************************************************************
; *                        Microsoft Windows NT                           *
; *                                                                       *
; *                  Copyright(c) Microsoft Corp., 1994                   *
; *                                                                       *
; * Revision History:                                                     *
; *                                                                       *
; *   Jan. 30,94    Koti     Created                                      *
; *                                                                       *
; * Description:                                                          *
; *                                                                       *
; *   This file (lpdmsg.h) is generated by the MC tool from the file      *
; *   lpdmsg.mc                                                           *
; *                                                                       *
; *************************************************************************/
;
;
;

;#define  LPD_SERVICE_NAME   "LPDSVC"
;#define  LPD_SPOOL_PREFIX "LPDSPL"
;#define  LPD_SERVICE_USRFRIENDLY_NAME "TCP/IP Print Server"
;#define  LPD_PARMS_REGISTRY_PATH  "System\\CurrentControlSet\\Services\\LPDSVC\\PARAMETERS"
;#define  LPD_PARMNAME_MAXUSERS    "MaxConcurrentUsers"
;#define  LPD_PARMNAME_JOBREMOVAL  "AllowJobRemoval"
;#define  LPD_PARMNAME_PRINTRESUME "AllowPrinterResume"
;#define  LPD_PARMNAME_ALWAYSRAW   "SimulatePassThrough"
;
;#define  LPD_PARMNAME_PRINTER_PASS_THROUGH "LpdPrinterPassThrough"
;#define  LPD_PARMNAME_DONT_DETECT          "LpdPrinterDontDetect"
;
;#define  STRING_POSTSCRIPT_HEADER          "%!PS"
;#define  STRING_LENGTH_POSTSCRIPT_HEADER   4
;
;#define  LPD_RAW_STRING           "RAW"
;#define  LPD_TEXT_STRING          "TEXT"
;
;#define  LPD_NEWLINE         "\n"
;
;

SeverityNames=(Success=0x0
               Informational=0x1
               Warning=0x2
               Error=0x3
              )

Messageid=4000 Severity=Informational SymbolicName=LPDLOG_LPD_STARTED
Language=English
LPD service started successfully.
.

Messageid=+1 Severity=Informational SymbolicName=LPDLOG_LPD_STOPPED
Language=English
LPD service stopped successfully.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_LPD_DIDNT_START
Language=English
LPD service failed to start.  The data is the error.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_OUT_OF_RESOURCES
Language=English
A request from client was refused because system is out of resources.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_MISBEHAVED_CLIENT
Language=English
Improper sequence of commands received from %1 : service refused.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_UNSUPPORTED_PRINT
Language=English
Request for unsupported print format received from %1 : job may not print correctly.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_UNAUTHORIZED_REQUEST
Language=English
%1 on %2 requested to remove job submitted by %3 on %4: service refused.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_BAD_FORMAT
Language=English
Illegal format used for commands received from %1 : service refused.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_NONEXISTENT_PRINTER
Language=English
Printer %1 specified in the request from %2 does not exist: request ignored.
.

Messageid=+1 Severity=Informational SymbolicName=LPDLOG_PRINTER_RESUMED
Language=English
As per request from %1, printer %2 resumed.
.

Messageid=+1 Severity=Warning SymbolicName=LPDLOG_DIDNT_WORK
Language=English
Request from %1 could not be satisfied: possibly due to network problems
.

Messageid=+1 Severity=Informational SymbolicName=LPD_LOGO
Language=English

                         Windows NT LPD Server
.

Messageid=+1 Severity=Informational SymbolicName=LPD_PRINTER_TITLE
Language=English
                              Printer%b%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_QUEUE_HEADER
Language=English


Owner       Status         Jobname          Job-Id    Size   Pages  Priority
.

Messageid=+1 Severity=Informational SymbolicName=LPD_QUEUE_HEADER2
Language=English
----------------------------------------------------------------------------%0
.
Messageid=+1 Severity=Informational SymbolicName=LPD_SERVER_TITLE
Language=English
   Server:%b%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_QUEUE_NOPRINTER
Language=English
Error: specified printer does not exist
.

Messageid=+1 Severity=Informational SymbolicName=LPD_QUEUE_ERRMSG
Language=English
Error: could not report status
.

Messageid=+1 Severity=Informational SymbolicName=LPD_PRINTER_PAUSED
Language=English
 (Paused)%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_PRINTER_PENDING_DEL
Language=English
 (Pending Deletion)%0
.

;
;   // sizeof(szIPAddr) is 16: this errmsg shouldn't exceed 15 chars!
Messageid=+1 Severity=Informational SymbolicName=LPD_ERMSG_NO_IPADDR
Language=English
????%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_PAUSED
Language=English
Paused%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_ERROR
Language=English
Error%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_DELETING
Language=English
Deleting%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_SPOOLING
Language=English
Spooling%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_PRINTING
Language=English
Printing%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_OFFLINE
Language=English
Offline%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_PAPEROUT
Language=English
Paperout%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_PRINTED
Language=English
Printed%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_STR_PENDING
Language=English
Waiting%0
.

Messageid=+1 Severity=Informational SymbolicName=LPD_DEFAULT_DOC_NAME
Language=English
LPR client document%0
.



