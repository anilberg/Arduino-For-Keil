#ifndef __STM32F0XX_CONF_H
#define __STM32F0XX_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32wbxx_hal_adc.h"
//#include "stm32wbxx_hal_cec.h"
#include "stm32wbxx_hal_crc.h"
#include "stm32wbxx_hal_comp.h"
//#include "stm32wbxx_hal_dac.h"
//#include "stm32wbxx_hal_dbgmcu.h"
#include "stm32wbxx_hal_dma.h"
#include "stm32wbxx_hal_exti.h"
#include "stm32wbxx_hal_flash.h"
#include "stm32wbxx_hal_gpio.h"
//#include "stm32wbxx_hal_syscfg.h"
#include "stm32wbxx_hal_i2c.h"
#include "stm32wbxx_hal_iwdg.h"
#include "stm32wbxx_hal_pwr.h"
#include "stm32wbxx_hal_rcc.h"
#include "stm32wbxx_hal_rtc.h"
#include "stm32wbxx_hal_spi.h"
#include "stm32wbxx_hal_tim.h"
#include "stm32wbxx_hal_usart.h"
#include "stm32wbxx_hal_wwdg.h"
//#include "stm32wbxx_hal_misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */


/* ȡ��������һ��չ��assert_param�����ڱ�׼�����������������*/
/*#define USE_FULL_ASSERT    1 */

/* �����ĺ궨�� --------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/***************************************************************************//**
  * @brief   assert_param ���ڲ������.
  * @param   expr: ����expr��flase, ������� assert_param
  *          ������������ڵ�Դ�ļ��������ڵ�����
  *          ����expr �� true, ��������ֵ.
  * @retval  ��
*******************************************************************************/
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* ��������------------------------------------------------------------------ */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}// extern "C"
#endif

#endif /* __STM32F0XX_CONF_H */
