/**
 @file uart.c
 @brief uart implementation
 @date 2010-04-09
 */

#include "uart.h"

void UART0_Init(void)
{
        /**
         @todo setup SCON0
         @li mode 1, 8 bits UART
         @li enable set RI0 and generate interuppt when 9th bit is 1
         @li disable RX
         @li 9th bit is 0
         @li clear TI0 and RI0 bits
        */
        //SCON0 = 0xC0;

        SCON0 = 0x50; // 8 bit mode,enable receive data
        SCON0 &= 0xFC; // clear TI0 and RI0 bits
        IE |= 0x10; // enable UART0 interrupt
        //IP |= 0x10;   // Make UART high priority
        //ES0 = 1;      // Enable UART0 interrupt
        timer1_init();
}

void UART0_PORT_Init(void)
{
        XBR0 |= 0x01; // route UART on P0.4(TX) and P0.5(RX)
        XBR1 |= 0x40; // enable crossbar
        P0MDOUT |= 0x30; // Enable UTX(P0.4 and P0.5) as push-pull output
}

void timer1_init()
{
        CKCON = 0x08;   // T1 use system clcok
        TMOD &= ~0xf0;
        TMOD |=  0x20; // two steps to set timer 1 in 8-bit autoreload mode
        TR1 = 1;        // START Timer1
}

void set_UART0_baudrate(uchar val)
{
        TH1 = ~val + 1; // equals to (TH1 = 256 - val), but will overflow
        TL1 = TH1;
}