/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "./port.h"

//get/set Button aliases
#define Button_SetHigh() do { PORTF_OUTSET = 0x40; } while(0)
#define Button_SetLow() do { PORTF_OUTCLR = 0x40; } while(0)
#define Button_Toggle() do { PORTF_OUTTGL = 0x40; } while(0)
#define Button_GetValue() (VPORTF.IN & (0x1 << 6))
#define Button_SetDigitalInput() do { PORTF_DIRCLR = 0x40; } while(0)
#define Button_SetDigitalOutput() do { PORTF_DIRSET = 0x40; } while(0)
#define Button_SetPullUp() do { PORTF_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define Button_ResetPullUp() do { PORTF_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define Button_SetInverted() do { PORTF_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define Button_ResetInverted() do { PORTF_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define Button_DisableInterruptOnChange() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define Button_EnableInterruptForBothEdges() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define Button_EnableInterruptForRisingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define Button_EnableInterruptForFallingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define Button_DisableDigitalInputBuffer() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define Button_EnableInterruptForLowLevelSensing() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED0 aliases
#define LED0_SetHigh() do { PORTF_OUTSET = 0x20; } while(0)
#define LED0_SetLow() do { PORTF_OUTCLR = 0x20; } while(0)
#define LED0_Toggle() do { PORTF_OUTTGL = 0x20; } while(0)
#define LED0_GetValue() (VPORTF.IN & (0x1 << 5))
#define LED0_SetDigitalInput() do { PORTF_DIRCLR = 0x20; } while(0)
#define LED0_SetDigitalOutput() do { PORTF_DIRSET = 0x20; } while(0)
#define LED0_SetPullUp() do { PORTF_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED0_ResetPullUp() do { PORTF_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED0_SetInverted() do { PORTF_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define LED0_ResetInverted() do { PORTF_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED0_DisableInterruptOnChange() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED0_EnableInterruptForBothEdges() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED0_EnableInterruptForRisingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED0_EnableInterruptForFallingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED0_DisableDigitalInputBuffer() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED0_EnableInterruptForLowLevelSensing() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

void PIN_MANAGER_Initialize();
void PF6_DefaultInterruptHandler(void);
void PF6_SetInterruptHandler(void (* interruptHandler)(void)) ; 
void PF5_DefaultInterruptHandler(void);
void PF5_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
