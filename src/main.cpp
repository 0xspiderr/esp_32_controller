#include <Arduino.h>
#include <DHT.h>
#include <ESP32Servo.h>

#include "../lib/networking/networking.h"

// pin definitions

const int ESC_PIN = 26;
const int SERVO_PIN = 27;
const int DHT11_PIN = 33;

Servo esc;
Servo servo;

DHT dht11(DHT11_PIN, DHT11);

String sensorData = "";

void setup() {
    Serial.begin(115200);
	// wait for serial to initialize
	while (!Serial);

	init_wifi();
	init_esp_now();
    dht11.begin();

    //attach ESC
    esc.attach(ESC_PIN, 1000, 2000); // min, max
    servo.attach(SERVO_PIN, 1000, 1400);
    delay(2000);

    //send neutral for 3+ seconds (initialization)
    esc.writeMicroseconds(1500);
    servo.writeMicroseconds(1200);

    delay(4000);

    Serial.println("ESC and Servo initialized. Ready for commands.");
}

//function to enable reverse mode on ESC

void armReverseMode() {
    Serial.println("Arming reverse mode...");
    esc.writeMicroseconds(1500); // Neutral
    delay(500);
    esc.writeMicroseconds(1380); // Quick backward pulse
    delay(100);
    esc.writeMicroseconds(1500); // Back to neutral
    delay(500);
}

void loop() {
    //DHT11 CODE START

    // humidity
    float humi = dht11.readHumidity();
    // temperature
    float tempC = dht11.readTemperature();

    // check reading successful or not
    if (isnan(tempC) || isnan(humi)) {
        sensorData = "Failed to read from DHT11 sensor!";
        Serial.println(sensorData);
    } else {
        // print to serial
        Serial.print("humidity: ");
        Serial.print(humi);
        Serial.print("%");
        Serial.print("...");
        Serial.print("temp: ");
        Serial.print(tempC);
        Serial.println("degrees C");
    }

    // wait 1 sec between readings
    delay(1000);

    //DHT11 CODE END

    //SERVO+ESC TESTING CODE

    /*
     TESTED VALUES FOR ESC AND SERVO:
     Note: When going forward you need to wait longer (1-2 seconds) before it moves,idk why

     > FOR ESC:

         * NEUTRAL:
         esc.writeMicroseconds(1500);

         * FORWARD:

         At this value it beeps:
         esc.writeMicroseconds(1543);

         At this value it moves (slow, with force):
         esc.writeMicroseconds(1563);

         * BACKWARD:

         At this value it beeps:
         esc.writeMicroseconds(1445);

         At this value it moves (slow, with force):
         esc.writeMicroseconds(1388);

     > FOR SERVO:

         * Far left:
         servo.writeMicroseconds(1400);

         * Center:
         servo.writeMicroseconds(1200);

         * Far right:
         servo.writeMicroseconds(1000);
    */

    //TESTING CODE FOR ESC AND SERVO START

    // forward + left
    Serial.println("Forward + Left");
    esc.writeMicroseconds(1583);
    delay(200);
    servo.writeMicroseconds(1400);
    delay(1000);

    // neutral + center
    Serial.println("Neutral + Center");
    esc.writeMicroseconds(1500);
    delay(200);
    servo.writeMicroseconds(1200);
    delay(1000);

    // arm reverse mode before going backward
    armReverseMode();

    // backward + right
    Serial.println("Backward + Right");
    esc.writeMicroseconds(1380);
    delay(200);
    servo.writeMicroseconds(1000);
    delay(1000);

    // neutral + center
    Serial.println("Neutral + Center");
    esc.writeMicroseconds(1500);
    delay(200);
    servo.writeMicroseconds(1200);
    delay(1000);
}

// !! CODE FOR CALIBRATION/ TESTING !!

/*
#include <Arduino.h>
#include <ESP32Servo.h>

const int ESC_PIN = 26;
Servo esc;

int currentPulse = 1500;  // Start at neutral

void armReverse() {
    Serial.println("\n>>> ARMING REVERSE MODE <<<");
    esc.writeMicroseconds(1500);
    delay(300);
    esc.writeMicroseconds(1380);
    delay(100);
    esc.writeMicroseconds(1500);
    delay(300);
    currentPulse = 1500;
    Serial.println("Reverse armed! Now use - to test reverse\n");
}

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n=== ESC Range Finder (No Calibration Needed) ===");
    Serial.println("Commands:");
    Serial.println("  + : Increase by 1us");
    Serial.println("  - : Decrease by 1us");
    Serial.println("  ] : Increase by 10us");
    Serial.println("  [ : Decrease by 10us");
    Serial.println("  n : Go to neutral (1500us)");
    Serial.println("  r : Arm reverse mode");
    Serial.println("=============================================\n");

    esc.attach(ESC_PIN, 1000, 2000);
    delay(1000);

    esc.writeMicroseconds(1500);  // Start at neutral
    delay(2000);  // Give ESC time to initialize

    Serial.println("ESC initialized at neutral (1500us)");
    Serial.println("\nSTARTING PROCEDURE:");
    Serial.println("1. Use +/- to find where forward motion starts");
    Serial.println("2. Type 'r' to arm reverse, then test reverse range");
    Serial.println("3. Note down your working values!\n");
}

void calibrateESC() {
    Serial.println("\n!!! CALIBRATION MODE !!!");
    Serial.println("1. DISCONNECT ESC BATTERY NOW!");
    Serial.println("   Type 'y' when ready...");

    while (Serial.read() != 'y') {
        delay(100);
    }

    Serial.println("\n2. Setting MAX throttle (2000us)");
    esc.writeMicroseconds(2000);
    Serial.println("3. CONNECT ESC BATTERY NOW!");
    Serial.println("   (Wait for beep confirmation - usually 2 beeps)");
    Serial.println("   Type 'y' when you hear beeps...");

    while (Serial.read() != 'y') {
        delay(100);
    }

    Serial.println("\n4. Setting MIN throttle (1000us)");
    esc.writeMicroseconds(1000);
    Serial.println("   (Wait for confirmation beeps)");
    delay(5000);

    Serial.println("\n5. Setting NEUTRAL (1500us)");
    esc.writeMicroseconds(1500);
    currentPulse = 1500;
    delay(2000);

    Serial.println("\n=== CALIBRATION COMPLETE ===");
    Serial.println("Now test the range with +/- commands\n");
}

void loop() {
    if (Serial.available() > 0) {
        char cmd = Serial.read();

        switch(cmd) {
            case '+':
                currentPulse += 1;
                break;
            case '-':
                currentPulse -= 1;
                break;
            case ']':
                currentPulse += 10;
                break;
            case '[':
                currentPulse -= 10;
                break;
            case 'n':
                currentPulse = 1500;
                Serial.println("\n>>> NEUTRAL <<<");
                break;
            case 'r':
                armReverse();
                return;
            default:
                return;  // Ignore other characters
        }

        // Constrain to safe range
        currentPulse = constrain(currentPulse, 1000, 2000);

        esc.writeMicroseconds(currentPulse);

        // Determine direction
        String direction = "NEUTRAL";
        if (currentPulse > 1510) direction = "FORWARD";
        else if (currentPulse < 1490) direction = "REVERSE";

        // Print status
        Serial.print("Pulse: ");
        Serial.print(currentPulse);
        Serial.print("us  |  ");
        Serial.print(direction);
        Serial.print("  |  Offset: ");
        Serial.println(currentPulse - 1500);
    }

    delay(10);
}
*/
