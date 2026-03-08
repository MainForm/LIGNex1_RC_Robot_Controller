#ifndef __JOYSTICK_CONTROLLER_H__
#define __JOYSTICK_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "UGV_Packet.hpp"

class JoyStickController : public IController
{
public:
    JoyStickController() : m_hadc(nullptr){};
    virtual ~JoyStickController();
    void update(Data* data, uint8_t mode) override;
    void readJoyStickADC();
    void process();
    void makePacket(Data* data, uint8_t mode);
    void setADC(ADC_HandleTypeDef* m_hadc);

private:
    ADC_HandleTypeDef* m_hadc;
    uint16_t JoyStick_X;
    uint16_t JoyStick_Y;
};

#endif