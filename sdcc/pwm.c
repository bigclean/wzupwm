/* pwm.c --- 
 * 
 * Filename: pwm.c
 * Description:pwm implementation file 
 * Author: bigclean
 * Maintainer: 
 * Created: Sat Nov 21 02:16:46 2009 (-0500)
 * Version: 
 * Last-Updated: Sat Feb  6 15:01:47 2010 (-0500)
 *           By: bigclean
 *     Update #: 3
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
 * 6-Feb-2010    bigclean  
 *    Last-Updated: Sat Feb  6 14:56:08 2010 (-0500) #2 (bigclean)
 *    1. change doxygen syntax from QT to standard JavaDoc
 *    2. some comments update
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


/** 
 * @file pwm.c
 * @brief PWM implementation 
 * @author Jujie Zheng
 * @date 2010-2-6
 */

#include "pwm.h"
// global variables
// wheel 0 and 1 speed
uint_t wheel_0_speed;          /*!< wheel 0 speed */
uint_t wheel_1_speed;          /*!< wheel 1 speed */
// PCA0 output PWM 0 and 1  duty cycle
uint_t pwm_0_duty_cycle;      /*!< PCA0 output PWM pipe 0 duty cycle */
uint_t pwm_1_duty_cycle;      /*!< PCA0 output PWM pipe 1 duty cycle */
// timer 0 and timer 1 counts to accumulate interrupt times to indicate the rounds
uint_t T2_count;             /*!< variable to count interrupt times */

void OSCILLATOR_Init()
{
	OSCICN = 0x86;		// Set internal oscillator to run at maximum frequency/2;
}

void PORT_Init()
{
	XBR1 = 0x72;		// enable crrossbar ,T0,T1 and CEX0 ,CEX1
	P0SKIP = 0x0F;		// route CEX0 to P0.4,T0 to P0.6

	P0MDOUT |= 0x00;	// Set CEX0 (P0.0) to push-pull
	P0 = 0xC0;
}

void PCA0_Init()
{
	PCA0CN = 0x00;		// Stop counter; clear all flags
	PCA0MD = 0x08;		// Use SYSCLK as time base

	// set PCA0 module 0 and 1 output PWM mode is 16-bit PWM,enable.
	PCA0CPM0 = 0x82;
	PCA0CPM1 = 0x82;

	// initial module 0 and 1 output PWM duty cycle both is  50%
	PCA0CPL0 = 0x7F;
	PCA0CPH1 = 0xFF;
	PCA0CPL1 = 0x7F;
	PCA0CPH1 = 0xFF;
	// enable PCA0 timering
	CR = 1;
}

void timer_0_1_init()
{
	TMOD = 0x55;		// timer 0 and 1 run as 8 bit reload  mode counter;
	TH0 = 0x00;
	TL0 = 0x00;
	TH1 = 0x00;
	TL1 = 0x00;
	// enable timer 0 and timer 1 interrupt
	ET0 = 1;
	ET1 = 1;
	// TCON = 0x55; // starts to countering,Timer0 ON with INT0 edge active
	TCON = 0x50;
}

void timer2_init()
{
	CKCON &= ~0x20;

	TMR2RLL = TIMER2_reload_low;
	TMR2L = TMR2RLL;
	TMR2RLH = TIMER2_reload_high;
	TMR2H = TMR2RLH;
	TMR2CN = 0x04;		// timer2 run as 16-bit reload mode,enable timer2,timer2 use sysclk/12;
	ET2 = 1;
}

void set_pwm_0_duty_cycle(uint_t n)
{
	uint_t CEX0_Compare_Value;
	CEX0_Compare_Value = 65536 - (n * 65.536);

	PCA0CPL0 = (CEX0_Compare_Value & 0x00FF);	// get low 8 bits
	PCA0CPH0 = (CEX0_Compare_Value & 0xFF00) >> 8;	// get high 8 bits
}

void set_pwm_1_duty_cycle(uint_t n)
{
	uint_t CEX1_Compare_Value;
	CEX1_Compare_Value = 65536 - (n * 65.536);

	PCA0CPL1 = (CEX1_Compare_Value & 0x00FF);	// get low 8 bits
	PCA0CPH1 = (CEX1_Compare_Value & 0xFF00) >> 8;	// get high 8 bits
}

void set_wheel_0_speed(uchar_t n)
{
	while (1)
	{
		if (wheel_0_speed < n)  // if speed is slow
		{
			if ((n - wheel_0_speed) > 50) 
			{
				pwm_0_duty_cycle += 10;  // long setp 
			} else
			{
				pwm_0_duty_cycle++;  // small step
			}
		} else
		{
			if ((wheel_0_speed - n) > 50)
			{
				pwm_0_duty_cycle -= 50;
			} else
			{
				pwm_0_duty_cycle--;
			}
		}
		set_pwm_0_duty_cycle(pwm_0_duty_cycle);
		if (wheel_0_speed == n)
			break;
	}
}

void set_wheel_1_speed(uchar_t n)
{
	while (1)
	{
		if (wheel_1_speed < n)
		{
			if ((n - wheel_1_speed) > 50)
			{
				pwm_1_duty_cycle += 10;
			} else
			{
				pwm_1_duty_cycle++;
			}
		} else
		{
			if ((wheel_1_speed - n) > 50)
			{
				pwm_1_duty_cycle -= 50;
			} else
			{
				pwm_1_duty_cycle--;
			}
		}
		set_pwm_1_duty_cycle(pwm_1_duty_cycle);
		if (wheel_1_speed == n)
			break;
	}
}

/**
 * @fn timer2_ISR()
 * @brief timer2 interrupt service routine
 * @return void
 */
void timer2_ISR() interrupt 5
{
	uint_t x;
	ET2 = 0;		// disable timer2
	T2_count++;
	x = 10 + T2_count;
	if (T2_count == 1000)	// 1 s has been counted
	{
		wheel_0_speed = TH0 * 256 + TL0;	// wheel 0 rounds in one second
		wheel_1_speed = TH1 * 256 + TL1;	// wheel 1 rounds in one second
		TL0 = 0;
		TH0 = 0;
		TL1 = 0;
		TH1 = 0;
	}
	TF2H = 0;		// clear  bufferflow flag
	ET2 = 1;		// enable timer2
}

/* pwm.c ends here */
