#ifndef CPN_TM1637_H_
#define CPN_TM1637_H_

#include "../DRV/drv_tm1637.h"

typedef struct CPN_TM1637_HandlerStruct {
    DRV_TM1637_HandlerTypeDef	hDRV_TM1637;				
} CPN_TM1637_HandlerTypeDef;

void CPN_TM1637_Init(CPN_TM1637_HandlerTypeDef *hCPN_TM1637);
void CPN_TM1637_SendData(CPN_TM1637_HandlerTypeDef *hCPN_TM1637, char* cTM1637_Buf);
void CPN_TM1637_TurnOff(CPN_TM1637_HandlerTypeDef *hCPN_TM1637);
void CPN_TM1637_TurnOn(CPN_TM1637_HandlerTypeDef *hCPN_TM1637);

#endif