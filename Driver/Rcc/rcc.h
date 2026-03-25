#ifndef DRIVER_RCC_H_
#define DRIVER_RCC_H_

#include <stdint.h>

#define RCC_BASE_ADDR  0x40023800U

#define RCC  ((struct RCC_REG_DEF*)RCC_BASE_ADDR)



#define APB1_PERIPHERAL_CLOCK   16000000U
#define APB2_PERIPHERAL_CLOCK   16000000U
typedef enum{

    RCC_AHB1_GPIOA        =0,
    RCC_AHB1_GPIOB        =1,
    RCC_AHB1_GPIOC        =2,
    RCC_AHB1_GPIOD        =3,
    RCC_AHB1_GPIOE        =4,
    RCC_AHB1_GPIOF        =5,
    RCC_AHB1_GPIOG        =6,
    RCC_AHB1_GPIOH        =7,
    RCC_APB2ENR_TIM1EN      = 0,
    RCC_APB2ENR_TIM8EN      = 1,
    RCC_APB2ENR_USART1EN    = 4,
    RCC_APB2ENR_USART6EN    = 5,
    RCC_APB2ENR_ADC1EN      = 8,
    RCC_APB2ENR_ADC2EN      = 9,
    RCC_APB2ENR_ADC3EN      = 10,
    RCC_APB2ENR_SDIOEN      = 11,
    RCC_APB2ENR_SPI1EN      = 12,
    RCC_APB2ENR_SPI4EN      = 13,
    RCC_APB2ENR_SYSCFGEN    = 14,
    RCC_APB2ENR_TIM9EN      = 16,
    RCC_APB2ENR_TIM10EN     = 17,
    RCC_APB2ENR_TIM11EN     = 18,
    RCC_APB2ENR_SPI5EN      = 20,
    RCC_APB2ENR_SAI1EN      = 22,
    RCC_APB2ENR_SAI2EN      = 23,
     RCC_APB2_TIM1        = 0,
    RCC_APB2_TIM8        = 1,
    RCC_APB2_USART1      = 4,
    RCC_APB2_USART6      = 5,
    RCC_APB2_ADC1        = 8,
    RCC_APB2_ADC2        = 9,
    RCC_APB2_ADC3        = 10,
    RCC_APB2_SDIO        = 11,
    RCC_APB2_SPI1        = 12,
    RCC_APB2_SPI4        = 13,
    RCC_APB2_SYSCFG      = 14,
    RCC_APB2_TIM9        = 16,
    RCC_APB2_TIM10       = 17,
    RCC_APB2_TIM11       = 18,
    RCC_APB2_SPI5        = 20,
    RCC_APB2_SAI1        = 22,
    RCC_APB2_SAI2        = 23,
    RCC_APB1_USART2 = 17  
}rcc_peripheral;
struct RCC_REG_DEF
{
    volatile unsigned int CR;
    volatile unsigned int PLLCFGR;
    volatile unsigned int CFGR;
    volatile unsigned int CIR;
    volatile unsigned int AHB1RSTR;
    volatile unsigned int AHB2RSTR;
    volatile unsigned int AHB3RSTR;
    volatile unsigned int RESERVED0;
    volatile unsigned int APB1RSTR;
    volatile unsigned int APB2RSTR;
    volatile unsigned int RESERVED1[2];
    volatile unsigned int AHB1ENR;
    volatile unsigned int AHB2ENR;
    volatile unsigned int AHB3ENR;
    volatile unsigned int RESERVED2;
    volatile unsigned int APB1ENR;
    volatile unsigned int APB2ENR;
};

void rcc_enable_ahb1(rcc_peripheral peripheral );
void rcc_disable_ahb1(rcc_peripheral peripheral);

void rcc_enable_apb1(rcc_peripheral peripheral );
void rcc_disable_apb1(rcc_peripheral peripheral );

void rcc_enable_apb2(rcc_peripheral peripheral );
void rcc_disable_apb2(rcc_peripheral peripheral );

#endif /* DRIVER_RCC_H_ */
