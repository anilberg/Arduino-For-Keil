/**
  ******************************************************************************
  * @file    stm32wbxx_ll_conf.h
  * @author  MCD Application Team
  * @brief   LL configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32WBXX_LL_CONF_H
#define __STM32WBXX_LL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the LL driver
  */
#define USE_FULL_LL_DRIVER

/* ########################## Oscillator Values adaptation ####################*/
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC LL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE) 
#define HSE_VALUE    8000000U             /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint32_t)100)   /*!< Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief Internal Multiple Speed oscillator (MSI) default value.
  *        This value is the default MSI range value after Reset.
  */
#if !defined  (MSI_VALUE)
  #define MSI_VALUE    ((uint32_t)4000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the RCC LL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
#define HSI_VALUE    16000000U            /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
  * @brief Internal Low Speed oscillator (LSI1) value.
  */
#if !defined  (LSI1_VALUE) 
 #define LSI1_VALUE  ((uint32_t)32000)       /*!< LSI1 Typical Value in Hz*/
#endif /* LSI1_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.*/
/**
  * @brief Internal Low Speed oscillator (LSI2) value.
  */
#if !defined  (LSI2_VALUE) 
 #define LSI2_VALUE  ((uint32_t)32000)       /*!< LSI2 Typical Value in Hz*/
#endif /* LSI2_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.*/

/**
  * @brief External Low Speed oscillator (LSE) value.
  *        This value is used by the UART, RTC LL module to compute the system frequency
  */
#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U               /*!< Value of the External oscillator in Hz*/
#endif /* LSE_VALUE */

/**
  * @brief Internal Multiple Speed oscillator (HSI48) default value.
  *        This value is the default HSI48 range value after Reset.
  */
#if !defined (HSI48_VALUE)
  #define HSI48_VALUE    ((uint32_t)48000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI48_VALUE */
   
#if !defined  (LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT    5000U      /*!< Time out for LSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief External clock source for SAI1 peripheral
  *        This value is used by the RCC LL module to compute the SAI1 & SAI2 clock source 
  *        frequency.
  */
#if !defined (EXTERNAL_SAI1_CLOCK_VALUE)
  #define EXTERNAL_SAI1_CLOCK_VALUE    ((uint32_t)2097000) /*!< Value of the SAI1 External clock source in Hz*/
#endif /* EXTERNAL_SAI1_CLOCK_VALUE */

/* Tip: To avoid modifying this file each time you need to use different HSE,
   ===  you can define the HSE value in your toolchain compiler preprocessor. */

/* ########################### System Configuration ######################### */
/**
  * @brief This is the LL system configuration section
  */     
  
#define  VDD_VALUE				3300U                   /*!< Value of VDD in mv */           
#define  TICK_INT_PRIORITY            15U      /*!< tick interrupt priority */            
#define  USE_RTOS                     0U     
#define  PREFETCH_ENABLE              1U
#define  INSTRUCTION_CACHE_ENABLE     1U
#define  DATA_CACHE_ENABLE            1U

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the
  *        LL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* ################## SPI peripheral configuration ########################## */

/* CRC FEATURE: Use to activate CRC feature inside LL SPI Driver
 * Activated: CRC code is present inside driver
 * Deactivated: CRC code cleaned from driver
 */

#define USE_SPI_CRC                   0U

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file
  */
#ifdef LL_DMA_MODULE_ENABLED
  #include "stm32wbxx_ll_dma.h"
#endif /* LL_DMA_MODULE_ENABLED */

#ifdef LL_ADC_MODULE_ENABLED
  #include "stm32wbxx_ll_adc.h"
#endif /* LL_ADC_MODULE_ENABLED */

#ifdef LL_COMP_MODULE_ENABLED
  #include "stm32wbxx_ll_comp.h"
#endif /* LL_COMP_MODULE_ENABLED */

#ifdef LL_CORTEX_MODULE_ENABLED
  #include "stm32wbxx_ll_cortex.h"
#endif /* LL_CORTEX_MODULE_ENABLED */

#ifdef LL_CRC_MODULE_ENABLED
  #include "stm32wbxx_ll_crc.h"
#endif /* LL_CRC_MODULE_ENABLED */

#ifdef LL_CRYP_MODULE_ENABLED
  #include "stm32wbxx_ll_cryp.h"
#endif /* LL_CRYP_MODULE_ENABLED */

#ifdef LL_EXTI_MODULE_ENABLED
  #include "stm32wbxx_ll_exti.h"
#endif /* LL_EXTI_MODULE_ENABLED */
   
#ifdef LL_FLASH_MODULE_ENABLED
  #include "stm32wbxx_ll_flash.h"
#endif /* LL_FLASH_MODULE_ENABLED */

#ifdef LL_GPIO_MODULE_ENABLED
  #include "stm32wbxx_ll_gpio.h"
#endif /* LL_GPIO_MODULE_ENABLED */

#ifdef LL_HSEM_MODULE_ENABLED
  #include "stm32wbxx_ll_hsem.h"
#endif /* LL_HSEM_MODULE_ENABLED */

#ifdef LL_I2C_MODULE_ENABLED
 #include "stm32wbxx_ll_i2c.h"
#endif /* LL_I2C_MODULE_ENABLED */

#ifdef LL_IPCC_MODULE_ENABLED
 #include "stm32wbxx_ll_ipcc.h"
#endif /* LL_IPCC_MODULE_ENABLED */

#ifdef LL_IRDA_MODULE_ENABLED
 #include "stm32wbxx_ll_irda.h"
#endif /* LL_IRDA_MODULE_ENABLED */

#ifdef LL_IWDG_MODULE_ENABLED
 #include "stm32wbxx_ll_iwdg.h"
#endif /* LL_IWDG_MODULE_ENABLED */

#ifdef LL_LCD_MODULE_ENABLED
 #include "stm32wbxx_ll_lcd.h"
#endif /* LL_LCD_MODULE_ENABLED */

#ifdef LL_LPTIM_MODULE_ENABLED
  #include "stm32wbxx_ll_lptim.h"
#endif /* LL_LPTIM_MODULE_ENABLED */

#ifdef LL_PCD_MODULE_ENABLED
  #include "stm32wbxx_ll_pcd.h"
#endif /* LL_PCD_MODULE_ENABLED */

#ifdef LL_PKA_MODULE_ENABLED
  #include "stm32wbxx_ll_pka.h"
#endif /* LL_PKA_MODULE_ENABLED */

#ifdef LL_PWR_MODULE_ENABLED
 #include "stm32wbxx_ll_pwr.h"
#endif /* LL_PWR_MODULE_ENABLED */

#ifdef LL_QSPI_MODULE_ENABLED
 #include "stm32wbxx_ll_qspi.h"
#endif /* LL_QSPI_MODULE_ENABLED */

#ifdef LL_RCC_MODULE_ENABLED
  #include "stm32wbxx_ll_rcc.h"
#endif /* LL_RCC_MODULE_ENABLED */

#ifdef LL_RNG_MODULE_ENABLED
  #include "stm32wbxx_ll_rng.h"
#endif /* LL_RNG_MODULE_ENABLED */
    
#ifdef LL_RTC_MODULE_ENABLED
 #include "stm32wbxx_ll_rtc.h"
#endif /* LL_RTC_MODULE_ENABLED */

#ifdef LL_SAI_MODULE_ENABLED
 #include "stm32wbxx_ll_sai.h"
#endif /* LL_SAI_MODULE_ENABLED */

#ifdef LL_SMARTCARD_MODULE_ENABLED
 #include "stm32wbxx_ll_smartcard.h"
#endif /* LL_SMARTCARD_MODULE_ENABLED */

#ifdef LL_SMBUS_MODULE_ENABLED
 #include "stm32wbxx_ll_smbus.h"
#endif /* LL_SMBUS_MODULE_ENABLED */

#ifdef LL_SPI_MODULE_ENABLED
 #include "stm32wbxx_ll_spi.h"
#endif /* LL_SPI_MODULE_ENABLED */

#ifdef LL_TIM_MODULE_ENABLED
 #include "stm32wbxx_ll_tim.h"
#endif /* LL_TIM_MODULE_ENABLED */

#ifdef LL_TSC_MODULE_ENABLED
  #include "stm32wbxx_ll_tsc.h"
#endif /* LL_TSC_MODULE_ENABLED */

#ifdef LL_UART_MODULE_ENABLED
 #include "stm32wbxx_ll_uart.h"
#endif /* LL_UART_MODULE_ENABLED */

#ifdef LL_USART_MODULE_ENABLED
 #include "stm32wbxx_ll_usart.h"
#endif /* LL_USART_MODULE_ENABLED */

#ifdef LL_WWDG_MODULE_ENABLED
 #include "stm32wbxx_ll_wwdg.h"
#endif /* LL_WWDG_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __stm32wbxx_ll_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
