/* pwm.h --- 
 * 
 * Filename: pwm.h
 * Description: pwm header file
 * Author: bigclean
 * Maintainer: 
 * Created: Sat Nov 21 02:22:30 2009 (-0500)
 * Version: 
 * Last-Updated: Mon Feb  8 21:19:10 2010 (-0500)
 *           By: bigclean
 *     Update #: 18
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
 * 8-Feb-2010    bigclean  
 *    Last-Updated: Mon Feb  8 21:10:03 2010 (-0500) #10 (bigclean)
 *    use SDCC macro to enable compiler differences between Keil
 * 6-Feb-2010    bigclean  
 *    Last-Updated: Sat Feb  6 15:02:56 2010 (-0500) #5 (bigclean)
 *    change doxygen syntax from QT to standard JavaDoc
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


/**
 * @file pwm.c
 * @brief PWM head file
 * @author Jujie Zheng
 * @date 2010-2-8
 */
 
#ifndef __PWM_H_
#define __PWM__H

#include "def.h"
/*!< To be tested in Linux */
#include <mcs51/C8051F410.h>

/* Macro definition */
#define SDCC 1                   /*!< using SDCC compiler macro */
#define KEIL 0                   /*!< using KEIL compiler macro */

#define SYSCLK       24500000/2	 /*!< Internal oscillator frequency in Hz */
#define TIMER_PRESCALER      12	 /*!< Based on Timer2 CKCON and TMR2CN */
#define CAR_TOGGLE_RATE      1	 /*!< CAR toggle rate in milliseconds */

#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000	/*!< the ticks in 1ms for timer clok*/
#define AUX1     TIMER_TICKS_PER_MS*CAR_TOGGLE_RATE
#define AUX2     65536-AUX1
#define TIMER2_reload_low      (AUX2 & 0x00FF)
#define TIMER2_reload_high     (AUX2 & 0xFF00)>>8

// these are associated to the hardware(mainly is car),will be obsolete

// SDCC compiler use different bit defintions 
#if SDCC
__sbit __at (0x80) IN1;      /*!< Port P0 ^ 0 */
__sbit __at (0x81) IN2;      /*!< Port P0 ^ 1 */
__sbit __at (0x82) IN3;      /*!< Port P0 ^ 2 */
__sbit __at (0x83) IN4;      /*!< Port P0 ^ 3 */
#endif

// defaulty,KEIL macro is disabled
#if KEIL
/*
sbit IN1 = P0 ^ 0;
sbit IN2 = P0 ^ 1;
sbit IN3 = P0 ^ 2;
sbit IN4 = P0 ^ 3;
*/
#endif

// function prototype

/** 
 * @fn OSCILLATOR_Init()
 * @brief set C8051F410 oscillator frequency 
 * @return none
 */
void OSCILLATOR_Init();

/**
 * @fn PORT_Init()
 * @brief init C8051F410 ports
 * @return none
 */
void PORT_Init();

/**
 * @fn PCA0_Init()
 * @brief initiate PCA0 ready for PWM generation
 * @return none
 */

void PCA0_Init();

/**
 * @fn timer_0_1_init
 * @brief  initiate TIME0 and TIME1 used as counter
 * @return none
 */
void timer_0_1_init();

/**
 * @fn timer2_init
 * @brief initiate TIME2
 * @return none 
 */
void timer2_init();

/**
 * @fn set_pwm_0_duty_cycle(uint n)
 * @brief  set PCA1 output PWM duty cycle.
 * @param n a integer in [1,100],which stands for duty cycle
 * @return void
 * exam : n=50 mens the PCA0 pwm duty cycle is 50%, n=40 means the PCA0 output PWM duty cycle is 40%
 */
void set_pwm_0_duty_cycle(uint n);

/** 
 * @fn set_pwm_1_duty_cycle(uint n)
 * @brief set PCA1 output PWM duty cycle.
 * @param n a integer in [1,1000],which stands for duty cycle n/1000;
 * @return void
 * exam n=50 mens the PCA0 pwm duty cycle is 50%, n=40 means the PCA0 output PWM duty cycle is 40%
 */
void set_pwm_1_duty_cycle(uint n);

/**
 * @fn set_wheel_0_speed(uchar n)
 * @brief set wheel0 speed
 * @param n speed
 * @return none
 */
void set_wheel_0_speed(uchar n);

/**
 * @fn set_wheel_1_speed(uchar n)
 * @brief set wheel1 speed
 * @param n speed
 * @return none 
 */
void set_wheel_1_speed(uchar n);

#endif

/* pwm.h ends here */
