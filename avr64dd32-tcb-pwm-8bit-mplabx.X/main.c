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
#include <avr/cpufunc.h>


/* F_CPU = 32768/64 = 512 Hz, input clock to TCB0 is 512 / 2 = 256 Hz */
#define TCB_EXAMPLE_PERIOD         255 /* f = 256 Hz / (255 + 1) = 1 Hz */
#define TCB_EXAMPLE_DUTY_CYCLE     (TCB_EXAMPLE_PERIOD+1)/2  /* half of the period is 50% duty cycle */

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
void TCB0_init (void);

void CLOCK_init (void)
{
    /* Enable Prescaler and set Prescaler Division to 64 */
    ccp_write_io((void *) &(CLKCTRL.MCLKCTRLB), (CLKCTRL_PEN_bm |CLKCTRL_PDIV_64X_gc));
    
    /* Select the Internal 32 KHz Oscillator (Ultra Low Power) */
    ccp_write_io((void *) &(CLKCTRL.MCLKCTRLA) , (CLKCTRL_CLKSEL_OSC32K_gc));

    /* Wait for system oscillator changing to finish */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
    {
        ;
    }
    /* System clock is 512 Hz */
}

void PORT_init (void)
{
    /* Configure the PA2 pin as output. */
    PORTA.DIRSET = PIN2_bm;
}

void TCB0_init (void)
{
    /* Enable TCB0 and Divide CLK_PER by 2 */
    TCB0.CTRLA = TCB_ENABLE_bm | TCB_CLKSEL_DIV2_gc;
    
    /* Enable Pin Output and configure TCB in 8-bit PWM mode */
    TCB0.CTRLB = TCB_CCMPEN_bm | TCB_CNTMODE_PWM8_gc;
    
    /* Duty cycle register */
    TCB0.CCMPH = TCB_EXAMPLE_DUTY_CYCLE;
    /* Period Register */
    TCB0.CCMPL = TCB_EXAMPLE_PERIOD;
}

int main(void)
{
    CLOCK_init();
    PORT_init();
    TCB0_init();
    
    while (1)
    {
    }
}