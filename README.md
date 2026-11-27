# Automatic Wet and Dry Garbage Segregation System (ESP32)

A college-level, physical-hardware prototype that classifies waste using a moisture sensor and moves a servo-operated flap to direct the item into a wet or dry bin.

> This repository documents a commonly used student-project setup: an ESP32 DevKit V1, an analog capacitive moisture sensor, and an SG90 servo. Confirm the pin assignments against the assembled circuit and calibrate the sensor and flap positions before operation.

## Problem statement

Manual separation of wet and dry waste is inconvenient and can expose people to unsanitary material. A small automated demonstrator can show how a sensor, microcontroller, and actuator work together to perform a basic first-stage separation.

## Objectives

- Read an analog moisture-sensor signal using the ESP32 ADC.
- Classify a detected item using a calibrated threshold.
- Drive a servo-operated flap toward the selected collection bin.
- Return the flap to its neutral position after the transfer interval.
- Provide serial diagnostics to support calibration and debugging.

## Features

- Configurable GPIO assignments, ADC resolution, threshold, polarity, servo angles, and timings.
- Averaged sensor samples to reduce short-term noise.
- Threshold-based wet/dry decision.
- Serial Monitor messages for raw and averaged ADC values and decisions.
- Servo movement sequence with a neutral return position.

This prototype demonstrates moisture-based waste routing. It estimates moisture from the sensor response; it does not identify the material composition.

## Hardware components

| Component | Baseline choice | Notes |
|---|---|---|
| Controller | ESP32 DevKit V1 | Board variants may have different pin labels |
| Moisture sensor | Analog capacitive moisture sensor | Use its analog output (AO); verify output voltage is ESP32-safe |
| Actuator | SG90 positional servo | Confirm mechanical load is within servo capability |
| Servo supply | Regulated external 5 V supply | Size supply for servo current; do not assume the ESP32 3.3 V pin can power it |
| Wiring | Jumper wires / breadboard | Secure connections for moving parts |
| Collection bins and flap | Mechanical assembly | Dimensions and geometry are project-specific |
| USB cable | Data-capable USB cable | For programming and serial monitoring |

The listed components cover the sensing, processing, and actuation functions. Add other components only if they are included in the implemented design.

## Software requirements

- Arduino IDE 2.x (or compatible Arduino IDE)
- ESP32 board support package by Espressif Systems
- `ESP32Servo` library
- USB serial driver appropriate for the ESP32 board's USB-to-UART bridge

## System architecture

```text
Waste item
   |
   v
Analog moisture sensor --> ESP32 ADC --> Threshold classification
                                            |
                                            v
                                      Servo control
                                            |
                                            v
                                     Mechanical flap
                                      /          \
                                  Wet bin      Dry bin
```

See [`documentation/Block_Diagram.png`](documentation/Block_Diagram.png) and [`documentation/Flowchart.png`](documentation/Flowchart.png).

## Working principle

1. Place one item in the sensing area according to the mechanical design.
2. The analog moisture sensor produces a voltage representing its response to the nearby/contacting material.
3. The ESP32 samples the analog output and averages multiple readings.
4. Firmware compares the average with a calibrated threshold and configured polarity.
5. The servo moves the flap to the configured wet or dry position.
6. After the configured transfer delay, the servo returns to its neutral position.

The exact sensor response depends on sensor type, placement, contact pressure, material, and moisture. Calibrate with representative samples from your intended demonstration.

## Circuit connections

**Illustrative connections only — verify your exact board and modules before wiring.** The baseline pin assignments are in [`hardware/Pin_Configuration.md`](hardware/Pin_Configuration.md). A dedicated hardware connection diagram is deliberately not included because no physical prototype wiring has been verified.

Important electrical notes:
- ESP32 GPIOs are **not 5 V tolerant**. Ensure the sensor AO voltage never exceeds the ESP32 ADC input limit. If the sensor board is powered from 5 V and AO can rise above the safe input range, use a suitable voltage divider or power the sensor at a compatible voltage if its datasheet permits.
- Power the servo from a suitable regulated 5 V supply, not from the ESP32 3.3 V output.
- Connect the external servo supply ground to ESP32 GND (common ground), unless the servo driver/interface design explicitly provides isolation.
- Connect servo signal to the configured GPIO.
- Check the sensor module's pin labels and supply-voltage range before connecting it.

## Arduino IDE setup

1. Install Arduino IDE 2.x.
2. Open **File → Preferences** and add Espressif's official ESP32 boards-manager URL if it is not already configured.
3. Open **Tools → Board → Boards Manager**, search for `esp32`, and install **esp32 by Espressif Systems**.
4. Open **Sketch → Include Library → Manage Libraries**, search for `ESP32Servo`, and install it.
5. Open `firmware/ESP32_Garbage_Segregation/ESP32_Garbage_Segregation.ino`.
6. Select the matching ESP32 board and serial port.

## Firmware upload procedure

1. Review `hardware/Pin_Configuration.md` and change the constants near the top of the sketch to match your actual wiring.
2. Confirm the sensor output voltage is safe for the ESP32 ADC.
3. Connect the ESP32 over USB.
4. Select the correct board and port in Arduino IDE.
5. Click **Verify** to compile, then **Upload**.
6. Open Serial Monitor at **115200 baud**.
7. Test the sensor and servo separately with the mechanism unloaded before attempting a full demonstration.

## Calibration instructions

1. Set `CALIBRATION_ONLY` to `true` in the firmware and upload.
2. Open Serial Monitor at 115200 baud.
3. Record averaged readings for several representative dry samples and wet samples using the same sensor placement.
4. Compare the ranges. Choose a threshold between the observed groups only if the ranges are sufficiently separated.
5. Set `MOISTURE_THRESHOLD_RAW` to the chosen value.
6. Set `WET_WHEN_READING_BELOW_THRESHOLD` according to the measured direction of response. Some modules produce higher readings when wet; others may produce lower readings.
7. Set `CALIBRATION_ONLY` back to `false`, upload, and test repeatedly.
8. If wet and dry ranges overlap, do not claim reliable classification. Improve sensing geometry or use a more suitable sensor.

The initial threshold in the sketch is a placeholder and must not be treated as a measured calibration result.

## Testing procedure

- **Power-off inspection:** check polarity, wiring, mechanical clearance, and common ground.
- **ADC-only test:** run calibration mode and observe readings without moving the servo.
- **Servo-only test:** verify neutral, wet, and dry positions with the flap disconnected or unloaded. Adjust angles to avoid binding.
- **Classification test:** use known dry and wet samples and compare results against your calibration notes.
- **Integrated test:** test one item at a time, ensuring the flap has enough time to move and return.
- **Repeatability:** repeat multiple trials and document misclassifications. Do not report results that were not actually measured.

## Expected operation

After a valid sensor reading is taken, the serial monitor reports the averaged ADC value and the selected category. The servo moves to the corresponding configured position, waits for the transfer interval, and returns to neutral. Actual mechanical routing depends on the assembled flap geometry and calibrated servo positions.

## Limitations

- Moisture alone is not a complete measure of whether an item is biodegradable, recyclable, or safe.
- Surface moisture, sensor contact, contamination, and material composition can affect readings.
- A single threshold may not classify mixed or borderline waste reliably.
- The baseline design has no item-presence detection, jam detection, bin-full detection, or emergency-stop hardware.
- The servo may not provide sufficient torque for a heavy or poorly balanced flap.
- Hardware performance depends on calibration, sensor placement, and the mechanical assembly.

## Future scope

- Add item-presence sensing after selecting and validating a suitable sensor.
- Add a mechanical jam-detection or limit-switch arrangement.
- Log classification counts and calibration data.
- Improve the classifier using multiple measurements and a defined test dataset.
- Add a suitable enclosure, guarded moving parts, and safer service access.
- Evaluate higher-torque actuators if the measured mechanical load requires them.

## Applications

- Educational demonstrations of embedded sensing and actuation.
- Mini-projects for learning ESP32 ADC, threshold logic, PWM servo control, and system integration.
- Proof-of-concept waste sorting demonstrations under supervised conditions.

## Repository structure

```text
Automatic-Garbage-Segregation-ESP32/
├── README.md
├── LICENSE
├── .gitignore
├── firmware/
│   └── ESP32_Garbage_Segregation/
│       └── ESP32_Garbage_Segregation.ino
├── hardware/
│   ├── Components_List.md
│   ├── Circuit_Connections.md
│   └── Pin_Configuration.md
├── documentation/
│   ├── Project_Overview.md
│   ├── Working_Principle.md
│   ├── System_Architecture.md
│   ├── Project_Report.md
│   ├── Block_Diagram.png
│   └── Flowchart.png
└── images/
    └── README.md
```

## Author / contributors

- **Author:** [Manish Patil]
- **Institution:** [College / University]
- **Department:** [Electronics and Telecommunications Engineering]
- **Academic year:** [2024-2025]

## License


