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
File    : Main.c
Purpose : Generic SEGGER application start
--------  END-OF-HEADER  ---------------------------------------------
*/

#ifndef USE_SYSVIEW
  #define USE_SYSVIEW 0
#endif

#ifndef USE_RTT
  #define USE_RTT 0
#endif

#ifndef DEBUG
  #define DEBUG 0
#endif

#include "RTOS.h"
#include "BSP.h"
#if USE_SYSVIEW > 0
  #include "SEGGER_SYSVIEW.h"
#endif

#ifndef MAIN_TASK_STACK_SIZE
  #define MAIN_TASK_STACK_SIZE 512 // in words
#endif

/*********************************************************************
*
*       Prototypes
*
**********************************************************************
*/
#ifdef __cplusplus
extern "C" {    /* Make sure we have C-declarations in C++ programs */
#endif
void MainTask(void);
#ifdef __cplusplus
}
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static OS_STACKPTR int Stack0[MAIN_TASK_STACK_SIZE];   /* Task stack */
static OS_TASK         TCB0;                  /* Task-control-block */

/*********************************************************************
*
*       main()
*
* Function description
*   Application entry point
*/
int main(void) {
  OS_IncDI();                      /* Initially disable interrupts  */
  OS_InitKern();                   /* Initialize OS                 */
  OS_InitHW();                     /* Initialize Hardware for OS    */
  BSP_Init();                      /* Initialize BSP module         */
  /* You need to create at least one task before calling OS_Start() */
  OS_CREATETASK(&TCB0, "MainTask", MainTask, 100, Stack0);
  OS_Start();                      /* Start multitasking            */
  return 0;
}

#if 0 // No longer needed???
/*********************************************************************
*
*       USBH_Panic
*
*  Function description
*    Is called if the stack encounters a critical situation.
*    In a release build, this function is not be linked in.
*
*  Parameters
*    s - Pointer to a string holding the error message.
*/

#if USE_RTT == 0 && DEBUG > 0
void USBH_Panic(const char * s);
void USBH_Panic(const char * s) {
  while (s);
}
#endif
#endif

/*********************************************************************
*
*       SEGGER_SYSVIEW_Conf
*
*  Function description
*    Dummy function, if not using SYSVIEW
*/
#if USE_SYSVIEW == 0
unsigned int SEGGER_SYSVIEW_TickCnt;
void SEGGER_SYSVIEW_Conf(void);
void SEGGER_SYSVIEW_Conf(void) {
}
#endif

/****** End Of File *************************************************/
