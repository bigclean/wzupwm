/**
 @file pwm-sample.c
 @brief PWM sample file
 @date 2010-03-22
 */

#include "pwm.h"
#include "uart.h"

/**
 @fn main()
 @brief just to test PWM module including drive, speed.
 @return none
 */
void main()
{
        //PCA0MD = 0x00;
        UART0_PORT_Init();
        PWM_PORT_Init();
        OSCILLATOR_Init();
        PCA0_Init();
        EA = 1;
        set_pwm_duty_cycle(50);
}
