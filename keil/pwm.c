/**
 @file PWM.c
 @brief PWM implementation 
 @date 2010-04-09
 */

#include "pwm.h"
// global variables
//uint motor_speed;          /**< motor speed */
uint pwm_duty_cycle;      /**< PCA0 output PWM module 0 duty cycle */
uint T2_count;             /**< variable to count interrupt times */
extern xdata uchar motor_speed[6];       /**< transimitted speed data to be processed */
extern xdata uchar transmit_index;   /**< index variable used in transmitting speed data */
void OSCILLATOR_Init()
{
        //OSCICN = 0x86;          // Set internal oscillator to run at maximum frequency/2;
        /**
         @note
         @li C8051F410 use internal oscillator as system clock defaultly
         @li configure system clock is maximum frequency/8
         */
        OSCICN = 0x84;
}

void PWM_PORT_Init()
{
        XBR1 |= 0x51;            // enable crrossbar, T0, CEX0
        P0SKIP = 0x0F;          // route CEX0 to P0.6, T0 to P0.7
        P0MDOUT |= 0x40;        // Set CEX0 (P0.6) to push-pull
        //P0 = 0xC0;
}

void PCA0_Init()
{
        PCA0CN = 0x00;          // stop PCA0 and clear all flags
        PCA0MD = 0x08;          // Use SYSCLK as time base

        // set PCA0 module 0 output PWM mode is 16-bit PWM, enable.
        PCA0CPM0 = 0x82;
        // initialize module 0 output PWM duty cycle is 50%
        PCA0CPL0 = 0x00;
        PCA0CPH0 = 0x80;

        // enable PCA0 timering
        CR = 1; // euqals to PCA0CN |= 0x40;
}

void timer0_init()
{
        TMOD = 0x05; // timer 0 run as 16 bit mode counter and as extern counter;
        TH0 = 0x00;
        TL0 = 0x00;
        // enable timer 0 interrupt
        ET0 = 1;
        // TCON = 0x55; // starts to countering,Timer0 ON with INT0 edge active
        // enable timer0
        TCON = 0x10;
}

void timer2_init()
{
        CKCON &= ~0x20;

        TMR2RLL = TIMER2_reload_low;
        TMR2L = TMR2RLL;
        TMR2RLH = TIMER2_reload_high;
        TMR2H = TMR2RLH;
        TMR2CN = 0x04; // timer2 run as 16-bit reload mode,enable timer2,timer2 use sysclk/12;
        ET2 = 1;
}

void set_pwm_duty_cycle(uint n)
{
        uint CEX0_Compare_Value = 65536 - (n * 655.36);
        PCA0CPL0 = (CEX0_Compare_Value & 0x00FF);       // get low 8 bits
        PCA0CPH0 = (CEX0_Compare_Value & 0xFF00) >> 8;  // get high 8 bits
}

void set_motor_speed(uchar n)
{
        while (1)
        {
                if (motor_speed < n)  // if speed is slow
                {
                        pwm_duty_cycle++;
                }
                else
                {
                        pwm_duty_cycle--;
                }
                set_pwm_duty_cycle(pwm_duty_cycle);
                if (motor_speed == n)
                        break;
        }
}

void change_motor_speed(uchar speed, motor_control action, uint step)
{
        if (action == increase)
        {
                set_motor_speed(speed + step);
        }
        if (action == decrease)
        {
                set_motor_speed(speed - step);
        }
}

/**
 * @fn timer2_ISR()
 * @brief timer2 interrupt service routine
 * @return void
 */
void timer2_ISR() interrupt 5
{
        //uint x;
        ET2 = 0; // disable timer2
        T2_count++;
        //x = 10 + T2_count;
        if (T2_count == 1000) // 1 s has been counted
        {
                // timer 0 counts to accumulate interrupt times to indicate the rounds
                motor_speed[transmit_index++] = TH0 * 256 + TL0; // motor rounds in one second
                TL0 = 0;
                TH0 = 0;
        }
        TF2H = 0;// clear bufferflow flag
        ET2 = 1;// enable timer2
}