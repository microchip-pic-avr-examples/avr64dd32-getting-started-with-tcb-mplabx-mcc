/**
 * \file main.c
 *
 * \brief Main source file.
 *
 (c) 2022 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

#define TCB_TIMEOUT_VALUE    32767 /* for a input clock of 32768Hz, this is 1 second timeout */ 

/* Default fuses configuration:
- BOD disabled
- Oscillator in High-Frequency Mode
- UPDI pin active(WARNING: DO NOT CHANGE!)
- RESET pin used as GPIO, Cnano button PF6
- CRC disabled
- MVIO enabled for dual supply
- Watchdog Timer disabled
*/
FUSES =
{
.BODCFG = ACTIVE_DISABLE_gc | LVL_BODLEVEL0_gc | SAMPFREQ_128Hz_gc | SLEEP_DISABLE_gc,
.BOOTSIZE = 0x0,
.CODESIZE = 0x0,
.OSCCFG = CLKSEL_OSC32K_gc,
.SYSCFG0 = CRCSEL_CRC16_gc | CRCSRC_NOCRC_gc | RSTPINCFG_GPIO_gc | UPDIPINCFG_UPDI_gc,
.SYSCFG1 = MVSYSCFG_DUAL_gc | SUT_0MS_gc,
.WDTCFG = PERIOD_OFF_gc | WINDOW_OFF_gc,
};


void CLOCK_init (void);
void PORT_init (void);
void EVENT_SYSTEM_init (void);
void TCB0_init (void);

void CLOCK_init (void)
{
    /* Disable CLK_PER Prescaler */
    ccp_write_io( (void *) &CLKCTRL.MCLKCTRLB , (CLKCTRL_PEN_bp));
    
    /* Select the Internal 32 KHz Oscillator (Ultra Low Power) */
    ccp_write_io((void *) &(CLKCTRL.MCLKCTRLA) , (CLKCTRL_CLKSEL_OSC32K_gc));
   
    /* Wait for system oscillator changing to finish */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
    {
        ;
    }
    /* system clock is 32768 Hz */
}

void PORT_init (void)
{
    /* Configure the LED pin as output. */
    PORTF.DIRSET = PIN5_bm;
    /* Set LED0 off. */
    PORTF.OUTSET = PIN5_bm;
    /* Configure the Button pin as input. */
    PORTF.DIRCLR = PIN6_bm;
    /* Enable the internal pull-up for the Button pin. */
    PORTF.PIN6CTRL |= PORT_PULLUPEN_bm;
}

void EVENT_SYSTEM_init (void)
{
    /* Set Port F Pin 6 (PF6) as input event on channel 5 */
    EVSYS.CHANNEL5 = EVSYS_CHANNEL5_PORTF_PIN6_gc;
    /* Connect user TCB0 Capt to event on channel 5 */ 
    EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL5_gc;
}

void TCB0_init (void)
{
    /* Load the Compare or Capture register with the timeout value*/
    TCB0.CCMP = TCB_TIMEOUT_VALUE;
    
    /* Enable TCB and set CLK_PER divider to 1 (No Prescaling) */
    TCB0.CTRLA = TCB_ENABLE_bm | TCB_CLKSEL_DIV1_gc;
    
    /* Configure TCB in Periodic Timeout mode */
    TCB0.CTRLB = TCB_CNTMODE_TIMEOUT_gc;
    
    /* Enable Capture or Timeout interrupt */
    TCB0.INTCTRL = TCB_CAPT_bm;
    
    /* Enable Event Input and Event Edge*/
    TCB0.EVCTRL = TCB_CAPTEI_bm | TCB_EDGE_bm;
}

ISR(TCB0_INT_vect)
{
    /* Clear the interrupt flag */
    TCB0.INTFLAGS = TCB_CAPT_bm;
    /* Toggle LED */
    PORTF.OUTTGL = PIN5_bm;
}

int main(void)
{
    CLOCK_init();
    PORT_init();
    EVENT_SYSTEM_init();
    TCB0_init();

    /* Enable Global Interrupts */
    sei(); 
    
    while (1)
    {
        ;
    }        
}

