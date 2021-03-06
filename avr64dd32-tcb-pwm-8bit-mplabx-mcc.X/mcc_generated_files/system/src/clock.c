/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
? [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/


#include <xc.h>
#include "../clock.h"

void CLOCK_Initialize(void)
{
    // Set the CLKCTRL module to the options selected in the user interface.
    
    //CLKOUT disabled; CLKSEL Internal 32.768 kHz oscillator; 
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLA),0x1);

    //PDIV 64X; PEN enabled; 
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLB),0xB);

    //EXTS disabled; OSC32KS disabled; OSCHFS disabled; PLLS disabled; SOSC disabled; XOSC32KS disabled; 
    ccp_write_io((void*)&(CLKCTRL.MCLKSTATUS),0x0);

    //RUNSTDBY disabled; 
    ccp_write_io((void*)&(CLKCTRL.OSC32KCTRLA),0x0);

    //AUTOTUNE disabled; RUNSTDBY disabled; 
    ccp_write_io((void*)&(CLKCTRL.OSCHFCTRLA),0xC);

    //TUNE 0x0; 
    ccp_write_io((void*)&(CLKCTRL.OSCHFTUNE),0x0);

    //MULFAC PLL is disabled; RUNSTDBY disabled; SOURCE OSCHF; 
    ccp_write_io((void*)&(CLKCTRL.PLLCTRLA),0x0);

    //CSUT 1k cycles; ENABLE enabled; LPMODE disabled; RUNSTDBY disabled; SEL disabled; 
    ccp_write_io((void*)&(CLKCTRL.XOSC32KCTRLA),0x1);

    //CFDEN disabled; CFDSRC CLKMAIN; CFDTST disabled; 
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLC),0x0);

    //CFD disabled; INTTYPE INT; 
    ccp_write_io((void*)&(CLKCTRL.MCLKINTCTRL),0x0);

    //CFD disabled; 
    ccp_write_io((void*)&(CLKCTRL.MCLKINTFLAGS),0x0);

    //CSUTHF 256; ENABLE disabled; FRQRANGE 8M; RUNSTBY disabled; SELHF XTAL; 
    ccp_write_io((void*)&(CLKCTRL.XOSCHFCTRLA),0x0);

}

void CFD_Enable(CLKCTRL_CFDSRC_t cfd_source)
{
    /* Enable Clock Failure Detection on main clock */
    ccp_write_io((uint8_t *) & CLKCTRL.MCLKCTRLC, cfd_source | CLKCTRL_CFDEN_bm);
}

void CFD_Disable()
{
    /* Disable Clock Failure Detection on main clock */
    ccp_write_io((uint8_t *) & CLKCTRL.MCLKCTRLC, CLKCTRL.MCLKCTRLC & ~CLKCTRL_CFDEN_bm);
}


/**
 End of File
*/