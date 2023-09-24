/**
 * @file test_leds.c
 * @author Gonzalo Fernandez
 *
 * Al iniciar el driver todos los LEDs deben estar apagados
 * @todo Con todos los LEDs apagados prendo un LED en particular.
 * @todo Apago un LED prendido
 * @todo Prendo y apago un LED con algunos prendido y otros apagados.
 * @todo Consulto el estado de un LED prendido.
 * @todo Consulto el estado de un LED apagado
 * @todo Con todos los LEDs apagados prendo todos
 * @todo Con todos los LED prendidos apago todos
 * @todo Probar LED 1 y LED 16.
 * @todo Probar fuera de los límiter
 * @todo Probar que ocurre cuando el puerto es NULL
 * @todo Probar que ocurre cuando se utiliza una funcion del driver si un previo init
 */

#include <stdint.h>

#include "unity.h"

#include "leds_driver.h"

uint16_t virtual_port; /*!> Puerto virtual para tests unitarios */

/**
 * @brief Fixture de inicializacion del driver de LEDs
 */
void setUp(void) {
    // inicializacion del driver
    leds_init(&virtual_port);
}

/**
 * @brief Todos los LEDs deben estar apagados al inicializar el driver
 */
void test_leds_init(void) {
    // simulacion de puerto no inicializado
    uint16_t virtual_port = 0xFFFF;
    // inicializacion del driver
    leds_init(&virtual_port);
    // chequeo de LEDs apagados
    TEST_ASSERT_EQUAL(0x0000, virtual_port);
}

/**
 * @brief Encendido de un LED particular
 */
void test_one_led_on(void) {
    // LED a encender
    unsigned int led_test = 5;
    // encendido de led
    leds_turn_on(led_test);
    // chequeo de LEDs apagados excepto el LED encendido
    uint16_t mask = (1 << (led_test - 1));
    TEST_ASSERT_BITS_HIGH(mask, virtual_port);
}

/**
 * @brief Apagado de un LED particular
 */
void test_one_led_off(void) {
    // LED a encender
    unsigned int led_test = 5;
    // encendido de led
    leds_turn_on(led_test);
    // apagado de led
    leds_turn_off(led_test);
    // chequeo de LEDs apagados
    uint16_t mask = ~(1 << (led_test - 1));
    TEST_ASSERT_BITS_LOW(mask, virtual_port);
}
