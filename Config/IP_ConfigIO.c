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
File        : IP_ConfigIO.c
Purpose     : I/O Configuration routines for TCP/IP
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include "IP.h"
#ifdef USB_HOST
  #include "USBH.h"
#else
  #include "USB.h"
#endif
#if USE_RTT > 0
  #include "SEGGER_RTT.h"
#endif


/*********************************************************************
*
*       Defines, configurable
*
*       This section is normally the only section which requires changes.
*       on most embedded systems
*
**********************************************************************
*/


/*********************************************************************
*
*       IP_Panic
*
*  Function description
*    This function is called if the stack encounters a critical situation.
*    In a release build, this function may not be linked in.
*
*/
void IP_Panic(const char *s) {
  (void)s;
#ifdef USB_HOST
  USBH_PANIC(s);
#else
  USB_PANIC(s);
#endif
}

/*********************************************************************
*
*       IP_Log
*
*  Function description
*    This function is called by the stack in debug builds with log output.
*    In a release build, this function may not be linked in.
*
*  Notes
*    (1)  Interrupts and task switches
*         printf() has a re-entrance problem on a lot of systems if interrupts are not disabled.
*                  which would scramble strings if printf() called from an ISR interrupts an other printf.
*         In order to avoid this problem, interrupts are disabled.
*
*/
void IP_Log(const char *s) {
#if USE_RTT > 0
  SEGGER_RTT_WriteString(0, s);
  SEGGER_RTT_WriteString(0, "\n");
#else
  USB_USE_PARA(s);
#endif
}

/*********************************************************************
*
*       IP_Warn
*
*  Function description
*    This function is called by the stack in debug builds with log output.
*    In a release build, this function may not be linked in.
*
*  Notes
*    (1)  Interrupts and task switches
*         See IP_Log()
*/
void IP_Warn(const char *s) {
#if USE_RTT > 0
  SEGGER_RTT_WriteString(0, s);
  SEGGER_RTT_WriteString(0, "\n");
#else
  USB_USE_PARA(s);
#endif
}

/*************************** End of file ****************************/
