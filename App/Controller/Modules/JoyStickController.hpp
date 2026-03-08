#ifndef __JOYSTICK_CONTROLLER_H__
#define __JOYSTICK_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "UGV_Packet.hpp"

class JoyStickController : public IController
{
public:
    JoyStickController() : m_hadc(nullptr){};
    virtual ~JoyStickController(){};
    void update(Data* data, uint8_t mode) override;
    void readJoyStickADC();
    void syncADC();
    void setADC(ADC_HandleTypeDef* m_hadc);

private:
    void process();
    void makePacket(Data* data, uint8_t mode);

    ADC_HandleTypeDef* m_hadc;

    uint16_t JoyStick_X;
    uint16_t JoyStick_Y;
    uint16_t Prev_Joystick_X;
    uint16_t Prev_Joystick_Y;

    static constexpr float P_RATIO = 0.05f;
    static constexpr uint16_t ThresHold = static_cast<uint16_t>((1 << 12) * P_RATIO);
};

#endif