#include<stdint.h>
#include<string.h>
#include"gpio.h"
#include"uart.h"
#include "nvic.h"
#include "rcc.h"
const char *logo =
"\033[2J\033[H"
"\r\n"
" ██    ██  █████  ██████  ████████      \r\n"
" ██    ██ ██   ██ ██   ██    ██        \r\n"
" ██    ██ ███████ ██████     ██        \r\n"
" ██    ██ ██   ██ ██   ██    ██      \r\n"
"  ██████  ██   ██ ██   ██    ██     \r\n"
"\r\n"
"===============================================================================\r\n"
"  Custom UART Driver (Bare-Metal)\r\n"
"\r\n"
"  Target MCU   : STM32F446RE (Cortex-M4)\r\n"
"  Interface    : USART2\r\n"
"\r\n"
"  Features:\r\n"
"    - Register-level configuration (No HAL)\r\n"
"    - Polling-based TX/RX\r\n"
"    - Interrupt-driven TX (Ring Buffer)\r\n"
"    - NVIC + ISR handling\r\n"
"\r\n"
"  Status       : Driver Initialized Successfully\r\n"
"===============================================================================\r\n"
"\r\n";



void console_show_logo(struct uart_config *uart)
{
    
     uart_write(uart,logo, strlen(logo));
     const char *boot_msg = "Press any key to continue...\r\n";
     uart_write(uart, boot_msg, strlen(boot_msg));

}




void uart_cursor_test(struct uart_config *uart)
{
    const uint8_t beep[] = "\a";
uart_write(uart, beep, sizeof(beep) - 1);

    /* Clear entire screen */
    const uint8_t clear_screen[] = "\033[2J";
    uart_write(uart, clear_screen, sizeof(clear_screen) - 1);

    /* Move cursor to row 5, column 10 */
    const uint8_t move_cursor[] = "\033[5;10H";
    uart_write(uart, move_cursor, sizeof(move_cursor) - 1);

    /* Print HELLO */
    const uint8_t text[] = "HELLO";
    uart_write(uart, text, sizeof(text) - 1);
}


int main()
{
    rcc_enable_ahb1( RCC_AHB1_GPIOA );
    rcc_enable_apb1(RCC_APB1_USART2);
    struct GPIO_Config config;
    config.port = GPIOA;
    config.mode =GPIO_MODE_ALTERNATE;
    config.pin = GPIO_PIN_2;
    config.speed = GPIO_SPEED_FAST;
    config.pupd = GPIO_NO_PUPD;
    config.alternate = AF7;
    GPIO_Init(GPIOA,&config);
    config.pin = GPIO_PIN_3;
     GPIO_Init(GPIOA,&config);


    struct uart_config uart2;
    uart2.instance  = USART2;
    uart2.baudrate = UART_BAUD_115200;
    uart2.mode = UART_MODE_TXRX;
    uart2.parity = UART_PARITY_NONE;
    uart2.samplingrate = UART_OVER8_FALSE;
    uart2.stop_bits = UART_STOP_1;
    uart2.hw_flow = UART_HW_NONE;
    uart2.io_mode = UART_MODE_INTERRUPT;

   nvic_set_priority(IRQ_USART2, NVIC_PRIORITY_5);
   nvic_enable_irq(IRQ_USART2);
    uart_init(&uart2);
    //uart_cursor_test(&uart2);
    console_show_logo(&uart2);
    while(1);
}
