#include "JoyStickController.hpp"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_def.h"

void JoyStickController::update(Data* data, uint8_t mode)
{
    
    readJoyStickADC();
    process();
    makePacket(data, mode);
}

void JoyStickController::readJoyStickADC()
{
    HAL_ADC_Start(m_hadc);
    for(int idx = 1; idx <=5; idx++){
        if(HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK){
            uint16_t val = HAL_ADC_GetValue(m_hadc);

            if(idx == 4) this->JoyStick_X = val;
            else if(idx == 5) this->JoyStick_Y = val;
        }
    }
    HAL_ADC_Stop(m_hadc);
}

void JoyStickController::process()
{

}

void JoyStickController::makePacket(Data* data, uint8_t mode)
{
    data->x_data = this->JoyStick_X;
    data->y_data = this->JoyStick_Y;

    data->flags &= ~(1<<1);
    data->flags |= mode << 1;}

void JoyStickController::setADC(ADC_HandleTypeDef* m_hadc)
{
    this->m_hadc = m_hadc;
}