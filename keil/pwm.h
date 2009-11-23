/*! \file PWM.c
 * \brief PWM head file
 * \author Jujie Zheng
 * \date 2009-10-30
 */
 
#ifndef __PWM_H_
#define __PWM__H

#include "def.h"
#include <mcs51/C8051F410.h>

/* Macro definition */
#define SYSCLK       24500000/2	 /*!< Internal oscillator frequency in Hz */
#define TIMER_PRESCALER      12	 /*!< Based on Timer2 CKCON and TMR2CN */
#define CAR_TOGGLE_RATE      1	 /*!< CAR toggle rate in milliseconds */

#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000	/*!< the ticks in 1ms for timer clok(1ms内，相对于定时器2的时钟，所需要的节拍数）*/
#define AUX1     TIMER_TICKS_PER_MS*CAR_TOGGLE_RATE
#define AUX2     65536-AUX1
#define TIMER2_reload_low      (AUX2 & 0x00FF)
#define TIMER2_reload_high     (AUX2 & 0xFF00)>>8

// these are associated to the hardware(mainly is car),will be obsolete
sbit IN1 = P0 ^ 0;
sbit IN2 = P0 ^ 1;
sbit IN3 = P0 ^ 2;
sbit IN4 = P0 ^ 3;

/* function prototype */
/*! 
 * \fn OSCILLATOR_Init()
 * \brief set C8051F410 oscillator frequency 
 * \return none
 */
void OSCILLATOR_Init();

/*!
 * \fn PORT_Init()
 * \brief init C8051F410 ports
 * \return none
 */
void PORT_Init();

/*!
 * \fn PCA0_Init()
 * \brief initiate PCA0 ready for PWM generation
 * \return none
 */

void PCA0_Init();

/*!
 * \fn timer_0_1_init
 * \brief  initite TIME0 and TIME1 used as counter
 * \return none
 */
void timer_0_1_init();

/*!
 * \fn timer2_init
 * \brief initiate TIME2
 * \return none 
 */
void timer2_init();

/*!
 * \fn set_pwm_0_duty_cycle(uint n)
 * \brief  set PCA1 output PWM duty cycle.
 * \param n a integer in [1,100],which stands for duty cycle
 * \return void
 * exam : n=50 mens the PCA0 pwm duty cycle is 50%, n=40 means the PCA0 output PWM duty cycle is 40%
 */
void set_pwm_0_duty_cycle(uint n);

/*! 
 * \fn set_pwm_1_duty_cycle(uint n)
 * \brief set PCA1 output PWM duty cycle.
 * \param n a integer in [1,1000],which stands for duty cycle n/1000;
 * \return void
 * exam n=50 mens the PCA0 pwm duty cycle is 50%, n=40 means the PCA0 output PWM duty cycle is 40%
 */
void set_pwm_1_duty_cycle(uint n);

/*!
 * \fn set_wheel_0_speed(uchar n)
 * \brief set wheel0 speed
 * \param n speed
 * \return none
 */
void set_wheel_0_speed(uchar n);

/*!
 * \fn set_wheel_1_speed(uchar n)
 * \brief set wheel1 speed
 * \param n speed
 * \return none 
 */
void set_wheel_1_speed(uchar n);

#endif
