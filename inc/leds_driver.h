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
 * @brief Inicializacion del driver
 * @param port  Puerto de los LEDs (direccion de memoria de 16 bits)
 */
void leds_init(uint16_t *port);

#ifdef __cplusplus
}
#endif

#endif /* LEDS_DRIVER_H */
