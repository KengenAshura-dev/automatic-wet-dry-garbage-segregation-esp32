# System Architecture

## Functional blocks

- **Input:** waste item presented to the sensing area.
- **Sensing:** analog moisture sensor.
- **Processing:** ESP32 ADC sampling, averaging, and threshold classification.
- **Actuation:** positional servo motor.
- **Mechanical output:** flap directs the item toward one of two bins.

## Signal flow

`Waste item → Moisture sensor → ESP32 ADC → Classification logic → Servo PWM → Mechanical flap → Wet/Dry bin`

## Software modules

The firmware separates configuration, validation, ADC acquisition, classification, servo movement, routing, and setup/loop orchestration into distinct functions. This makes it easier to explain and modify during a technical interview.
