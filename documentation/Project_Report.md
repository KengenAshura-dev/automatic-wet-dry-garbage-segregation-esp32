 # Project Report: Automatic Wet and Dry Garbage Segregation System Using ESP32

## Abstract
This project presents a student-level embedded prototype concept for moisture-based separation of wet and dry waste. An analog moisture sensor supplies a signal to an ESP32 microcontroller. The firmware samples and averages the signal, compares it with a calibrated threshold, and controls a servo-operated flap to route the item toward one of two collection bins.

## 1. Introduction
Waste segregation is an important step in waste handling. The project demonstrates how a microcontroller, sensor, and actuator can be integrated to automate a simple sorting action.

## 2. Problem Statement
Manual wet/dry separation can be inconvenient and may be inconsistent. A compact demonstrator can help students understand how embedded sensing and actuation can support a basic sorting process.

## 3. Objectives
- Interface a moisture sensor with an ESP32.
- Read analog sensor data using the ADC.
- Classify readings using a calibrated threshold.
- Control a servo-operated flap.
- Document the design and provide a repeatable test procedure.

## 4. Proposed Hardware
The project configuration uses an ESP32 DevKit V1, an analog capacitive moisture sensor, an SG90 servo, a regulated servo supply, wiring, a mechanical flap, and two bins. Confirm the selected component models and ratings before assembly.

## 5. Methodology
The sensor output is sampled several times and averaged. The average is compared against a threshold established through calibration. A configurable polarity option determines the wet classification direction. The servo moves to the corresponding position, waits for the item-transfer interval, and returns to neutral.

## 6. Software
The firmware is written for the Arduino framework on ESP32 and uses the ESP32Servo library. Serial output supports calibration and debugging.

## 7. Calibration and Testing
Calibration should record dry and wet sample readings under consistent sensor placement. The threshold should be selected from observed data only when the groups are sufficiently separated. Testing should cover ADC acquisition, servo travel, classification, and integrated routing.

## 8. Results
**No experimental results are included in this repository.** Add only results measured on the completed hardware, including test conditions, sample count, observed ADC ranges, threshold, and misclassification count.

## 9. Limitations
Moisture sensing alone cannot identify material composition or recyclability. Surface moisture, sensor placement, mixed waste, and mechanical constraints can affect operation. The baseline has no item-presence, jam, or bin-full detection.

## 10. Future Scope
Possible extensions include item-presence detection, bin-full sensing, jam detection, data logging, improved classification, and a mechanically guarded enclosure. Any added hardware should be documented and validated.

## 11. Conclusion
The project provides an educational example of an embedded sensing-and-actuation chain using ESP32. Reliable operation depends on correct electrical interfacing, sensor calibration, and mechanical tuning.

## Author Details
- Name: [Manish Patil]
- Department: [Electronics and Telecommunications Engineering]
- Institute: [Amrutvahini College Of Engineering]
- Academic Year: [2024-2025]
