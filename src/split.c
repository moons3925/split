#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/timer.h"
#include "hardware/uart.h"

#include "spi_ex.h"
#include "uart_ex.h"

#define UART_ID uart1

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

int main()
{
    stdio_init_all();

    spi_ex_init();
    uart_ex_init();

    add_alarm_in_ms(2000, alarm_callback, NULL, false);
    uart_puts(UART_ID, " Hello, UART!\n");
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
