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
#include "HardwareSerial.h"

/**
  * @brief  Serial port object constructor
  * @param  Serial port peripheral address
  * @retval Null
  */
HardwareSerial::HardwareSerial(USART_TypeDef *_USARTx)
{
    this->USARTx = _USARTx;
    USART_Function = 0;
}

/**
  * @brief  Serial port interrupt handler
  * @param  Null
  * @retval Null
  */
void HardwareSerial::IRQHandler()
{
    if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        uint8_t c = USART_ReceiveData(USARTx);
        uint16_t i = (uint16_t)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
        if (i != _rx_buffer_tail)
        {
            _rx_buffer[_rx_buffer_head] = c;
            _rx_buffer_head = i;
        }

        if(USART_Function)
        {
            USART_Function();
        }

        USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
    }
}

/**
  * @brief  Serial port initialization
  * @param  BaudRate: Baudrate
  * @retval Null
  */
void HardwareSerial::begin(uint32_t BaudRate)
{
    begin(BaudRate, SERIAL_Config_Default);
}

/**
  * @brief  Serial port initialization
  * @param  BaudRate: Baudrate
  * @param  Config: Configuration parameters
  * @retval Null
  */
void HardwareSerial::begin(uint32_t BaudRate, SERIAL_Config Config)
{
    begin(BaudRate, Config, USART_ChannelPriority_Default);
}

/**
  * @brief  Serial port initialization
  * @param  BaudRate: Baudrate
  * @param  Config: Configuration parameters
  * @param  ChannelPriority: Channel priority
  * @retval Null
  */
void HardwareSerial::begin(uint32_t BaudRate, SERIAL_Config Config, uint8_t ChannelPriority)
{
    // GPIO port settings
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint16_t Tx_Pin, Rx_Pin;
    uint16_t ItChannel;
    uint32_t RCC_AHBPeriph_GPIOx;
    GPIO_TypeDef *GPIOx;

    if(USARTx == USART1)
    {
        Tx_Pin = GPIO_Pin_9;
        Rx_Pin = GPIO_Pin_10;

        GPIOx = GPIOA;
        RCC_AHBPeriph_GPIOx = RCC_AHBPeriph_GPIOA;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        ItChannel = USART1_IRQn;
    }
    else if(USARTx == USART2)
    {
        Tx_Pin = GPIO_Pin_2;
        Rx_Pin = GPIO_Pin_3;

        GPIOx = GPIOA;
        RCC_AHBPeriph_GPIOx = RCC_AHBPeriph_GPIOA;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        ItChannel = USART2_IRQn;
    }

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);

    GPIO_PinAFConfig(GPIOx, GPIO_GetPinSource(Tx_Pin), GPIO_AF_1);
    GPIO_PinAFConfig(GPIOx, GPIO_GetPinSource(Rx_Pin), GPIO_AF_1);

    GPIO_InitStructure.GPIO_Pin =  Tx_Pin | Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    // Usart NVIC configuration
    NVIC_InitStructure.NVIC_IRQChannel = ItChannel;
    NVIC_InitStructure.NVIC_IRQChannelPriority = ChannelPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // USART initialization settings
    USART_InitStructure.USART_BaudRate = BaudRate;	// Serial baudrate
    USART_InitStructure.USART_WordLength = Get_USART_WordLength_x(Config);	// Word length is 8-bit data format
    USART_InitStructure.USART_StopBits = Get_USART_StopBits_x(Config);	// Stop bit
    USART_InitStructure.USART_Parity = Get_USART_Parity_x(Config);	// No parity bit
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// No hardware flow control
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // Transceiver mode
    USART_Init(USARTx, &USART_InitStructure); // Initialize the serial port

    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	// Open the serial port to accept interrupt
    USART_Cmd(USARTx, ENABLE);                   // Enable serial port
}

/**
  * @brief  Close the serial port
  * @param  Null
  * @retval Null
  */
void HardwareSerial::end(void)
{
    USART_Cmd(USARTx, DISABLE);
}

/**
  * @brief  Serial port interrupt callback
  * @param  Function: Callback
  * @retval Null
  */
void HardwareSerial::attachInterrupt(USART_CallbackFunction_t Function)
{
    USART_Function = Function;
}

/**
  * @brief  Get the number of bytes readable from the serial port
  * @param  Null
  * @retval The number of bytes that can be read
  */
int HardwareSerial::available(void)
{
    return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

/**
  * @brief  Read incoming serial data (characters)
  * @param  Null
  * @retval First byte of incoming serial data available (-1 if no data available)
  */
int HardwareSerial::read(void)
{
    // If the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        unsigned char c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }
}

/**
  * @brief  Returns the next byte (character) of incoming serial data without removing it from the internal serial buffer
  * @param  Null
  * @retval First byte of incoming serial data available (-1 if no data available)
  */
int HardwareSerial::peek(void)
{
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        return _rx_buffer[_rx_buffer_tail];
    }
}

/**
  * @brief  Clear the serial cache
  * @param  Null
  * @retval Null
  */
void HardwareSerial::flush(void)
{
    while(read() >= 0);
}

/**
  * @brief  Serial port writes a byte
  * @param  Byte will be written
  * @retval 1
  */
size_t HardwareSerial::write(uint8_t n)
{
    while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE)){};
    USART_SendData(USARTx, n);
    return 1;
}

// Create Object For User
HardwareSerial Serial(USART1);	//TX-PA9 RX-PA10
HardwareSerial Serial2(USART2);	//TX-PA2 RX-PA3

// USARTx_IRQHandler
extern "C" {
    void USART1_IRQHandler(void)
    {
        Serial.IRQHandler();
    }

    void USART2_IRQHandler(void)
    {
        Serial2.IRQHandler();
    }
}
