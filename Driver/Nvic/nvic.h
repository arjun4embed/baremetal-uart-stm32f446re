#ifndef MCU_H_
#define MCU_H_

#include<stdint.h> 

#define NVIC_PRIO_BITS   4 //mcu dependent
#define NVIC_IPR_BASE   ((volatile uint8_t*)0xE000E400)
#define NVIC_ISER_BASE   ((volatile uint32_t*)0xE000E100)

typedef enum
{
    NVIC_PRIORITY_0  = 0,
    NVIC_PRIORITY_1  = 1,
    NVIC_PRIORITY_2  = 2,
    NVIC_PRIORITY_3  = 3,
    NVIC_PRIORITY_4  = 4,
    NVIC_PRIORITY_5  = 5,
    NVIC_PRIORITY_6  = 6,
    NVIC_PRIORITY_7  = 7,
    NVIC_PRIORITY_8  = 8,
    NVIC_PRIORITY_9  = 9,
    NVIC_PRIORITY_10 = 10,
    NVIC_PRIORITY_11 = 11,
    NVIC_PRIORITY_12 = 12,
    NVIC_PRIORITY_13 = 13,
    NVIC_PRIORITY_14 = 14,
    NVIC_PRIORITY_15 = 15
} nvic_priority;

typedef enum
{
    IRQ_WWDG               = 0,
    IRQ_PVD                = 1,
    IRQ_TAMP_STAMP         = 2,
    IRQ_RTC_WKUP           = 3,
    IRQ_FLASH              = 4,
    IRQ_RCC                = 5,
    IRQ_EXTI0              = 6,
    IRQ_EXTI1              = 7,
    IRQ_EXTI2              = 8,
    IRQ_EXTI3              = 9,
    IRQ_EXTI4              = 10,
    IRQ_DMA1_STREAM0       = 11,
    IRQ_DMA1_STREAM1       = 12,
    IRQ_DMA1_STREAM2       = 13,
    IRQ_DMA1_STREAM3       = 14,
    IRQ_DMA1_STREAM4       = 15,
    IRQ_DMA1_STREAM5       = 16,
    IRQ_DMA1_STREAM6       = 17,
    IRQ_ADC                = 18,
    IRQ_CAN1_TX            = 19,
    IRQ_CAN1_RX0           = 20,
    IRQ_CAN1_RX1           = 21,
    IRQ_CAN1_SCE           = 22,
    IRQ_EXTI9_5            = 23,
    IRQ_TIM1_BRK_TIM9      = 24,
    IRQ_TIM1_UP_TIM10      = 25,
    IRQ_TIM1_TRG_COM_TIM11 = 26,
    IRQ_TIM1_CC            = 27,
    IRQ_TIM2               = 28,
    IRQ_TIM3               = 29,
    IRQ_TIM4               = 30,
    IRQ_I2C1_EV            = 31,
    IRQ_I2C1_ER            = 32,
    IRQ_I2C2_EV            = 33,
    IRQ_I2C2_ER            = 34,
    IRQ_SPI1               = 35,
    IRQ_SPI2               = 36,
    IRQ_USART1             = 37,
    IRQ_USART2             = 38,
    IRQ_USART3             = 39,
    IRQ_EXTI15_10          = 40,
    IRQ_RTC_ALARM          = 41,
    IRQ_OTG_FS_WKUP        = 42,
    IRQ_TIM8_BRK_TIM12     = 43,
    IRQ_TIM8_UP_TIM13      = 44,
    IRQ_TIM8_TRG_COM_TIM14 = 45,
    IRQ_TIM8_CC            = 46,
    IRQ_DMA1_STREAM7       = 47,
    IRQ_FMC                = 48,
    IRQ_SDIO               = 49,
    IRQ_TIM5               = 50,
    IRQ_SPI3               = 51,
    IRQ_UART4              = 52,
    IRQ_UART5              = 53,
    IRQ_TIM6_DAC           = 54,
    IRQ_TIM7               = 55,
    IRQ_DMA2_STREAM0       = 56,
    IRQ_DMA2_STREAM1       = 57,
    IRQ_DMA2_STREAM2       = 58,
    IRQ_DMA2_STREAM3       = 59,
    IRQ_DMA2_STREAM4       = 60,
    IRQ_ETH                = 61,
    IRQ_ETH_WKUP           = 62,
    IRQ_CAN2_TX            = 63,
    IRQ_CAN2_RX0           = 64,
    IRQ_CAN2_RX1           = 65,
    IRQ_CAN2_SCE           = 66,
    IRQ_OTG_FS             = 67,
    IRQ_DMA2_STREAM5       = 68,
    IRQ_DMA2_STREAM6       = 69,
    IRQ_DMA2_STREAM7       = 70,
    IRQ_USART6             = 71,
    IRQ_I2C3_EV            = 72,
    IRQ_I2C3_ER            = 73,
    IRQ_OTG_HS_EP1_OUT     = 74,
    IRQ_OTG_HS_EP1_IN      = 75,
    IRQ_OTG_HS_WKUP        = 76,
    IRQ_OTG_HS             = 77,
    IRQ_DCMI               = 78,
    IRQ_CRYP               = 79,
    IRQ_HASH_RNG           = 80,
    IRQ_FPU                = 81,
    IRQ_UART7              = 82,
    IRQ_UART8              = 83,
    IRQ_SPI4               = 84,
    IRQ_SPI5               = 85,
    IRQ_SPI6               = 86,
    IRQ_SAI1               = 87,
    IRQ_LTDC               = 88,
    IRQ_LTDC_ER            = 89,
    IRQ_DMA2D              = 90
} irq_number_t;


void nvic_set_priority(uint8_t irq, nvic_priority priority);


void nvic_enable_irq(uint8_t irq);

void nvic_disable_irq(uint8_t irq);

#endif