/**
 * @file leds_driver.c
 * @author Gonzalo Fernandez
 * @brief LEDs driver
 */

#include "leds_driver.h"

#define LED_LOGIC_OFFSET 1
#define _BV(bit) (1 << bit)
#define LED_LOGIC_TO_BIT(led_id) _BV(led_id - LED_LOGIC_OFFSET)

static uint16_t *reg_port; /*!> Puerto registrado por la funcion de inicializacion del driver */

void leds_init(uint16_t *port) {
    // inicializacion en 0
    *port = 0;
    // registro del puerto
    reg_port = port;
}

void leds_turn_on(unsigned int led_id) {
    *reg_port |= LED_LOGIC_TO_BIT(led_id);
}

void leds_turn_off(unsigned int led_id) {
    *reg_port &= ~LED_LOGIC_TO_BIT(led_id);
}
