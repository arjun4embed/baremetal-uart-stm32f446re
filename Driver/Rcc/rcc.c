#include<stdint.h>
#include"rcc.h"




void rcc_enable_ahb1(rcc_peripheral peripheral )
{
   RCC->AHB1ENR |=1<<peripheral;
}

void rcc_disable_ahb1(rcc_peripheral peripheral)
{
    RCC->AHB1ENR &=~(1<<peripheral);
}

void rcc_enable_apb1(rcc_peripheral peripheral )
{
   RCC->APB1ENR |=1<<peripheral;
}
void rcc_disable_apb1(rcc_peripheral peripheral )
{
   RCC->APB1ENR &=1<<peripheral;
}

void rcc_enable_apb2(rcc_peripheral peripheral )
{
   RCC->APB2ENR |=1<<peripheral;
}
void rcc_disable_apb2(rcc_peripheral peripheral )
{
   RCC->APB2ENR &=1<<peripheral;
}