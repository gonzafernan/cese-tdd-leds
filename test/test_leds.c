/**
 * @file test_leds.c
 * @author Gonzalo Fernandez
 *
 * @todo Al iniciar el driver todos los LEDs deben estar apagados
 * @todo Con todos los LEDs apagados prendo un LED en particular.
 * @todo Apago un LED prendido
 * @todo Prendo y apago un LED con algunos prendido y otros apagados.
 * @todo Consulto el estado de un LED prendido.
 * @todo Consulto el estado de un LED apagado
 * @todo Con todos los LEDs apagados prendo todos
 * @todo Con todos los LED prendidos apago todos
 * @todo Probar LED 1 y LED 16.
 * @todo Probar fuera de los límiter
 */

#include <stdint.h>

#include "unity.h"

#include "leds_driver.h"

/**
 * @brief Todos los LEDs deben estar apagados al inicializar el driver
 */
void test_leds_init(void) {
    uint16_t virtual_port = 0xFFFF;
    leds_init(&virtual_port);
    TEST_ASSERT_EQUAL(0, virtual_port);
}
