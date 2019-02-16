#include <libopencm3/stm32/usart.h>

#include "utils.h"


static uint8_t nibble_rep(uint8_t nibble) {
    if (nibble < 10) {
        return '0' + nibble;
    }
    else if (nibble < 16) {
        return 'a' + nibble - 10;
    }
    return '?';
}

void uint8_to_hex(uint8_t value, uint8_t rep[]) {
    rep[0] = nibble_rep(value / 16);
    rep[1] = nibble_rep(value % 16);
}

void uint32_to_hex(uint32_t value, uint8_t rep[]) {
    uint8_to_hex(value >> 24 & 0xff, &rep[0]);
    uint8_to_hex(value >> 16 & 0xff, &rep[2]);
    uint8_to_hex(value >>  8 & 0xff, &rep[4]);
    uint8_to_hex(value >>  0 & 0xff, &rep[6]);
}

void usart_puts(uint32_t usart, uint8_t *str) {
    while (*str) {
        usart_send_blocking(usart, *str);
        str++;
    }
}

