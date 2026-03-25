#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#include<stdint.h>


#define GPIOA   ((struct GPIO_Def*)0x40020000U)
#define GPIOB   ((struct GPIO_Def*)0x40020400U)
#define GPIOC   ((struct GPIO_Def *)0x40020800U)
#define GPIOD   ((struct GPIO_Def*)0x40020C00U)
#define GPIOE   ((struct GPIO_Def *)0x40021000U)
#define GPIOF   ((struct GPIO_Def *)0x40021400U)
#define GPIOG   ((struct GPIO_Def*)0x40021800U)
#define GPIOH   ((struct GPIO_Def *)0x40021C00U)

struct GPIO_Def {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
};


typedef enum
{
  GPIO_MODE_INPUT       =0,
  GPIO_MODE_OUTPUT      =1,
  GPIO_MODE_ALTERNATE   =2,
  GPIO_MODE_ANALOG      =3
}gpio_mode;

typedef enum
{
  GPIO_SPEED_LOW       =0,
  GPIO_SPEED_MEDIUM    =1,
  GPIO_SPEED_FAST      =2,
  GPIO_SPEED_HIGH      =3
}gpio_speed;

typedef enum
{
  GPIO_NO_PUPD  =0,
  GPIO_PU       =1,
  GPIO_PD       =2
}gpio_pupd;
typedef enum{
    GPIO_PIN_0 =0,
    GPIO_PIN_1 =1,
    GPIO_PIN_2 =2,
    GPIO_PIN_3 =3,
    GPIO_PIN_4 =4,
    GPIO_PIN_5 =5,
    GPIO_PIN_6 =6,
    GPIO_PIN_7 =7,
    GPIO_PIN_8 =8,
    GPIO_PIN_9 =9,
    GPIO_PIN_10 =10,
    GPIO_PIN_11 =11,
    GPIO_PIN_12 =12,
    GPIO_PIN_13 =13,
    GPIO_PIN_14 =14,
   GPIO_PIN_16 =15
}Gpio_pin;
typedef enum{
AF0 =0,
AF1,
AF2,
AF3,
AF4,
AF5,
AF6,
AF7,
AF8,
AF9,
AF10,
AF11,
AF12,
AF13,
AF14,
AF15
}alternate_fucntion_mode;

typedef enum
{

   push_pull =0,
   open_drain =1,
   NONE
}Otype;

struct GPIO_Config
{
    struct GPIO_Def *port;
    Gpio_pin pin;
    gpio_mode  mode;
    Otype type;
    gpio_speed speed;
    gpio_pupd  pupd;
    alternate_fucntion_mode alternate;
} ;



void GPIO_Init(struct GPIO_Def*port, struct GPIO_Config *config);  
void GPIO_DeInit(struct GPIO_Def*port,struct GPIO_Config *config);
void GPIO_TogglePin(struct GPIO_Def*port, Gpio_pin);
void GPIO_SetPin(struct GPIO_Def*port, Gpio_pin);
void GPIO_ResetPin(struct GPIO_Def*port, Gpio_pin);
uint32_t GPIO_ReadPort(struct GPIO_Def*port);
void GPIO_WritePort(struct GPIO_Def*port,uint16_t data);
#endif