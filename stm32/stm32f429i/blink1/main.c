#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup() {
    rcc_periph_clock_enable(RCC_GPIOG);

    gpio_mode_setup(
        GPIOG,
        GPIO_MODE_OUTPUT,
        GPIO_PUPD_NONE,
        GPIO13);
}

int main(void) {

    gpio_setup();

    while(1) {
        gpio_toggle(GPIOG, GPIO13);
        for (int i = 0; i < 500000; i++) {
            __asm__("nop");
        }
    }

    return 0;
}
