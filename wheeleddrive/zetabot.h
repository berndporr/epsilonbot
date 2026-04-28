/**
 * Copyright (c) 2026 by Bernd Porr
 * Apache License 2.0
 **/

#ifndef ZETABOT_H
#define ZETABOT_H

#include <thread>
#include <sys/time.h>
#include <gpiod.hpp>
#include "rpi_pwm.h"

struct GPIO
{
    GPIO(int GPIOpinNo,
         gpiod::line::direction direction)
    {
        pinNo = GPIOpinNo;
        const int chipNo = 0;
        // const std::string chipPath = std::format("/dev/gpiochip{}", chipNo);
        // const std::string consumername = std::format("gpioconsumer_{}_{}", chipNo, pinNo);
        
        const std::string chipPath = std::string("/dev/gpiochip")+std::to_string(chipNo);
        const std::string consumername = std::string("gpioconsumer_")+std::to_string(chipNo)+std::string("_")+std::to_string(pinNo);


        // Config the pin as input and detecting falling and rising edegs
        gpiod::line_config line_cfg;
        line_cfg.add_line_settings(
            GPIOpinNo,
            gpiod::line_settings().set_direction(direction));
        chip = std::make_shared<gpiod::chip>(chipPath);
        auto builder = chip->prepare_request();
        builder.set_consumer(consumername);
        builder.set_line_config(line_cfg);
        request = std::make_shared<gpiod::line_request>(builder.do_request());
        if (!request)
        {
            std::cerr << consumername << " could not be opened.\n";
            exit(1);
        }
    }

    bool get_value()
    {
        return gpiod::line::value::ACTIVE == (request->get_value(pinNo));
    }

    void set_value(bool v)
    {
        if (v)
        {
            request->set_value(pinNo, gpiod::line::value::ACTIVE);
        }
        else
        {
            request->set_value(pinNo, gpiod::line::value::INACTIVE);
        }
    }

    std::shared_ptr<gpiod::chip> chip;
    std::shared_ptr<gpiod::line_request> request;
    int pinNo;
};

/**
 * Zetabot class to control the lin servos
 */
class ZetaBot
{
public:
    /**
     * Starts the PWM
     **/
    void start();

    /**
     * Shuts down the GPIO/PWM.
     */
    void stop();

    /**
     * Destroys the Alpha Bot object
     */
    ~ZetaBot()
    {
        stop();
    }

    /**
     * Set the Left Wheel Speed
     * @param speed between -1 and +1
     */
    void setLeftWheelSpeed(float speed);

    /**
     * Set the Right Wheel Speed
     * @param speed between -1 and +1
     */
    void setRightWheelSpeed(float speed);

private:
    static constexpr int PWM_CHANNEL_MOTORL = 2;
    static constexpr int PWM_CHANNEL_MOTORR = 3;

    static constexpr float pwmfrequ = 50; // Hz
    static constexpr float motor_rest_pulseduration_ns = 1.5 * 1E6;
    static constexpr float speed2pwm_ns = 0.1 * 1E6; // maps +-1 to +-0.1ms

    int speed2nanosec(float speed) const
    {
        return motor_rest_pulseduration_ns + speed * speed2pwm_ns;
    }

    float leftWheelSpeed = 0;
    float rightWheelSpeed = 0;

    RPI_PWM left_wheel_pwm;
    RPI_PWM right_wheel_pwm;
};

#endif
