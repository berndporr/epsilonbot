#include "zetabot.h"
#include <math.h>
#include <iostream>
#include <unistd.h>

void ZetaBot::start()
{
    left_wheel_pwm.start(PWM_CHANNEL_MOTORL, pwmfrequ);
    right_wheel_pwm.start(PWM_CHANNEL_MOTORR, pwmfrequ);
}

void ZetaBot::stop()
{
    if ((leftWheelSpeed > 0) || (rightWheelSpeed > 0))
    {
        for (int i = 0; i < 10; i++)
        {
            setLeftWheelSpeed(leftWheelSpeed / 1.5);
            setRightWheelSpeed(rightWheelSpeed / 1.5);
            usleep(100000);
        }
        setLeftWheelSpeed(0);
        setRightWheelSpeed(0);
    }
}

void ZetaBot::setRightWheelSpeed(float speed)
{
    speed = -speed;
    if (speed < -1)
        speed = -1;
    if (speed > 1)
        speed = 1;
    rightWheelSpeed = speed;
    right_wheel_pwm.setDutyCycleNanosecs(speed2nanosec(speed));
}

void ZetaBot::setLeftWheelSpeed(float speed)
{
    if (speed < -1)
        speed = -1;
    if (speed > 1)
        speed = 1;
    leftWheelSpeed = speed;
    left_wheel_pwm.setDutyCycleNanosecs(speed2nanosec(speed));
}
