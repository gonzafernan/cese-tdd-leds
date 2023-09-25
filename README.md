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
- Con la inicializacion todos los LEDs quedan apagados
- Prender un LED individual
- Apagar un LED individual
- Prendo y apago un LED con algunos prendido y otros apagados.
- Prender todos los LEDs de una vez
- Apagar todos los LEDs de una vez
- Consulta el estado de un LED que esta encendido
- Consulto el estado de un LED que esta apagado
- Revisar limites de los parametros

## Setup de entorno de trabajo

Para configurar pre-commit:

```sh
$ pre-commit install
```

Para ejecutar la suite de test unitarios:

```sh
$ ceedling
```
