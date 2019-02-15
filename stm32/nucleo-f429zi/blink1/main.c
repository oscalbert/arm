#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup() {
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_mode_setup( GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);
    gpio_mode_setup( GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
    gpio_mode_setup( GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
}

int main(void) {
    int counter = 0;
    gpio_setup();

    while(1) {
        switch (counter++%3) {
            case 0:
                gpio_toggle(GPIOB, GPIO0);
                break;
            case 1:
                gpio_toggle(GPIOB, GPIO7);
                break;
            case 2:
                gpio_toggle(GPIOB, GPIO14);
                break;
            default:
                break;
        }

        for (int i = 0; i < 200000; i++) {
            __asm__("nop");
        }
    }

    return 0;
}
