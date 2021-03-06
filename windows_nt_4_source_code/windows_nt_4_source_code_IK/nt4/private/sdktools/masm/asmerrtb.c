/* asmerrtb.c -- microsoft 80x86 assembler
**
** microsoft (r) macro assembler
** copyright (c) microsoft corp 1986.  all rights reserved
**
** randy nevin
**
** 10/90 - Quick conversion to 32 bit by Jeff Spencer
*/

#include <stdio.h>
#include "asm86.h"
#include "asmfcn.h"
#include "asmmsg.h"

/*  error message table - on 8086 it is in a far segment  */

char FAR *messages[E_MAX] = { NULL, };
short FAR msgnum[] = { /* this table must be in the same order as the
        error codes in asm86.h */
        0,
        ER_BNE,
        ER_ECL,
        ER_RAD,
        ER_UST,
        ER_RSY,
        ER_SMD,
        ER_PHE,
        ER_ELS,
        ER_NCB,
        ER_SND,
        ER_SYN,
        ER_TIL,
        ER_NGR,
        ER_PS1,
        ER_TUL,
        ER_SDK,
        ER_RES,
        ER_IFR,
        ER_MBR,
        ER_WRT,
        ER_MSG,
        0,
        ER_MSY,
        ER_ALD,
        ER_SPC,
        ER_NPA,
        ER_RMD,
        ER_OPN,
        ER_OPR,
        ER_DV0,
        ER_SCN,
        ER_OMM,
        ER_IUE,
        0,
        ER_RRF,
        ER_OHS,
        ER_NOP,
        0,
        ER_LOS,
        ER_OOC,
        ER_OSA,
        0,
        ER_CXP,
        ER_OSG,
        ER_ASD,
        ER_ASC,
        ER_DBR,
        ER_DIR,
        ER_IBR,
        ER_IUR,
        ER_VOR,
        ER_NIP,
        ER_IOT,
        ER_JOR,
        0,
        ER_IRV,
        ER_NIM,
        ER_IIS,
        ER_BRI,
        ER_CSI,
        ER_AXL,
        ER_ISR,
        ER_NCS,
        ER_OCI,
        ER_JCD,
        ER_NSO,
        ER_OAP,
        ER_OES,
        ER_CRS,
        ER_MSB,
        ER_NEB,
        ER_FOF,
        ER_IDV,
        ER_SAE,
        ER_DTL,
        ER_UID,
        ER_MVD,
        ER_OIL,
        ER_DIS,
        ER_ODI,
        ER_FCO,
        0,
        0,
        ER_CEA,
        ER_7OE,
        ER_EOF,
        ER_ENS,
        ER_EP1,
        ER_EP2,
        ER_ERR,
        ER_ERE,
        ER_ERZ,
        ER_END,
        ER_ESD,
        ER_EBL,
        ER_ENB,
        ER_EID,
        ER_EDF,
        ER_OWL,
        ER_LTL,
        ER_IMP,
        ER_MDZ,
        ER_286,
        ER_AP2,
        ER_JSH,
        ER_EXP,
        ER_LNL,
        ER_NDN,
        ER_EMS,
        ER_MOP,
        ER_PAR,
        ER_NMC,
        ER_UEL,
        ER_CPU,
        ER_ONW,
        ER_ANW,
        ER_INC,
        ER_FPO1,
        ER_FPO2
        };

