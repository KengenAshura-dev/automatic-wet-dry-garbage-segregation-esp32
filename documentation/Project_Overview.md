# Project Overview

## Title
Automatic Wet and Dry Garbage Segregation System Using ESP32

## Summary
The project demonstrates a basic automated waste-routing mechanism. An analog moisture sensor provides a measurement to an ESP32. Firmware averages the sensor readings and compares the result with a calibrated threshold. The ESP32 then commands a servo motor to position a flap toward the selected wet or dry collection bin.

## Problem addressed
Separating wet and dry waste manually can be inconvenient. This prototype explores a small embedded automation approach to assist with a first-stage moisture-based separation demonstration.

## Objectives
- Interface an analog sensor with an ESP32 ADC.
- Apply threshold-based classification.
- Control a positional servo using PWM.
- Integrate sensing, decision logic, and mechanical actuation.
- Practice calibration, serial debugging, and embedded-system documentation.

## Scope
The repository documents a student-project design. Actual hardware, wiring, calibration data, mechanical design, and test results must be filled in by the project owner. No hardware test is claimed.
