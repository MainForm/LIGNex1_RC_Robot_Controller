#ifndef __UGV_PACKET_H__
#define __UGV_PACKET_H__

#include "main.h"

#pragma pack(push, 1) 

typedef struct Data_Packet 
{
    uint16_t x_data;  // 2048 기준 좌우 (12-bit ADC 원본: 0 ~ 4095)
    uint16_t y_data;  // 2048 기준 앞뒤 (12-bit ADC 원본: 0 ~ 4095)
    uint16_t bot_ser; // 하단(Base) 서보 가변저항 값
    uint16_t mid_ser; // 중단(Inner) 서보 가변저항 값
    uint16_t top_ser; // 상단(Outer) 서보 가변저항 값
    uint8_t  flags;   // 상태 플래그 (모드 정보, 집게 버튼 상태 등)
} Data;

#pragma pack(pop)
#endif