# Arduino-For-Keil STM32F0xx
> https://github.com/FASTSHIFT/Arduino-For-Keil

# Update Log
## [v1.0] - 2018.7.29
* 1.Transplanted all ArduinoAPI7 based on STM32F0xx standard peripheral library (version 1.0.1)

## [v1.1] - 2018.8.14
* 1.Organize USART related codes
* 2.Modify the Tone library to only occupy one timer (you can use the toneSetTimer() function to switch)
* 3.time_exti.c renamed to timer.c

## [v1.2] - 2018.8.17
* 1.Added a more complete function for interacting with GPIO registers in Arduino.h
* 2.Improve compatibility with third-party libraries

## [v1.3] - 2018.8.20
* 1.Add WCharacter.h to support Arduino functions related to Characters
* 2.Add mcu_type.h so that Arduino.h can be used across MCUs

## [v1.4] - 2018.10.9
* 1.Add notes
* 2.Update Tone, HardwareSerial
* 3.Remove usart.c usart.h

## [v1.5] - 2018.11.21
* 1.Update Arduino.c

## [v1.6] - 2019.2.18
* 1.Tidy code
* 2.Better compatibility

## [v1.7] - 2019.3.22
* 1.Set the highest interrupt priority for SysTick to prevent being interrupted by other interrupts (very important!)

## [v1.8] - 2019.6.3
* 1.The pwm.c library changes the frequency setting value from 16 bits to 32 bits, and adds the parameter legal range judgment
* 2.ARDUINO macro definition from Arduino.h to global macro definition

## [v1.9] - 2019.6.18
* 1.PA4 can supply PWM output

## [v2.0] - 2019.7.12
* 1.Add yield() and digitalPinToInterrupt(Pin) definitions in Arduino.h
* 2.Change the legal parameter judgment method of analogRead_DMA()

## [v2.1] - 2019.10.3
* 1.Synchronization _Keilduino(STM32F10x) V_7.0 part code
* 2.Remove ADC DMA temporarily
* 3.Map STM32F030F4P6 serial port 1 to PA9 and PA10
* 4.Add TIM6 timing interrupt

## [v2.2] - 2019.11.4
* 1.Update the Print library (transplant Georges Menie's printf-stdarg.c), printf no longer has a length limit
* 2.Add sprintf member

## [v2.3] - 2019.12.25
* 1.The SPI library can be used normally, add the option to use the internal clock
* 2.Synchronization _Keilduino(STM32F10x) V_7.5 part code

## [v2.4] - 2020.1.15
* 1.Since the printf of the Print library does not support floating-point output, restore the Print library and use vsnprintf to convert printf

## [v2.5] - 2020.4.14
* 1.The update log is changed to use Markdown syntax to write
* 2.Remove duplicate dtostrf.c, dtostrf.h
* 3.Add Libraries path
* 4.Arduino.h adds macros for clock cycle and time conversion
* 5.Add WMath.h and Tone.h to Arduino.h
* 6.Add README file group
* 7.Add yield() function entity
* 8.GPIO fast operation macro definition, function moved from mcu_type.h to gpio.h and Arduino.h
* 9.__STM32__ macro definition moved from Arduino.h to mcu_type.h
* 10.In Delay.c, adc.c files remove #include "Arduino.h"
* 11.Add timer channel definition for PA5

## [v2.6] - 2020.4.16
* 1.Remove FileGroup.h
* 2.Libraries only keep the Servo library

## [v2.7] - 2020.4.24
* 1.The bug that the adc library can only read one channel has been resolved
* 2.ADC_DMA mode is supported

## [v2.8] - 2020.11.4
* 1.Fix external interrupt line setting missing by exti library
