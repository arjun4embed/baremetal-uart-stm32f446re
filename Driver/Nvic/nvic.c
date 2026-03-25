#include "nvic.h"
#include<stdint.h>
#include<stdint.h>


void nvic_set_priority(uint8_t irq, nvic_priority priority)
{
    NVIC_IPR_BASE[irq] = (priority << 4);
}


void nvic_enable_irq(uint8_t irq)
{
    uint8_t index = irq / 32;
    uint8_t pos   = irq % 32;

    NVIC_ISER_BASE[index] = (1U << pos);
}
#define NVIC_ICER_BASE   ((volatile uint32_t*)0xE000E180)

void nvic_disable_irq(uint8_t irq)
{
    uint8_t index = irq / 32;
    uint8_t pos   = irq % 32;

    NVIC_ICER_BASE[index] = (1U << pos);
}