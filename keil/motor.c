/**
 @file motor.c
 @brief motor control via UART0 communication
 @date 2010-03-22
 */

#include "uart.h"
#include "pwm.h"

extern xdata uchar motor_speed[6];       /**< transimitted speed data to be processed */
xdata uchar motor_control;      /**< store received control signal */
xdata uchar k;   /**< index variable used in transmitting speed data */
enum {
    motor_speed_length = 6
};


/**
 @fn main()
 @brief main motor control routine
 @note 
 @return none
 */
void main()
{
        PCA0MD = 0x00;
        UART0_Init();
        UART0_PORT_Init();
        PWM_PORT_Init();
        OSCILLATOR_Init();
        set_UART0_baudrate(10);    // set UART0 baudrate is 9600
        timer0_init();
        timer2_init();
        EA = 1;
        k = 0;
        SBUF0 = motor_speed[k];  // start to transmit data
        while (1)
        {
                if(k >= motor_speed_length)
                {
                        TR1 = 0;        // disable timer1 and stop transmitting data
                        k = 0; // reset index k
                }
        }
}

/**
 @brief full duplex send and receive data
 */
void UART0_ISR() interrupt 4
{
        // receive data(control signal) interrupt RI0
        if (SCON0 & 0x01)
        {
                motor_control_signal = SBUF0; // store received control signal
                change_motor_speed(motor_speed, motor_control_signal, 5); // default step is constant 5
                TR1 = 1;        // enable timer1 and next turn of transmitting
                SCON0 &= 0xfe;
        }
        // transmit speed data interrupt TI0
        if (SCON0 & 0x02)
        {
                k++;
                SBUF0 = motor_speed[k];
                SCON0 &= 0xfd;
        }
}