/* exam.c --- 
 * 
 * Filename: exam.c
 * Description: PWM example
 * Author: bigclean
 * Maintainer: 
 * Created: Sat Nov 21 02:23:26 2009 (-0500)
 * Version: 
 * Last-Updated: Sat Nov 21 02:23:34 2009 (-0500)
 *           By: bigclean
 *     Update #: 1
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */


/*! 
 * \file exam.c
 * \brief PWM example
 * \author Jujie zheng
 * \date 2009-11-16
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

/* exam.c ends here */
