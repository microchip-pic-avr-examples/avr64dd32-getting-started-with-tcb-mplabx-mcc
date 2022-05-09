<!-- Please do not change this html logo with link -->

<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Timer Counter Type B (TCB) in Three Different Modes Using the AVR64DD32 Microcontroller Generated with MCC Melody

<br>The repository contains three MPLAB® X projects:

1.  [TCB in 8-bit PWM mode](#1-tcb-in-8-bit-pwm-mode) – This code example shows how to configure the TCB peripheral using MCC Melody, to obtain a Pulse-Width Modulation (PWM) signal with a 50% duty cycle and one second period.
2.  [TCB in Sleep Mode](#2-tcb-in-sleep-mode) – This code example configures the TCB peripheral to operate in Sleep mode with an overflow interrupt on every second.
3.  [TCB in Time-out Check Mode](#3-tcb-in-time-out-check-mode) – This code example uses the TCB peripheral in Time-out Check mode, using MCC Melody, and measures the signal time generated by a General Purpose Input/Output (GPIO).

## Related Documentation

More details and code examples on the AVR64DD32 can be found at the following links:

- [AVR64DD32 Product Page](https://www.microchip.com/wwwproducts/en/AVR64DD32)
- [AVR64DD32 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=AVR64DD32)
- [AVR64DD32 Project Examples in START](https://start.atmel.com/#examples/AVR64DD32CuriosityNano)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) v6.00 or newer
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) v2.36 or newer
- [AVR-Dx Series Device Pack](https://packs.download.microchip.com/) v2.1.152 or newer
- [MPLAB® Code Configurator Melody](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody) core 2.1.11 or newer

## Hardware Used

- The AVR64DD32 Curiosity Nano Development board is used as a test platform
  <br><img src="images/AVR64DD32.PNG" width="640">

## Operation

To program the Curiosity Nano board with this MPLAB® X project, follow the steps provided in the [How to Program the Curiosity Nano board](#how-to-program-the-curiosity-nano-board) chapter.<br><br>

## 1. TCB in 8-bit PWM mode

This code example shows how to configure the Timer/Counter Type B (TCB) to output a PWM signal with 50% duty cycle and one second period and how to output it on a pin.

### 1.1 Setup

The following configurations must be made for this project:

- System clock is set to Internal 32.768 kHz Oscillator (Ultra Low-Power)
  - Prescaler is set to 64x.
- TCB0 configuration:
  - Clock Selection: Main clock divided by 2 (CLK_PER/2)
  - Period in CCMP register set to 0x80FF (the PWM signal period is controlled by the CCMPH, while CCMPL controls the duty cycle of the waveform)
  - TCB configured in 8-bit PWM mode
  - TCB output on external pin enabled (PA2)

| Pin | Configuration  |
| :-: | :------------: |
| PA2 | Digital output |

### 1.2 Demo

Connect a Logic Analyzer to pin PA2 on the AVR64DD32 Curiosity Nano board and check the signal:
<br><img src="images/pwm-demo.png" width="1100">

This image shows the PWM signal generated by the TCB0 instance. The waveform period is 1 second and its duty cycle is 50%.

### 1.3 Summary

This code example shows how to configure the TCB peripheral in 8-bit PWM mode to generate a PWM signal with a period of 1 second and 50% duty cycle.<br><br>
[Back to top](#timer-counter-type-b-tcb-in-three-different-modes-using-the-avr64dd32-microcontroller-generated-with-mcc-melody)<br>

## 2. TCB in Sleep Mode

This code example shows how to configure the Timer/Counter Type B (TCB) to operate in Sleep mode. The TCB0 is configured to generate an overflow interrupt every second. The interrupt wakes up the device and toggles the on-board LED (PF5).

### 2.1 Setup

The following configurations must be made for this project:

- System clock is set to Internal 32.768 kHz Oscillator (Ultra Low-Power) and the Prescaler is off.
- TCB0 configuration:
  - Clock Selection: Main clock divided by 1
  - Period in CCMP register set to 0x8000 (1 second period)
  - TCB configured in Periodic Interrupt mode
  - Capture or time-out interrupt enabled
  - Run in Standby enabled

Sleep is enabled and set to Standby mode.

Pin PF5 is configured as output, having the initial state HIGH (for the LED to start off).

| Pin |     Configuration     |
| :-: | :-------------------: |
| PF5 | Digital output (LED0) |

### 2.2 Demo

Connect a Logic Analyzer to pin PF5 on the AVR64DD32 Curiosity Nano board and check the signal:
<br><img src="images/sleep-demo.png" width="1100">

This image shows the LED pin toggling every second. The core exits the Sleep mode, toggles the LED, and enters the Sleep mode once again.

### 2.3 Summary

This code example shows how to configure the TCB peripheral to provide an interrupt every second to wake up the microcontroller from Standby Sleep mode and toggle an LED.<br><br>
[Back to top](#timer-counter-type-b-tcb-in-three-different-modes-using-the-avr64dd32-microcontroller-generated-with-mcc-melody)<br>

## 3. TCB in Time-out Check Mode

This program shows how to configure the Timer/Counter Type B (TCB) in Time-out Check mode and how measure the signal time generated by a GPIO. The time-out will be set to 1 second. If the time-out period is reached, the on-board LED (PF5) will toggle.

### 3.1 Setup

The following configurations must be made for this project:

- System clock is set to Internal 32.768 kHz Oscillator (Ultra Low-Power) and the Prescaler is off.
- TCB0:
  - Clock Selection: Main clock divided by 1
  - Time-out in CCMP register set to 0x8000 (1 second period)
  - TCB configured in Periodic Time-out mode
  - Capture or time-out interrupt enabled
  - Event input for capture is enabled and the Edge bit is set
- Event System
  - Pin PF6 (on-board button on the Curiosity Nano Development board) as event generator on channel 5
  - Event user TCB0 capture set to channel 5

Pin PF5 is configured as output having the initial state HIGH (for the LED to start off) and pin PF6 is configured as input with pull up.

| Pin |     Configuration      |
| :-: | :--------------------: |
| PF5 | Digital output (LED0)  |
| PF6 | Digital input (Button) |

### 3.2 Demo

Connect a Logic Analyzer to pin PF5 and pin PF6 on the AVR64DD32 Curiosity Nano board and check the signal:
<br><img src="images/timeout-demo.png" width="700">

This image shows the input signal on pin PF6 on the first line and the signal on the LED on the second line. Note that the LED signal toggles after the first signal was longer than a second.

### 3.3 Summary

This program shows how to configure the TCB peripheral in Time-out Check mode and measure the signal time generated by a GPIO pin.<br><br>
[Back to top](#timer-counter-type-b-tcb-in-three-different-modes-using-the-avr64dd32-microcontroller-generated-with-mcc-melody)<br>

## How to Program the Curiosity Nano board

This chapter shows how to use the MPLAB® X IDE to program an AVR® device with an Example_Project.X. This can be applied to any other projects.

- Connect the board to the PC

- Open the Example_Project.X project in MPLAB® X IDE

- Set the Example_Project.X project as main project

  - Right click the project in the **Projects** tab and click **Set as Main Project**
    <br><img src="images/Program_Set_as_Main_Project.PNG" width="600">

- Clean and build the Example_Project.X project

  - Right click the **Example_Project.X** project and select **Clean and Build**
    <br><img src="images/Program_Clean_and_Build.PNG" width="600">

- Select **AVRxxxxx Curiosity Nano** in the Connected Hardware Tool section of the project settings:

  - Right click the project and click **Properties**
  - Click the arrow under the Connected Hardware Tool
  - Select **AVRxxxxx Curiosity Nano** (click the **SN**), click **Apply** and then click **OK**:
    <br><img src="images/Program_Tool_Selection.PNG" width="600">

- Program the project to the board
  - Right click the project and click **Make and Program Device**
    <br><img src="images/Program_Make_and_Program_Device.PNG" width="600">

<br>

- [Back to 1. TCB in 8-bit PWM mode](#1-tcb-in-8-bit-pwm-mode)
- [Back to 2. TCB in Sleep Mode](#2-tcb-in-sleep-mode)
- [Back to 3. TCB in Time-out Check Mode](#3-tcb-in-time-out-check-mode)
- [Back to top](#timer-counter-type-b-tcb-in-three-different-modes-using-the-avr64dd32-microcontroller-generated-with-mcc-melody)
