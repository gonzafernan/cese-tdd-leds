/**
 * @file leds_driver.c
 * @author Gonzalo Fernandez
 * @brief LEDs driver
 */

#include "leds_driver.h"

void leds_init(uint16_t *port) {
    // inicializacion en 0
    *port = 0x0000;
}
