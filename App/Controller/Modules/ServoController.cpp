#include "ServoController.hpp"
#include "main.h"
#include "stm32f1xx_hal_gpio.h"

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

void ServoController::process()
{
    Gripper_button = HAL_GPIO_ReadPin(Gripper_Button_GPIO_Port, Gripper_Button_Pin);

}

void ServoController::makePacket(Data* data, uint8_t mode)
{
    data->bot_ser = this->Base_Servo;
    data->mid_ser = this->Inner_Servo;
    data->top_ser = this->Outer_Servo;

    data->flags &= 0xFC;
    data->flags |= (mode << 1) | (this->Gripper_button & 0x01) 
}

void ServoController::setADC(ADC_HandleTypeDef* m_hadc)
{
        this->m_hadc = m_hadc;
}