---
autor: Gonzalo G. Fernandez
materia: Testing de Software en Sistemas Embebidos
---

# Driver LEDs

## Requerimientos

- Maneja 16 LEDs de dos estados (encendido y apagado).
- Se puede cambiar el estado de un LED sin afectar a los otros.
- Se puede cambiar el estado de todos los LEDs en una sola operación.
- Se puede recuperar el estado actual de un LED.
- Los LEDs están mapeados en una palabra de 16 bits en memoria en una dirección a determinar.
- Para encender el LED se debe escribir un "1" en el bit y para apagarlo se debe escribir un "0".
- El LED 1 corresponde al LSB y el LED 16 al MSB.
- El reset de hardware no define un estado conocido de los LEDs, estos deben ser apagados por software.

## Tests unitarios

- Al iniciar el driver todos los LEDs deben estar apagados.
- Con todos los LEDs apagados prendo un LED en particular.
- Apago un LED prendido
- Prendo y apago un LED con algunos prendido y otros apagados.
- Consulto el estado de un LED prendido.
- Consulto el estado de un LED apagado
- Con todos los LEDs apagados prendo todos
- Con todos los LED prendidos apago todos
- Probar LED 1 y LED 16.
- Probar fuera de los límiter
