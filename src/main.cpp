#include <ESP32Servo.h>

// Create a Servo object to control the ESC
Servo esc;

// Define the GPIO pin connected to the ESC signal wire
// Using GPIO 22 as requested
const int ESC_PIN = 22;

// Standard throttle values in microseconds (µs)
const int NEUTRAL_THROTTLE = 1500;       // Neutral / Stop
const int MAX_FORWARD_THROTTLE = 2000;   // Full forward throttle
const int MAX_REVERSE_THROTTLE = 1000;   // Full reverse throttle

void setup() {
  // Start serial communication for monitoring
  Serial.begin(115200);
  esc.attach(ESC_PIN);
  // Serial.println("Full Guide: Testing ESC WP 1625 with ESP32 on GPIO 22");
  //
  // // Attach the servo object to the specified GPIO pin
  // esc.attach(ESC_PIN, MAX_REVERSE_THROTTLE, MAX_FORWARD_THROTTLE);
  //
  // // == ARMING SEQUENCE ==
  // // According to the manual, the ESC performs auto-calibration
  // // if it detects a neutral signal at startup.
  // Serial.println("Arming ESC: Sending neutral signal (1500µs)...");
  // esc.writeMicroseconds(NEUTRAL_THROTTLE);
  //
  // // Wait 3–4 seconds for ESC self-test and calibration
  // delay(4000);
  // Serial.println("ESC Ready! (You should hear one long beep).");
}

void loop() {
  // Serial.println("\n===== Starting Movement Sequence =====");
  //
  // // --- Forward Movement ---
  // Serial.println("Command: Forward (50% throttle)");
  // esc.writeMicroseconds(1600);
  // delay(3000); // Move forward for 3 seconds
  //
  // // --- Transitioning from Forward to Reverse (Brake Logic) ---
  // // Required for Fwd/Brake/Rev mode
  //
  // // 1. Brake Command: The first reverse signal acts as a brake
  // Serial.println("Command: Brake (Step 1)");
  // esc.writeMicroseconds(1250);
  // delay(1000); // Hold brake
  //
  // // 2. Return to Neutral: ESC must go back to neutral before reversing
  // Serial.println("Command: Neutral (Step 2)");
  // esc.writeMicroseconds(NEUTRAL_THROTTLE);
  // delay(1500);
  //
  // // --- Reverse Movement ---
  // // 3. Reverse Command: Send reverse signal again to move backward
  // Serial.println("Command: Reverse (Step 3)");
  // esc.writeMicroseconds(1250); // 50% reverse speed
  // delay(3000); // Move backward for 3 seconds
  //
  // // --- Full Stop ---
  // Serial.println("Command: Full Stop (Back to Neutral)");
  // esc.writeMicroseconds(NEUTRAL_THROTTLE);
  // delay(5000); // Wait 5 seconds before restarting the sequence
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    esc.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    esc.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}