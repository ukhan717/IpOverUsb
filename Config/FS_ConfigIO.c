/*********************************************************************
*                   (c) SEGGER Microcontroller GmbH                  *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2003 - 2019     SEGGER Microcontroller GmbH              *
*                                                                    *
*       www.segger.com     Support: support_emusb@segger.com         *
*                                                                    *
**********************************************************************
*                                                                    *
*       emUSB-Device * USB Device stack for embedded applications    *
*                                                                    *
*                                                                    *
*       Please note:                                                 *
*                                                                    *
*       Knowledge of this file may under no circumstances            *
*       be used to write a similar product.                          *
*                                                                    *
*       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       emUSB-Device version: V3.19-r15500                           *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : FS_ConfigIO.c
Purpose     : I/O configuration routines for file system
---------------------------END-OF-HEADER------------------------------
*/

//#include "USB.h"
#include "FS.h"


/*********************************************************************
*
*       FS_X_Panic
*
*  Function description
*    Referred in debug builds of the file system only and
*    called only in case of fatal, unrecoverable errors.
*/
void FS_X_Panic(int ErrorCode) {
  while (ErrorCode) {
  }
}

/*********************************************************************
*
*      Logging: OS dependent
*
*/
void FS_X_Log(const char * s) {
  (void)s;
  //USB_LOG((USB_MTYPE_CORE, "%s", s));
}

void FS_X_Warn(const char * s) {
  (void)s;
  //USB_WARN((USB_MTYPE_CORE, "FS warning: %s", s));
}

void FS_X_ErrorOut(const char * s) {
  (void)s;
  //USB_WARN((USB_MTYPE_CORE, "FS error: %s", s));
}

/*************************** End of file ****************************/
