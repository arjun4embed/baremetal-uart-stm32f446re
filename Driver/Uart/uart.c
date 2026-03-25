/**
 * @file uart.c
 * @brief Bare-metal UART driver for STM32F446RE
 *
 * Features:
 *  - Polling TX/RX
 *  - Interrupt-based TX (ring buffer)
 *
 * Author: Arjun V
 * Date: 2026
 */
#include<stdint.h>
#include"uart.h"
#include "rcc.h"


static volatile uint8_t tx_data;
#define UART_TX_BUFFER_SIZE 2048
#define UART_RX_BUFFER_SIZE 1024

static volatile uint8_t tx_buffer[UART_TX_BUFFER_SIZE];
static volatile uint16_t tx_head = 0;
static volatile uint16_t tx_tail = 0;
static volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;


static uint32_t uart_compute_brr(uint32_t pclk,struct uart_config *uart)
{
    if (uart->samplingrate == 0U)
    {
        return (pclk + (uart->baudrate / 2U)) / uart->baudrate;
    }
    else
    {
        uint32_t div = (pclk * 2U + (uart->baudrate / 2U)) / uart->baudrate;
        uint32_t mantissa = div & 0xFFF0U;       
        uint32_t fraction = (div & 0xFU) >> 1; 
        return (mantissa | fraction);
    }
}



void uart_set_state(struct UART_Reg_Def *instance,uart_status status)
{
    if(status == UART_ENABLE)
    {
         instance->CR1 |=USART_CR1_UE;
    }
    else
    {
        instance->CR1 &=~USART_CR1_UE;
    }
}

void uart_init(struct uart_config *uart)
{

        uart_set_state(uart->instance,UART_DISABLE);
        uart->instance->CR1 &=~USART_CR1_M;
        uart->instance->CR2 &=~USART_CR2_STOP_MASK;
        uart->instance->CR2 |=USART_STOP_1;
        
         uart->instance->CR1 &=~USART_CR1_PCE;
        if(uart->parity !=UART_PARITY_NONE)
        {
            uart->instance->CR1 |=USART_CR1_PCE;
            
            if(uart->parity == UART_PARITY_EVEN)
            {
                uart->instance->CR1 &=~(USART_CR1_PS);
            }
            else
            {
                uart->instance->CR1 |=(USART_CR1_PS);
            }
        }
        
        if(uart->samplingrate == UART_OVER8_TRUE)
        {
            uart->instance->CR1 |=USART_CR1_OVER8;
        }
        else
        {
            uart->instance->CR1 &=~USART_CR1_OVER8;
        }
        uint32_t p_clk;
        if(uart->instance == USART1 || uart->instance ==USART6)
        {
               p_clk = APB2_PERIPHERAL_CLOCK;
        }
        else
        {
             p_clk = APB1_PERIPHERAL_CLOCK;
        }

        uint32_t USARTDIV = uart_compute_brr(p_clk,uart);

        uart->instance->BRR = USARTDIV;

        uart->instance->CR1 &=~(USART_CR1_RE | USART_CR1_TE);
        uart->instance->CR1 &=~(USART_CR1_TXEIE|USART_CR1_RXNEIE);

        if(uart->mode == UART_MODE_RX)
        {
            uart->instance->CR1 |= USART_CR1_RE;
            uart->instance->CR1 |=USART_CR1_RXNEIE;
            
        }
        else if(uart->mode == UART_MODE_TX)
        {
           uart->instance->CR1 |= USART_CR1_TE;
        }
        else if(uart->mode == UART_MODE_TXRX)
        {
           uart->instance->CR1 |= USART_CR1_RE;
           uart->instance->CR1 |= USART_CR1_TE;
           uart->instance->CR1 |=USART_CR1_RXNEIE;
        }
       
        uart_set_state(uart->instance,UART_ENABLE);

}




void uart_write(struct uart_config *uart, const uint8_t *data, uint16_t len)
{
    
    if (uart->io_mode == UART_MODE_POLLING)
    {
          for (uint16_t i = 0; i < len; i++)
        {
            while (!(uart->instance->SR & USART_SR_TXE));
            uart->instance->DR = data[i];
        }

        while (!(uart->instance->SR & USART_SR_TC));
    }
    else
    {
        for (uint16_t i = 0; i < len; i++)
        {
            uint16_t next_head = (tx_head + 1) % UART_TX_BUFFER_SIZE;

            while (next_head == tx_tail);   

            tx_buffer[tx_head] = data[i];
            tx_head = next_head;
        }

        uart->instance->CR1 |= USART_CR1_TXEIE;
    }
    
}
uint8_t uart_read_blocking(void)
{
    while (!(USART2->SR & USART_SR_RXNE));
    return (uint8_t)USART2->DR;
}
int uart_read(uint8_t *data)
{
    if (rx_head == rx_tail)
        return 0; 

    *data = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_RX_BUFFER_SIZE;

    return 1;
}
void USART2_IRQHandler(void)
{
    if ((USART2->SR & USART_SR_TXE) &&
    (USART2->CR1 & USART_CR1_TXEIE))
{
    if (tx_head != tx_tail)
    {
        USART2->DR  = tx_buffer[tx_tail];
        tx_tail = (tx_tail + 1) % UART_TX_BUFFER_SIZE;
    }
    else
    {
        USART2->CR1 &= ~USART_CR1_TXEIE;
    }
}
 if (USART2->SR & USART_SR_RXNE)
    {
        uint8_t data = USART2->DR;  

        uint16_t next = (rx_head + 1) % UART_RX_BUFFER_SIZE;

        if (next != rx_tail)  
        {
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
        else
        {
            while (1)
            {
               //overflow happened
            }
            
        }
    }
}


