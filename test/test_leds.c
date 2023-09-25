/**
 * @file test_leds.c
 * @author Gonzalo Fernandez
 *
 * @brief Tests unitarios de driver para LEDs
 *
 * - Con la inicializacion todos los LEDs quedan apagados
 * - Prender un LED individual
 * - Apagar un LED individual
 * - Prendo y apago un LED con algunos prendido y otros apagados.
 * - Prender todos los LEDs de una vez
 * - Apagar todos los LEDs de una vez
 * - Consulta el estado de un LED que esta encendido
 * - Consulto el estado de un LED que esta apagado
 * - Revisar limites de los parametros
 * @todo Probar que ocurre cuando el puerto es NULL
 * @todo Probar que ocurre cuando se utiliza una funcion del driver si un previo init
 */

#include <stdint.h>

#include "unity.h"

#include "leds_driver.h"

#define _BV(bit) (1 << bit)

/**
 * @brief Definicion de tipo para manejo de errores
 */
typedef enum {
    ERROR_CLEAR = 0,
    ERROR_RAISE,
} error_status_t;

uint16_t virtual_port; /*!> Puerto virtual para tests unitarios */

error_status_t flag_error; /*!> Flag to be set in the callback and asserted in the tests */

/**
 * @brief Callback to be registered in the driver de LEDs
 */
void leds_error_callback(void) {
    flag_error = ERROR_RAISE;
}

/**
 * @brief Fixture de inicializacion del driver de LEDs
 */
void setUp(void) {
    // error flag clear
    flag_error = ERROR_CLEAR;
    // inicializacion del driver
    leds_init(&virtual_port);
}

/**
 * @brief Con la inicializacion todos los LEDs quedan apagados
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
 * @brief Prender un LED individual
 */
void test_one_led_on(void) {
    // LED a encender
    unsigned int led_test = 5;
    // encendido de led
    leds_turn_on(led_test);
    // chequeo de LEDs apagados excepto el LED encendido
    TEST_ASSERT_BITS_HIGH(_BV(4), virtual_port);
}

/**
 * @brief Apagar un LED individual
 */
void test_one_led_off(void) {
    // led a apagar
    unsigned int led_test = 5;
    // encendido de led
    leds_turn_on(led_test);
    // apagado de led
    leds_turn_off(led_test);
    // chequeo de LEDs apagados
    TEST_ASSERT_BITS_LOW(_BV(4), virtual_port);
}

/**
 * @brief Encender multiples LEDs
 */
void test_multiple_led_on(void) {
    leds_turn_on(5);
    leds_turn_on(3);
    leds_turn_on(3);
    // LED 3 y 5 encendido
    TEST_ASSERT_BITS_HIGH(_BV(4) | _BV(2), virtual_port);
}

/**
 * @brief Apagar multiples LEDs
 */
void test_multiple_led_off(void) {
    leds_turn_on(5);
    leds_turn_on(3);
    leds_turn_off(5);
    leds_turn_off(2);
    // LED 3 y 5 encendido
    TEST_ASSERT_BITS_LOW(_BV(4) | _BV(1), virtual_port);
}

/**
 * @brief Encender todos los LEDs a la vez
 */
void test_all_leds_on(void) {
    leds_turn_on_all();
    // chequear todos los LEDs encendidos
    TEST_ASSERT_BITS_HIGH(0xFFFF, virtual_port);
}

/**
 * @brief Apagar todos los LEDs a la vez
 */
void test_all_leds_off(void) {
    leds_turn_off_all();
    // chequear todos los LEDs apagados
    TEST_ASSERT_BITS_LOW(0xFFFF, virtual_port);
}

/**
 * @brief Consultar el estado de un LED encendido.
 */
void test_request_led_on(void) {
    // encender led 5
    leds_turn_on(5);
    // consultar led 5 y chequear estado alto
    TEST_ASSERT_EQUAL(LED_STATE_HIGH, leds_get_state(5));
}

/**
 * @brief Consultar el estado de un LED apagado.
 */
void test_request_led_off(void) {
    // encender led 5
    leds_turn_off(5);
    // consultar led 5 y chequear estado bajo
    TEST_ASSERT_EQUAL(LED_STATE_LOW, leds_get_state(5));
}

/**
 * @brief Prender LEDs limites
 */
void test_limit_led_on(void) {
    // encendido de led 1 y 16
    leds_turn_on(1);
    leds_turn_on(16);
    // chequeo de leds encendidos
    TEST_ASSERT_BITS_HIGH(_BV(0) | _BV(15), virtual_port);
}

/**
 * @brief Apagar LEDs limites
 */
void test_limit_led_off(void) {
    // apagado de led 1 y 16
    leds_turn_off(1);
    leds_turn_off(16);
    // chequeo de leds apagados
    TEST_ASSERT_BITS_LOW(_BV(0) | _BV(15), virtual_port);
}

/**
 * @brief Consultar el estado de LED limite
 */
void test_request_limit_led_on(void) {
    // encender led 1 y 16
    leds_turn_on(1);
    leds_turn_on(16);
    // consultar led 1 y 16 y chequear estado alto
    TEST_ASSERT_EQUAL(LED_STATE_HIGH, leds_get_state(1));
    TEST_ASSERT_EQUAL(LED_STATE_HIGH, leds_get_state(16));
}

/**
 * @brief Consultar el estado de un LED limite apagado.
 */
void test_request_limit_led_off(void) {
    // apagar led 1 y 16
    leds_turn_off(1);
    leds_turn_off(16);
    // consultar led 1 y 16 y chequear estado bajo
    TEST_ASSERT_EQUAL(LED_STATE_LOW, leds_get_state(1));
    TEST_ASSERT_EQUAL(LED_STATE_LOW, leds_get_state(16));
}

/**
 * @brief Prender LED invalido
 */
void test_invalid_led_on(void) {
    // encendido de led 0 (invalido)
    leds_turn_on(0);
    // chequeo de flag de error
    TEST_ASSERT_EQUAL(ERROR_RAISE, flag_error);
    // clear error flag
    flag_error = ERROR_CLEAR;
    // encendido de led 17 (invalido)
    leds_turn_on(17);
    // chequeo de flag de error
    TEST_ASSERT_EQUAL(ERROR_RAISE, flag_error);
}

/**
 * @brief Apagar LED invalido
 */
void test_invalid_led_off(void) {
    // apagado de led 0 (invalido)
    leds_turn_off(0);
    // chequeo de flag de error
    TEST_ASSERT_EQUAL(ERROR_RAISE, flag_error);
    // clear error flag
    flag_error = ERROR_CLEAR;
    // apagado de led 17 (invalido)
    leds_turn_off(17);
    // chequeo de flag de error
    TEST_ASSERT_EQUAL(ERROR_RAISE, flag_error);
}

/**
 * @brief Consultar el estado de LED invalido
 */
void test_request_invalid_led(void) {
    // consultar led 0 (invalido)
    TEST_ASSERT_EQUAL(LED_STATE_INVALID, leds_get_state(0));
    // clear error flag
    flag_error = ERROR_CLEAR;
    // consultar led 17 (invalido)
    TEST_ASSERT_EQUAL(LED_STATE_INVALID, leds_get_state(17));
}
