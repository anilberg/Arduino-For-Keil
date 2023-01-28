/*
 * MIT License
 * Copyright (c) 2019 _VIFEXTech
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Arduino.h"

/**
  * @brief  Configure pin input/output mode
  * @param  Pin: Pin number
  * @param  GPIO_Mode_x: Pin mode
  * @retval Null
  */
void pinMode(uint8_t Pin, pinMode_TypeDef pinMode_x)
{
    if(!IS_PIN(Pin))
        return;
    
    if(pinMode_x == PWM)
    {
        PWM_Init(Pin, 1000, 2000);
    }
    else if(pinMode_x == INPUT_ANALOG_DMA)
    {
        if(!IS_ADC_PIN(Pin))
            return;
        
        pinMode(Pin, INPUT_ANALOG);
        ADC_DMA_Register(PIN_MAP[Pin].ADC_Channel);
    }
    else
    {
        GPIOx_Init(
            PIN_MAP[Pin].GPIOx,
            PIN_MAP[Pin].GPIO_Pin_x,
            pinMode_x,
            GPIO_Speed_50MHz
        );
    }
}

/**
  * @brief  Write a digital HIGH(1) or LOW(0) value to a digital pin
  * @param  Pin: Pin number
  * @param  val: Pin output Logic High/Low
  * @retval Null
  */
void digitalWrite(uint8_t Pin, uint8_t val)
{
    if(!IS_PIN(Pin))
        return;
    
    val ? digitalWrite_HIGH(Pin) : digitalWrite_LOW(Pin);
}

/**
  * @brief  Read pin level
  * @param  Pin: Pin number
  * @retval Pin level
  */
uint8_t digitalRead(uint8_t Pin)
{
    if(!IS_PIN(Pin))
        return 0;
    
    return digitalRead_FAST(Pin);
}

/**
  * @brief  Write an analog value (PWM duty cycle) to the pin
  * @param  Pin: Pin number
  * @param  val: PWM duty cycle
  * @retval PWM duty cycle
  */
uint16_t analogWrite(uint8_t Pin, uint16_t val)
{
    return (IS_PWM_PIN(Pin) ? pwmWrite(Pin, val) : 0);
}

/**
  * @brief  Read the value from the specified analog pin
  * @param  Pin: Pin number
  * @retval ADC value 0 to 4095
  */
uint16_t analogRead(uint8_t Pin)
{
    return (IS_ADC_PIN(Pin) ? ADCx_GetValue(PIN_MAP[Pin].ADCx, PIN_MAP[Pin].ADC_Channel) : 0);
}

/**
  * @brief  Analog pin read value (DMA mode)
  * @param  Pin: Pin number
  * @retval ADC value 0 to 4095
  */
uint16_t analogRead_DMA(uint8_t Pin)
{
    if(!IS_ADC_PIN(Pin))
        return 0;
    
    return ADC_DMA_GetValue(PIN_MAP[Pin].ADC_Channel);
}

/**
  * @brief  Shift out one byte of data at a time, starting from the leftmost or smallest (rightmost)
  * @param  dataPin: Output pin for each bit
  * @param  clockPin: Pin to toggle after setting dataPin to the correct value (int)
  * @param  bitOrder: MSBFIRST / LSBFIRST
  * @param  value: Data to shift out (bytes)
  * @retval Null
  */
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
    uint8_t i;
    digitalWrite_LOW(clockPin);
    for (i = 0; i < 8; i++)
    {
        int bit = bitOrder == LSBFIRST ? i : (7 - i);
        digitalWrite(dataPin, (value >> bit) & 0x1);
        togglePin(clockPin);
        togglePin(clockPin);
    }
}

/**
  * @brief  Shift data one byte at a time, starting from leftmost or least (rightmost)
  * @param  dataPin:  Input the pin for each bit
  * @param  clockPin: The pin signal to switch to is read from dataPin
  * @param  bitOrder: MSBFIRST/LSBFIRST
  * @retval Read value (bytes)
  */
uint32_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint32_t bitOrder)
{
    uint8_t value = 0 ;
    uint8_t i ;
    for ( i = 0 ; i < 8 ; ++i )
    {
        digitalWrite_HIGH(clockPin) ;
        if (bitOrder == LSBFIRST )
        {
            value |= digitalRead(dataPin) << i ;
        }
        else
        {
            value |= digitalRead(dataPin) << (7 - i) ;
        }
        digitalWrite_LOW(clockPin);
    }

    return value ;
}

/**
  * @brief  Remaps a number (integer) from one range to another
  * @param  x: The number to map
  * @param  in_min: The lower bound of the current range of values
  * @param  in_max: The upper bound of the current range of values
  * @param  out_min: The lower bound of the target range of values
  * @param  out_max: The upper bound of value target range
  * @retval Mapped value (long)
  */
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
  * @brief  Remaps a number (float) from one range to another
  * @param  x: The number to map
  * @param  in_min: The lower bound of the current range of values
  * @param  in_max: The upper bound of the current range of values
  * @param  out_min: The lower bound of the target range of values
  * @param  out_max: The upper bound of value target range
  * @retval Mapped value (double)
  */
double fmap(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
  * @brief  Read pulse on pin
  * @param  pin: The pin number to read the pulse from
  * @param  value: Pulse Type (High or Low)
  * @param  timeout: Time (microseconds) to wait for a pulse to start
  * @retval The length of the pulse in microseconds or 0 if no pulse started before the timeout
  */
uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout )
{
    // Cache the IDR address and bit of the pin in order to speed up the
    // pulse width measuring loop and achieve finer resolution. Calling
    // digitalRead() instead yields much coarser resolution.

    __IO uint16_t * const idr = portInputRegister(digitalPinToPort(pin));
    const uint32_t bit = digitalPinToBitMask(pin);
    const uint32_t stateMask = (state ? bit : 0);

    uint32_t width = 0; // Keep initialization out of time critical area

    // Convert the timeout from microseconds to a number of times through
    // the initial loop; it takes 16 clock cycles per iteration.
    uint32_t numloops = 0;
    uint32_t maxloops =  timeout * ( F_CPU / 16000000);
    volatile uint32_t dummyWidth = 0;

    // Wait for any previous pulse to end
    while ((*idr & bit) == stateMask)
    {
        if (numloops++ == maxloops)
        {
            return 0;
        }
        dummyWidth++;
    }

    // Wait for the pulse to start
    while ((*idr & bit) != stateMask)
    {
        if (numloops++ == maxloops)
        {
            return 0;
        }
        dummyWidth++;
    }

    // Wait for the pulse to stop
    while ((*idr & bit) == stateMask)
    {
        if (numloops++ == maxloops)
        {
            return 0;
        }
        width++;
    }

    // Excluding time taking up by the interrupts, it needs 16 clock cycles to look through the last while loop
    // 5 is added as a fiddle factor to correct for interrupts etc. But ultimately this would only be accurate if it was done ona hardware timer

    return (uint32_t)( ( (unsigned long long)(width + 5) *  (unsigned long long) 16000000.0) / (unsigned long long)F_CPU ) ;
}

void yield(void)
{
}
