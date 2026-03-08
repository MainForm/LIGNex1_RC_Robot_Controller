#include "ServoController.hpp"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <cmath>
void ServoController::update(Data* data, uint8_t mode)
{
    readServoADC();
    process();
    makePacket(data, mode);
}

void ServoController::readServoADC()
{
    HAL_ADC_Start(m_hadc);
    for(int idx = 1; idx <=5; idx++){
        if(HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK){
            uint16_t val = HAL_ADC_GetValue(m_hadc);

            if(idx == 1) this->Outer_Servo = val;
            else if(idx == 2) this->Inner_Servo = val;
            else if(idx == 3) this->Base_Servo = val;
        }
    }
    HAL_ADC_Stop(m_hadc);
}
// 변화량 감지
// 버킷 버튼 감지
void ServoController::process()
{
    uint32_t Current_Time = HAL_GetTick();
    uint8_t temp_Current_Val = HAL_GPIO_ReadPin(Gripper_Button_GPIO_Port, Gripper_Button_Pin);
    
    // 한 번 누르면 계속 1이 유지 되는 것이 아니라 1 번만 1이 저장이 됨. 
    // 50ms 미만일 때 무시(이전 누른 시간 vs 현재 누른 시간)

    if(temp_Current_Val != Last_Gripper_button){
        if(Current_Time - Last_Time > DEBOUNCE_INTERVAL){
            Last_Time = Current_Time;
            Last_Gripper_button = temp_Current_Val;
    
            if(temp_Current_Val == 1){
                this->Gripper_button ^= 1;
            }
        }
    }
    
    uint16_t diff_base = abs((int32_t)this->Prev_Base_Servo - (int32_t)this->Base_Servo);
    uint16_t diff_outer = abs((int32_t)this->Prev_Outer_Servo - (int32_t)this->Outer_Servo);
    uint16_t diff_inner = abs((int32_t)this->Prev_Inner_Servo - (int32_t)this->Inner_Servo);

    if(diff_base > ThresHold)
    {
        this->Prev_Base_Servo = this->Base_Servo;
    }

    if(diff_outer > ThresHold)
    {
        this->Prev_Outer_Servo = this->Outer_Servo;
    }

    if(diff_inner > ThresHold)
    {
        this->Prev_Inner_Servo = this->Inner_Servo;
    }
}

void ServoController::makePacket(Data* data, uint8_t mode)
{
    data->bot_ser = this->Prev_Base_Servo;
    data->mid_ser = this->Prev_Inner_Servo;
    data->top_ser = this->Prev_Outer_Servo;

    data->flags &= 0xFC;
    data->flags |= (mode << 1) | (this->Gripper_button & 0x01);
}

void ServoController::setADC(ADC_HandleTypeDef* m_hadc)
{
    this->m_hadc = m_hadc;
}

void ServoController::syncADC()
{
    this->Prev_Base_Servo = Base_Servo;
    this->Prev_Inner_Servo = Inner_Servo;
    this->Prev_Outer_Servo = Outer_Servo; 
}