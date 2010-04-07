/**
 @file uart-sample.c
 @brief UART sample file
 @date 2010-03-22
 */

#include "uart.h"

xdata uchar UART0_data[6] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36};       /**< transimitted UART0 date */
xdata uchar res[6];      /**< address to store received data */
xdata uchar k;   /**< index variable used in transmitting data */
xdata uchar t;   /**< index variable used in receiving data */
enum {
    UART0_data_length = 6
};

/**
 @fn main()
 @brief just to test UART0 module
 @return none
 */
void main()
{
        UART0_Init();
        UART0_PORT_Init();
        OSCILLATOR_Init();
        set_UART0_baudrate(10);    // set UART0 baudrate is 9600
        EA = 1;
        k = 0;
        SBUF0 = UART0_data[k];  // start to transmit data
        while (1)
        {
                if(k >= UART0_data_length)
                {
                        TR1 = 0;        // disable timer1 and stop transmitting data
                }
        }
}

/**
 @brief full duplex send and receive data
 */
void UART0_ISR() interrupt 4
{
        // receive data interrupt RI0
        if (SCON0 & 0x01)
        {
                res[t] = SBUF0; // store received data to res address
                t++;
                SCON0 &= 0xfe;
        }
        // transmit data interrupt TI0
        if (SCON0 & 0x02)
        {
                k++;
                SBUF0 = UART0_data[k];
                SCON0 &= 0xfd;
        }
}