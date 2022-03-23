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
-------------------------- END-OF-HEADER -----------------------------

File    : SEGGER_snprintf_IP.c
Purpose : Formatter hook for SEGGER_snprintf() handling the following
          formatter extensions:
            - h: Hardware address
            - i: IPv4 address
            - n: IPv6 address
Revision: $Rev: 6174 $
*/

#include "SEGGER.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static SEGGER_PRINTF_FORMATTER _Formatter_h;
static SEGGER_PRINTF_FORMATTER _Formatter_i;
static SEGGER_PRINTF_FORMATTER _Formatter_n;

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _PrintHWAddr()
*
*  Function description
*    Stores a HW addr. (MAC addr.) into the string buffer.
*
*  Parameters
*    pBufferDesc: Output buffer descriptor.
*    pContext   : Management context. Can be NULL.
*    pApi       : Pointer to a SEGGER_PRINTF_API structure.
*    pParamList : Pointer to a variable arguments list to take the value from.
*    Flags      : Flags Byte, see SEGGER_PRINTF_FLAG_* definitions.
*    Width      : Overall width of the resulting string.
*    Precision  : Number of digits after decimal point of the value to store.
*/
static void _PrintHWAddr(SEGGER_BUFFER_DESC* pBufferDesc, SEGGER_SNPRINTF_CONTEXT* pContext, const SEGGER_PRINTF_API* pApi, va_list* pParamList, char Flags, int Width, int Precision) {
  U8* p;
  int i;

  SEGGER_USE_PARA(Width);
  SEGGER_USE_PARA(Precision);

  p = va_arg(*pParamList, U8*);
  i = 0;
  do {
    pApi->pfPrintUnsigned(pBufferDesc, pContext, *p++, 16, Flags, -1, 2);
    if (++i == 6) {
      break;
    }
    pApi->pfStoreChar(pBufferDesc, pContext, ':');
  } while (1);
}

/*********************************************************************
*
*       _PrintIPv4Addr()
*
*  Function description
*    Stores an IPv4 addr. into the string buffer.
*
*  Parameters
*    pBufferDesc: Output buffer descriptor.
*    pContext   : Management context. Can be NULL.
*    pApi       : Pointer to a SEGGER_PRINTF_API structure.
*    pParamList : Pointer to a variable arguments list to take the value from.
*    Flags      : Flags Byte, see SEGGER_PRINTF_FLAG_* definitions.
*    Width      : Overall width of the resulting string.
*    Precision  : Number of digits after decimal point of the value to store.
*/
static void _PrintIPv4Addr(SEGGER_BUFFER_DESC* pBufferDesc, SEGGER_SNPRINTF_CONTEXT* pContext, const SEGGER_PRINTF_API* pApi, va_list* pParamList, char Flags, int Width, int Precision) {
  U32 IPAddr;
  U8* p;
  int i;

  SEGGER_USE_PARA(Width);
  SEGGER_USE_PARA(Precision);

  IPAddr = va_arg(*pParamList, U32);  // The IP addr. is always given in network endianess.
  p = (U8*)&IPAddr;
  i = 0;
  do {
    pApi->pfPrintInt(pBufferDesc, pContext, *p++, 10, Flags, -1, 0);
    if (++i == 4) {
      break;
    }
    pApi->pfStoreChar(pBufferDesc, pContext, '.');
  } while (1);
}

/*********************************************************************
*
*       _PrintIPv6Addr()
*
*  Function description
*    Stores an IPv6 addr. into the string buffer.
*
*  Parameters
*    pBufferDesc: Output buffer descriptor.
*    pContext   : Management context. Can be NULL.
*    pApi       : Pointer to a SEGGER_PRINTF_API structure.
*    pParamList : Pointer to a variable arguments list to take the value from.
*    Flags      : Flags Byte, see SEGGER_PRINTF_FLAG_* definitions.
*    Width      : Overall width of the resulting string.
*    Precision  : Number of digits after decimal point of the value to store.
*/
static void _PrintIPv6Addr(SEGGER_BUFFER_DESC* pBufferDesc, SEGGER_SNPRINTF_CONTEXT* pContext, const SEGGER_PRINTF_API* pApi, va_list* pParamList, char Flags, int Width, int Precision) {
  U8* p;
  int i;

  SEGGER_USE_PARA(Width);
  SEGGER_USE_PARA(Precision);

  p = va_arg(*pParamList, U8*);
  i = 0;
  do {
    pApi->pfPrintUnsigned(pBufferDesc, pContext, *p++, 16, Flags, -1, 2);
    pApi->pfPrintUnsigned(pBufferDesc, pContext, *p++, 16, Flags, -1, 2);
    if (++i == 8) {
      break;
    }
    pApi->pfStoreChar(pBufferDesc, pContext, ':');
  } while (1);
}

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       SEGGER_PRINTF_AddIPFormatter()
*
*  Function description
*    Adds formatters h, i and n for IP usage to the SEGGER_snprintf()
*    formatter.
*/
void SEGGER_PRINTF_AddIPFormatter(void) {
  SEGGER_PRINTF_AddFormatter(&_Formatter_h, &_PrintHWAddr  , 'h');
  SEGGER_PRINTF_AddFormatter(&_Formatter_i, &_PrintIPv4Addr, 'i');
  SEGGER_PRINTF_AddFormatter(&_Formatter_n, &_PrintIPv6Addr, 'n');
}

/*************************** End of file ****************************/
