#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>

#include "utils.h"

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName);


void vApplicationStackOverflowHook(
    xTaskHandle *pxTask __attribute((unused)),
    signed portCHAR *pcTaskName __attribute((unused))) {

    while(true) {
        gpio_toggle(GPIOG, GPIO13);
    }
}

void clock_setup(void) {
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	systick_set_reload(168000); // 168 MHz 1 ms
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB); // source selection
	systick_counter_enable();

	systick_interrupt_enable();
}

static void gpio_setup() {
    rcc_periph_clock_enable(RCC_GPIOG);

    gpio_mode_setup(
        GPIOG,
        GPIO_MODE_OUTPUT,
        GPIO_PUPD_NONE,
        GPIO13);

    gpio_mode_setup(
        GPIOG,
        GPIO_MODE_OUTPUT,
        GPIO_PUPD_NONE,
        GPIO14);
}



void uart_setup() {
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART1);

    gpio_mode_setup(
        GPIOA,
        GPIO_MODE_AF,
        GPIO_PUPD_NONE,
        GPIO9);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO9);
    usart_set_baudrate(USART1, 19200);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_enable(USART1);
}

static void task1(void * args __attribute((unused))) {
    while(true) {
        gpio_toggle(GPIOG, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void task2(void * args __attribute((unused))) {
    while(true) {
        gpio_toggle(GPIOG, GPIO14);
        vTaskDelay(pdMS_TO_TICKS(30));

        gpio_toggle(GPIOG, GPIO14);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void task3(void * args __attribute((unused))) {
    uint32_t start = 0x8000000;
    uint32_t address = start;
    uint8_t line[16];

    line[8] = ' ';
    line[11] = '\n';
    line[12] = '\r';
    line[13] = 0;

    while (true) {
        uint32_to_hex(address, line);
        uint8_to_hex(*(uint8_t*)address, &line[9]);
        usart_puts(USART1, line);
        vTaskDelay(pdMS_TO_TICKS(100));
        address++;
        if (address > start + 0x1000) {
            address = start;
        }
    }

}

int main(void) {

    clock_setup();
    gpio_setup();
    uart_setup();

    xTaskCreate(task1, "LED13", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(task2, "LED14", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(task3, "UART1", 100, NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler();

    while (true) {
      gpio_toggle(GPIOG, GPIO13);
    }

    return 0;
}


