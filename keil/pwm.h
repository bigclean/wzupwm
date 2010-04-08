/**
 @file PWM.h
 @brief PWM head file
 @date 2010-04-09
 */
 
#ifndef __PWM_H_
#define __PWM__H

#include "def.h"
#include <c8051F410.h>
#define SYSCLK       24500000/2 /**< Internal oscillator frequency in Hz */
#define TIMER_PRESCALER      12 /**< Based on Timer2 CKCON and TMR2CN */

#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000 /** the ticks in 1ms for timer clock*/
#define AUX1     TIMER_TICKS_PER_MS
#define AUX2     65536 - AUX1
#define TIMER2_reload_low      (AUX2 & 0x00FF)
#define TIMER2_reload_high     (AUX2 & 0xFF00) >> 8

/** @enum motor_control 
 indicate increase or decrease motor speed based on recived signal
 */
typedef enum
{
    increase = 1,       /**< increase motor speed */
    decrease = 0        /**< decrease motor speed */
} motor_control;

/* function prototype */
/** 
 @fn OSCILLATOR_Init()
 @brief set C8051F410 oscillator frequency 
 @return none
 */
void OSCILLATOR_Init();

/**
 @fn PWM_PORT_Init()
 @brief initialize corelated PWM ports
 @note P0.4 and P0.5 is preserved for UART0 when including uart.h
 @li \c CEX0 P0.6 for PWM to drive motor
 @li \c CEX1 P0.7
 @return none
 */
void PWM_PORT_Init();

/**
 @fn PCA0_Init()
 @brief initialize PCA0
 @li initialize PCA0 module 1 for PWM generation to drive motor
 @li initialize PCA0 module 2 for negative edge capture to measure speed
 @return none
 */
void PCA0_Init();

/**
 * @fn timer0_init
 * @brief  initialize TIME0 and TIME1 used as counter
 * @return none
 */
void timer0_init();

/**
 * @fn timer2_init
 * @brief initialize TIME2
 * @return none 
 */
void timer2_init();

/**
 @fn set_pwm_duty_cycle(uint n)
 @brief  set PCA1 output PWM duty cycle.
 @param n a integer in [1,100],which stands for duty cycle
 @return void
 @note n=50 means the PCA0 pwm duty cycle is 50%, n=40 means the PCA0 output PWM duty cycle is 40%
 */
void set_pwm_duty_cycle(uint n);

/**
 @fn set_motor_speed(uchar n)
 @brief set motor speed
 @param n speed
 @return none
 */
void set_motor_speed(uchar n);

/**
 @fn change_motor_speed(uchar speed, motor_control action, uint step)
 @brief change motor speed based on recived signal
 @param speed motor current speed
 @param action increase or decrease speed
 @param step step of changing motor speed
 */
void change_motor_speed(uchar speed, motor_control action, uint step);

#endif