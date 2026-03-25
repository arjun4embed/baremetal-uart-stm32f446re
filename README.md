# STM32 Bare-Metal UART Driver 

Custom UART driver for STM32F446RE using direct register-level programming (no HAL).

---

## Features

- Polling-based TX/RX
- Interrupt-driven TX (ring buffer)
- Interrupt-driven RX (ring buffer)
- Dynamic baud rate calculation (OVER8 / OVER16)
- Manual ISR handling (USART2)

---

## Hardware

- STM32 Nucleo-F446RE  
- USART2 (PA2 - TX, PA3 - RX)

---

## Usage

### Initialization
```c
uart_init(&uart_config);
```

---

### Polling Mode

#### Write (Blocking)
```c
uart_write(&uart_config, data, len);
```

#### Read (Blocking)
```c
uint8_t data = uart_read_blocking();
```

---

### Interrupt Mode

#### Write (Non-blocking)
```c
uart_write(&uart_config, data, len);   // uses TX ring buffer + TXE interrupt
```

#### Read (Non-blocking)
```c
uint8_t data;
if (uart_read(&data))
{
    // data received
}
```

---

## Notes

- No HAL or CubeMX used  
- Circular buffers used for non-blocking communication  
- Supports both polling and interrupt modes  

---

## Author

Arjun V
