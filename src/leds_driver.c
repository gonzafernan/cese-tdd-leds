/**
 * @file leds_driver.c
 * @author Gonzalo Fernandez
 * @brief LEDs driver
 */

#include "leds_driver.h"

#define LED_LOGIC_OFFSET 1  /*!> Offset logico de LED id a bit */
#define _BV(bit) (1 << bit) /*!> Utilidad para acceder a bit mediante desplazamiento */
#define LED_LOGIC_TO_BIT(led_id)                                                                   \
    _BV(led_id - LED_LOGIC_OFFSET) /*!> Utilidad para convertir de LED id a LED bit */
#define ALL_LEDS_OFF 0x0000        /*!> Mask para apagar LEDs */
#define ALL_LEDS_ON 0xFFFF         /*!> Mask para encender LEDs */
#define LEDS_MIN_ID 1              /*!> Minimo valor logico para LEDs */
#define LEDS_MAX_ID 16             /*!> Maximo valor logico para LEDs */
#define LEDS_INVALID_ID(led_id) (led_id < LEDS_MIN_ID || led_id > LEDS_MAX_ID)

static uint16_t *reg_port; /*!> Puerto registrado por la funcion de inicializacion del driver */

void leds_init(uint16_t *port) {
    // registro del puerto
    reg_port = port;
    // inicializacion en 0
    *reg_port = ALL_LEDS_OFF;
}

void leds_turn_on(unsigned int led_id) {
    if (LEDS_INVALID_ID(led_id))
        return leds_error_callback();
    *reg_port |= LED_LOGIC_TO_BIT(led_id);
}

void leds_turn_off(unsigned int led_id) {
    if (LEDS_INVALID_ID(led_id))
        return leds_error_callback();
    *reg_port &= ~LED_LOGIC_TO_BIT(led_id);
}

void leds_turn_on_all(void) {
    *reg_port = ALL_LEDS_ON;
}

void leds_turn_off_all(void) {
    *reg_port = ALL_LEDS_OFF;
}

led_state_t leds_get_state(unsigned int led_id) {
    if (LEDS_INVALID_ID(led_id))
        return LED_STATE_INVALID;
    return (*reg_port & LED_LOGIC_TO_BIT(led_id)) ? LED_STATE_HIGH : LED_STATE_LOW;
}

void __attribute__((weak)) leds_error_callback(void) {
    // a definir por el usuario
}
