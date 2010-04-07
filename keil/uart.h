/**
 @file uart.h
 @brief UART0 head file
 @date 2010-03-22
 */
 
#ifndef __UART_H
#define __UART_H

#include "def.h"
#include <c8051F410.h>
#define BAUDRATE 9600 /**< default baudrate for this project */



/*!
 * @fn UART0_Init(void)
 * @note default baudrate is 9600 in this project
 * @brief initial UART0
 */
void UART0_Init(void);

/**
 @fn UART0_PORT_Init(void)
 @brief initialize UART0 ports
 @sa PORT_Init()
 @li \c TX0 P0.4
 @li \c RX0 P0.5
 @brief initialize ports related UART0
 */
void UART0_PORT_Init(void);

/**
 @fn timer1_init(void)
 @brief initial timer1 for UART0
 */
void timer1_init();

/**
 @fn set_UART0_baudrate(uchar val)
 @brief set UART0 baudrate(overflow rate) controlled by timer1
 @todo see datasheet
 @note 
 @li overflow rate is inverse of most counts in one cycle
 @li \f$ baudrate = \frac{overflow rate}{2} \f$
 @li use formula \f[ overflow rate = \frac{T1_{clk}}{256 - TH1} \f]
 @param val set overflow rate as (timer1 clock frequency / val)
 @note when val = 10, then overflow rate is 19200, so baudrate is 9600.
 */
void set_UART0_baudrate(uchar val);

#endif