# Pin Configuration

## Pin assignments

The following pin assignments are used by the firmware.

| Function | Example ESP32 pin | Firmware constant | Notes |
|---|---:|---|---|
| Moisture sensor analog output (AO) | GPIO34 | `MOISTURE_SENSOR_PIN` | ADC1 input-only pin on common ESP32 DevKit V1; confirm board variant |
| Servo signal | GPIO18 | `SERVO_SIGNAL_PIN` | PWM-capable GPIO on common ESP32 DevKit V1 |

## Values requiring calibration

| Setting | Example value | Required action |
|---|---:|---|
| ADC resolution | 12 bit | Confirm supported Arduino-ESP32 core |
| ADC attenuation | 11 dB | Check actual sensor output range and ADC behavior |
| Moisture threshold | 2000 | Replace with measured threshold |
| Wet polarity | Below threshold | Measure dry and wet sample readings |
| Neutral servo angle | 90° | Adjust to mechanical center |
| Wet servo angle | 45° | Verify bin alignment and safe travel |
| Dry servo angle | 135° | Verify bin alignment and safe travel |

Edit the constants at the beginning of `ESP32_Garbage_Segregation.ino`.

## Pin selection cautions

- Avoid ESP32 boot-strapping pins unless you understand their boot-state requirements.
- GPIO34 is input-only and cannot drive a servo.
- Use an ADC1 pin for analog sensing when Wi-Fi may be enabled in future versions.
- Confirm the exact ESP32 module pinout; board variants are not interchangeable in every detail.
