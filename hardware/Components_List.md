# Components List


| Item | Suggested common component | Purpose | Verification needed |
|---|---|---|---|
| 1 | ESP32 DevKit V1 | Main controller | Confirm exact board/module |
| 2 | Analog capacitive moisture sensor | Moisture-responsive analog signal | Confirm sensor model, supply range, AO range |
| 3 | SG90 positional servo | Moves the sorting flap | Confirm torque is sufficient |
| 4 | Regulated 5 V supply for servo | Servo power | Confirm current capacity from servo datasheet/load |
| 5 | Jumper wires / breadboard | Prototyping connections | Confirm wire and connector security |
| 6 | Mechanical flap and two bins | Directs waste into wet/dry collection | Design and dimensions are build-specific |
| 7 | USB data cable | ESP32 programming and power | Confirm data capability |

## Electrical cautions

- ESP32 GPIO and ADC inputs are not 5 V tolerant.
- Do not connect a sensor output to an ESP32 ADC pin until its maximum voltage is known.
- A servo can draw current spikes. Use a suitable external regulated supply.
- Connect the servo supply ground and ESP32 ground together for a common signal reference.
- Verify all module pin labels and datasheets before powering the circuit.
