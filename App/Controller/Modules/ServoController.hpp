#ifndef __SERVO_CONTROLLER_H__
#define __SERVO_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "UGV_Packet.hpp"

class ServoController : public IController
{
public:
    ServoController() : m_hadc(nullptr){};
    virtual ~ServoController();
    void update(Data* data, uint8_t mode) override;
    void readServoADC();
    void process();
    void makePacket(Data* data, uint8_t mode);
    void setADC(ADC_HandleTypeDef* m_hadc);

private:
    ADC_HandleTypeDef* m_hadc;
    uint16_t Outer_Servo;
    uint16_t Inner_Servo;
    uint16_t Base_Servo;
    uint8_t Gripper_button;
};

#endif