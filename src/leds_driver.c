/**
 * @file leds_driver.c
 * @author Gonzalo Fernandez
 * @brief LEDs driver
 */

#include "leds_driver.h"

static uint16_t *reg_port; /*!> Puerto registrado por la funcion de inicializacion del driver */

void leds_init(uint16_t *port) {
    // inicializacion en 0
    *port = 0;
    // registro del puerto
    reg_port = port;
}

void leds_turn_on(unsigned int led_id) {
    *reg_port |= (1 << 4);
}
