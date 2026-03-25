#include<stdint.h>
#include"gpio.h"

void GPIO_Init(struct GPIO_Def*port, struct GPIO_Config *config)
{
  uint8_t shift = 2u*config->pin;
   port->MODER &=(uint32_t)~(0X3<<shift);
   port->MODER |=(uint32_t)(config->mode<<shift);
  
   port->OSPEEDR &=(uint32_t)~(0X3<<shift);
   port->OSPEEDR |=(uint32_t)(config->speed<<shift);

   port->PUPDR &=(uint32_t)~(0X3<<shift);
   port->PUPDR |=(uint32_t)(config->pupd<<shift);

   if(config->mode == GPIO_MODE_OUTPUT || config->mode == GPIO_MODE_ALTERNATE)
   {
    port->OTYPER &=(uint32_t)~(0X1<<config->pin);
    port->OTYPER |=(uint32_t)(config->type<<config->pin);
   }

    if(config->mode == GPIO_MODE_ALTERNATE)
    {
        uint32_t shift = 4U * (config->pin % 8U);
        if(config->pin < 8)
        {
            port->AFRL &=(uint32_t)~(0xf<<shift);
            port->AFRL |=(uint32_t)(config->alternate<<shift);
        }
        else
        {
            port->AFRH &=(uint32_t)~(0xf<<shift);
            port->AFRH |=(uint32_t)(config->alternate<<shift);
        }
    }

}
   
void GPIO_DeInit(struct GPIO_Def*port,struct GPIO_Config *config)
{
  uint8_t shift = 2u*config->pin;

   port->MODER &=(uint32_t)~(0X3<<shift);
   port->OSPEEDR &=(uint32_t)~(0X3<<shift);
   port->PUPDR &=(uint32_t)~(0X3<<shift);

    port->OTYPER &=(uint32_t)~(0X1<<config->pin);
 
   
   if(config->mode == GPIO_MODE_ALTERNATE)
    {
        uint32_t shift = 4U * (config->pin % 8U);
        if(config->pin < 8)
        {
            port->AFRL &=(uint32_t)~(0xf<<shift);
        }
        else
        {
            port->AFRH &=(uint32_t)~(0xf<<shift);
        }
    }

}

void GPIO_TogglePin(struct GPIO_Def*port,Gpio_pin pin)
{
   if(port->ODR & (1u<<pin))
   {
    GPIO_ResetPin(port,pin);
   }
   else
   {
    GPIO_SetPin(port,pin);
   }
}
void GPIO_SetPin(struct GPIO_Def*port, Gpio_pin pin)
{
    port->BSRR = 1<<pin;
}

void GPIO_ResetPin(struct GPIO_Def*port, Gpio_pin pin)
{
   port->BSRR = 1<<(pin + 16u);
}


uint32_t GPIO_ReadPort(struct GPIO_Def*port)
{
   return port->IDR;
}
void GPIO_WritePort(struct GPIO_Def*port,uint16_t data)
{
  port->ODR = data;
}