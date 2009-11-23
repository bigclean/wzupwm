/*! \file exam.c
 * \brief PWM example
 * \author Jujie zheng
 * \date 2009-10-30
 */

#include "pwm.h"

/*!
 * \fn main()
 * \brief just to test PWM module
 * \return none
 */
int main()
{
	PCA0MD = 0x00;
	PORT_Init();
	OSCILLATOR_Init();
	PCA0_Init();
	timer_0_1_init();
	timer2_init();
	IN1 = 0;
	IN2 = 1;
	IN3 = 0;
	IN4 = 1;
	EA = 1;
	//set_pwm_0_duty_cycle(20);
	//set_pwm_1_duty_cycle(16);
	while (1)
	{
		//set_pwm_0_duty_cycle(700);
		//set_pwm_1_duty_cycle(660);
		set_wheel_1_speed(50);
		set_wheel_0_speed(50);
	}
}
