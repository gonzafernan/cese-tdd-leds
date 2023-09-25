/**
 * @file leds_driver.h
 * @author Gonzalo Fernandez
 * @brief LEDs driver header
 */

#ifndef LEDS_DRIVER_H
#define LEDS_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Definicion de tipo para estado de LED
 */
typedef enum {
    LED_STATE_LOW = 0,
    LED_STATE_HIGH,
    LED_STATE_INVALID,
} led_state_t;

/**
 * @brief Inicializacion del driver
 * @param port  Puerto de los LEDs (direccion de memoria de 16 bits)
 */
void leds_init(uint16_t *port);

/**
 * @brief Encendido de LED unico
 * @param led_id Numero logico de LED
 */
void leds_turn_on(unsigned int led_id);

/**
 * @brief Apagado de LED unico
 * @param led_id Numero logico de LED
 */
void leds_turn_off(unsigned int led_id);

/**
 * @brief Encener todos los LEDs
 */
void leds_turn_on_all(void);

/**
 * @brief Apagar todos los LEDs
 */
void leds_turn_off_all(void);

/**
 * @brief Consultar estado de LED
 * @param led_id Numero logico de LED a consultar
 * @retval led_state_t
 */
led_state_t leds_get_state(unsigned int led_id);

/**
 * @brief Callback ante error (a definir por el usuario)
 */
void leds_error_callback(void);

#ifdef __cplusplus
}
#endif

#endif /* LEDS_DRIVER_H */
