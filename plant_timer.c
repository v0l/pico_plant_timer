#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"

#define RELAY 0
#define LED 25

#define RELAY_ON 0

const uint64_t MS = 1e3;
const uint64_t S = 1e6;
const uint64_t M = 6e7;
const uint64_t H = 36e8;

const uint64_t T_ON = 16 * H;
const uint64_t T_TOTAL = 24 * H;

int main()
{
    stdio_init_all();

    gpio_init(RELAY);
    gpio_init(LED);

    gpio_set_dir(RELAY, GPIO_OUT);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(RELAY, 1);
    gpio_put(LED, 1);

    busy_wait_us(S);
    while (true)
    {
        uint64_t now = time_us_64();

        uint64_t v = now % T_TOTAL;
        if (v < T_ON)
        {
            gpio_put(RELAY, RELAY_ON);
            gpio_put(LED, 1);
        }
        else
        {
            gpio_put(RELAY, !RELAY_ON);
            gpio_put(LED, 0);
        }
        busy_wait_us(S);
    }
    return 0;
}