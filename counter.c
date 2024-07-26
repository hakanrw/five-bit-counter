/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <stdio.h>
#include <math.h>
#include <pico/stdlib.h>
#include "counter.h"

static const char LEDS[BIT_COUNT] = {LED_1, LED_2, LED_3, LED_4, LED_5};

static signed char counter = 0;
static bool last_button_inc_state = false;
static bool last_button_dec_state = false;

void pins_setup() {
    gpio_init(LED_OVERFLOW);
    gpio_set_dir(LED_OVERFLOW, GPIO_OUT);

    for (char i = 0; i < BIT_COUNT; i++) {
        gpio_init(LEDS[i]);
        gpio_set_dir(LEDS[i], GPIO_OUT);
    }

    gpio_init(BUTTON_INC);
    gpio_init(BUTTON_DEC);
    gpio_set_dir(BUTTON_INC, GPIO_IN);
    gpio_set_dir(BUTTON_DEC, GPIO_IN);
}

void board_loop() {
    signed char value = counter;

    for (char i = 0; i < BIT_COUNT; i++) {
    	bool bit = value & 1; // rightmost bit
    	value >>= 1; // right-shift
        gpio_put(LEDS[i], bit);
    	//printf("LEDS[%d]: %d\n", index, bit);
    }

    bool overflow = counter >= pow(2, BIT_COUNT) || counter < 0;
    gpio_put(LED_OVERFLOW, overflow);

    bool button_inc_state = gpio_get(BUTTON_INC);
    bool button_dec_state = gpio_get(BUTTON_DEC);

    printf("counter: %d\n", counter);

    // increment pressed
    if (button_inc_state && !last_button_inc_state) {
        counter++;
        printf("increment pressed\n");
    }

    // decrement pressed
    if (button_dec_state && !last_button_dec_state) {
        counter--;
        printf("decrement pressed\n");
    }

    last_button_inc_state = button_inc_state;
    last_button_dec_state = button_dec_state;
}

int main() {
    stdio_init_all();
    printf("starting raspberry pico");

    pins_setup();
    while (true) board_loop();
    return 0;
}
