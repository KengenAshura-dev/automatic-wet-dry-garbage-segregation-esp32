# Circuit Connections

## Status

Use the connection table below as the circuit wiring reference. Confirm module pin labels, voltage ratings, and board pinout during assembly.

## Circuit connection table

| Module terminal | Illustrative connection | Status |
|---|---|---|
| Moisture sensor VCC | Sensor supply supported by its datasheet | Must verify |
| Moisture sensor GND | ESP32 GND | Must verify |
| Moisture sensor AO | ESP32 GPIO34 through suitable level protection if needed | Must verify voltage safety |
| Servo signal | ESP32 GPIO18 | Illustrative firmware default |
| Servo V+ | Regulated external 5 V supply | Confirm servo rating/current |
| Servo GND | External supply GND and ESP32 GND | Common ground required for non-isolated signal |

## Before connecting power

1. Identify the exact sensor board and its allowed supply voltage.
2. Measure or confirm the maximum AO voltage. It must remain within the ESP32 ADC input limits.
3. Confirm servo voltage and current requirements from its datasheet.
4. Use a regulated supply capable of handling servo startup/stall current.
5. Join grounds between the servo supply and ESP32.
6. Check for short circuits and mechanical obstruction.
7. Test the servo with the flap disconnected before attaching the mechanism.

Do not infer that a 5 V sensor supply makes its analog output safe for an ESP32. Use a suitable voltage divider or other level-conditioning circuit if required by the measured output.
