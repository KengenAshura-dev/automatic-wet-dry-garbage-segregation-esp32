/*
 * Project : Automatic Wet and Dry Garbage Segregation System
 * Board   : ESP32 DevKit V1
 * Sensor  : Analog moisture sensor (AO)
 * Actuator: SG90 positional servo
 *
 * Configure the pin assignments and operating parameters for the
 * assembled hardware. Calibrate the sensor before normal operation.
 *
 * Required library: ESP32Servo
 */

#include <Arduino.h>
#include <ESP32Servo.h>

// ------------------------- USER CONFIGURATION -------------------------

// GPIO assignments.
// GPIO34 is an input-only ADC1 pin on the common ESP32 DevKit V1.
constexpr int MOISTURE_SENSOR_PIN = 34;
constexpr int SERVO_SIGNAL_PIN = 18;

// ESP32 ADC configuration.
constexpr uint8_t ADC_RESOLUTION_BITS = 12;  // Typical raw range: 0..4095
constexpr int ADC_ATTENUATION_DB = 11;       // Arduino-ESP32 API attenuation

// Set this value using the sensor calibration procedure.
constexpr int MOISTURE_THRESHOLD_RAW = 2000;

// true: an average below the threshold is classified as wet.
// false: an average above the threshold is classified as wet.
// Select the direction that matches the sensor response.
constexpr bool WET_WHEN_READING_BELOW_THRESHOLD = true;

// Servo positions; adjust to match the flap mechanism.
// Adjust carefully with the flap disconnected or unloaded.
constexpr int SERVO_NEUTRAL_ANGLE = 90;
constexpr int SERVO_WET_ANGLE = 45;
constexpr int SERVO_DRY_ANGLE = 135;

// Timing and sampling configuration.
constexpr uint8_t SENSOR_SAMPLE_COUNT = 10;
constexpr uint16_t SAMPLE_INTERVAL_MS = 20;
constexpr uint16_t FLAP_TRANSFER_TIME_MS = 1200;
constexpr uint16_t SERVO_SETTLE_TIME_MS = 500;

// Set true to print calibration readings without actuating the servo.
constexpr bool CALIBRATION_ONLY = false;

// Servo pulse range is a common starting range; verify for your servo.
constexpr int SERVO_MIN_PULSE_US = 500;
constexpr int SERVO_MAX_PULSE_US = 2400;

// ---------------------------------------------------------------------

Servo sortingServo;
bool servoReady = false;

enum WasteCategory {
  WASTE_WET,
  WASTE_DRY
};

bool isValidAngle(int angle) {
  return angle >= 0 && angle <= 180;
}

bool validateConfiguration() {
  if (MOISTURE_SENSOR_PIN < 0 || SERVO_SIGNAL_PIN < 0) {
    Serial.println("[CONFIG ERROR] GPIO numbers must be non-negative.");
    return false;
  }

  if (!isValidAngle(SERVO_NEUTRAL_ANGLE) ||
      !isValidAngle(SERVO_WET_ANGLE) ||
      !isValidAngle(SERVO_DRY_ANGLE)) {
    Serial.println("[CONFIG ERROR] Servo angles must be between 0 and 180.");
    return false;
  }

  if (MOISTURE_THRESHOLD_RAW < 0 ||
      MOISTURE_THRESHOLD_RAW > ((1 << ADC_RESOLUTION_BITS) - 1)) {
    Serial.println("[CONFIG ERROR] Threshold is outside configured ADC range.");
    return false;
  }

  if (SENSOR_SAMPLE_COUNT == 0) {
    Serial.println("[CONFIG ERROR] SENSOR_SAMPLE_COUNT cannot be zero.");
    return false;
  }

  return true;
}

int readMoistureAverage() {
  uint32_t total = 0;

  for (uint8_t i = 0; i < SENSOR_SAMPLE_COUNT; ++i) {
    total += static_cast<uint32_t>(analogRead(MOISTURE_SENSOR_PIN));
    delay(SAMPLE_INTERVAL_MS);
  }

  return static_cast<int>(total / SENSOR_SAMPLE_COUNT);
}

WasteCategory classifyWaste(int averageRaw) {
  const bool readingIsBelowThreshold = averageRaw < MOISTURE_THRESHOLD_RAW;
  const bool isWet = (readingIsBelowThreshold == WET_WHEN_READING_BELOW_THRESHOLD);
  return isWet ? WASTE_WET : WASTE_DRY;
}

void moveServoTo(int angle) {
  if (!servoReady) {
    Serial.println("[SERVO ERROR] Servo is not initialized.");
    return;
  }

  if (!isValidAngle(angle)) {
    Serial.println("[SERVO ERROR] Refusing invalid angle.");
    return;
  }

  sortingServo.write(angle);
  delay(SERVO_SETTLE_TIME_MS);
}

void routeWaste(WasteCategory category) {
  const int targetAngle =
      (category == WASTE_WET) ? SERVO_WET_ANGLE : SERVO_DRY_ANGLE;

  Serial.print("[ACTION] Routing ");
  Serial.println(category == WASTE_WET ? "WET waste" : "DRY waste");

  moveServoTo(targetAngle);
  delay(FLAP_TRANSFER_TIME_MS);

  Serial.println("[ACTION] Returning flap to neutral position.");
  moveServoTo(SERVO_NEUTRAL_ANGLE);
}

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println();
  Serial.println("==============================================");
  Serial.println(" ESP32 Automatic Wet/Dry Garbage Segregation ");
  Serial.println("==============================================");

  if (!validateConfiguration()) {
    Serial.println("[FATAL] Correct configuration and restart.");
    while (true) {
      delay(1000);
    }
  }

  analogReadResolution(ADC_RESOLUTION_BITS);
  analogSetPinAttenuation(MOISTURE_SENSOR_PIN, ADC_11db);

  pinMode(MOISTURE_SENSOR_PIN, INPUT);

  if (!CALIBRATION_ONLY) {
    sortingServo.setPeriodHertz(50);
    sortingServo.attach(
        SERVO_SIGNAL_PIN, SERVO_MIN_PULSE_US, SERVO_MAX_PULSE_US);

    servoReady = sortingServo.attached();
    if (!servoReady) {
      Serial.println("[FATAL] Servo attach failed. Check pin and library.");
      while (true) {
        delay(1000);
      }
    }

    moveServoTo(SERVO_NEUTRAL_ANGLE);
  } else {
    Serial.println("[MODE] Calibration-only: servo will not move.");
  }

  Serial.println("[INFO] Ready. Place one sample in the sensing area.");
  Serial.println("[INFO] Confirm the moisture threshold through calibration.");
}

void loop() {
  const int averageRaw = readMoistureAverage();

  Serial.print("[SENSOR] Averaged ADC raw value: ");
  Serial.println(averageRaw);

  if (CALIBRATION_ONLY) {
    Serial.println("[CALIBRATION] Record readings for dry and wet samples.");
    delay(1000);
    return;
  }

  const WasteCategory category = classifyWaste(averageRaw);

  Serial.print("[CLASSIFICATION] ");
  Serial.println(category == WASTE_WET ? "WET" : "DRY");

  routeWaste(category);

  // Pause between items. Adjust to suit the physical mechanism.
  delay(500);
}
