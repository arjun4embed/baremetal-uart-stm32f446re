#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#include<stdint.h>

#define USART1 ((struct UART_Reg_Def *)0x40011000)
#define USART2 ((struct UART_Reg_Def *)0x40004400)
#define USART3 ((struct UART_Reg_Def *)0x40004800)
#define UART4  ((struct UART_Reg_Def *)0x40004C00)
#define UART5  ((struct UART_Reg_Def *)0x40005000)
#define USART6 ((struct UART_Reg_Def *)0x40011400)

#define USART_SR_PE        (1U << 0)
#define USART_SR_FE        (1U << 1)
#define USART_SR_NE        (1U << 2)
#define USART_SR_ORE       (1U << 3)
#define USART_SR_IDLE      (1U << 4)
#define USART_SR_RXNE      (1U << 5)
#define USART_SR_TC        (1U << 6)
#define USART_SR_TXE       (1U << 7)
#define USART_SR_LBD       (1U << 8)
#define USART_SR_CTS       (1U << 9)

#define USART_CR1_SBK      (1U << 0)
#define USART_CR1_RWU      (1U << 1)
#define USART_CR1_RE       (1U << 2)
#define USART_CR1_TE       (1U << 3)
#define USART_CR1_IDLEIE   (1U << 4)
#define USART_CR1_RXNEIE   (1U << 5)
#define USART_CR1_TCIE     (1U << 6)
#define USART_CR1_TXEIE    (1U << 7)
#define USART_CR1_PEIE     (1U << 8)
#define USART_CR1_PS       (1U << 9)
#define USART_CR1_PCE      (1U << 10)
#define USART_CR1_WAKE     (1U << 11)
#define USART_CR1_M        (1U << 12)
#define USART_CR1_UE       (1U << 13)
#define USART_CR1_OVER8    (1U << 15)

#define USART_CR2_ADD_MASK   (0xFU << 0)
#define USART_CR2_LBDL       (1U << 5)
#define USART_CR2_LBDIE      (1U << 6)
#define USART_CR2_LBCL       (1U << 8)
#define USART_CR2_CPHA       (1U << 9)
#define USART_CR2_CPOL       (1U << 10)
#define USART_CR2_CLKEN      (1U << 11)
#define USART_CR2_STOP_MASK  (3U << 12)
#define USART_CR2_LINEN      (1U << 14)
#define USART_CR2_STOP_MASK (3U << 12)


#define USART_STOP_1      (0U << 12)
#define USART_STOP_0_5    (1U << 12)
#define USART_STOP_2      (2U << 12)
#define USART_STOP_1_5    (3U << 12)

struct UART_Reg_Def
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
};

typedef enum
{
    UART_BAUD_1200   = 1200,
    UART_BAUD_2400   = 2400,
    UART_BAUD_4800   = 4800,
    UART_BAUD_9600   = 9600,
    UART_BAUD_19200  = 19200,
    UART_BAUD_38400  = 38400,
    UART_BAUD_57600  = 57600,
    UART_BAUD_115200 = 115200,
    UART_BAUD_230400 = 230400,
    UART_BAUD_460800 = 460800,
    UART_BAUD_921600 = 921600
}uart_baudrate;

typedef enum
{
    UART_WORDLEN_8 = 0,
    UART_WORDLEN_9 = 1
} uart_word_length;

typedef enum{
    UART_ENABLE =1,
    UART_DISABLE =0
}uart_status;
typedef enum 
{
    UART_STOP_1   = 0,
    UART_STOP_0_5 = 1,
    UART_STOP_2   = 2,
    UART_STOP_1_5 = 3
}uart_stop_bits;
typedef enum 
{
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN = 1,
    UART_PARITY_ODD  = 2
}uart_parity;
typedef enum 
{
    UART_MODE_RX   = 1,
    UART_MODE_TX   = 2,
    UART_MODE_TXRX = 3
}uart_mode;
typedef enum 
{
    UART_HW_NONE   = 0,
    UART_HW_RTS    = 1,
    UART_HW_CTS    = 2,
    UART_HW_RTSCTS = 3
}uart_hw_flow;
typedef enum
{
 UART_OVER8_FALSE =0,
 UART_OVER8_TRUE  =1
}uart_OVER8;
typedef enum
{
    UART_MODE_POLLING = 0,
    UART_MODE_INTERRUPT =1
} uart_io_mode;
struct uart_config
{
     struct UART_Reg_Def *instance;
     uart_baudrate baudrate;
     uart_word_length word_length;
     uart_stop_bits stop_bits;
     uart_OVER8 samplingrate;
     uart_parity parity;
     uart_mode mode;
     uart_hw_flow hw_flow;
     uart_io_mode io_mode;
};

void uart_init(struct uart_config *uart);
void uart_write(struct uart_config *uart, const uint8_t *data, uint16_t len);
uint8_t uart_read_blocking(void);
int uart_read(uint8_t *data);
#endif