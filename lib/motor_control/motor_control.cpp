/*****************************************************
 *  INCLUDES
 *****************************************************/
#include "motor_control.h"

#include <esp32-hal.h>

#include "ESP32Servo.h"

/*****************************************************
 *  VARIABLES
 *****************************************************/
static const char *TAG = "motor_control";
static const int ESC_PIN = 26;
static const int SERVO_PIN = 27;
static const int DHT11_PIN = 33;
static Servo esc;
static Servo servo;

/*****************************************************
 *  DEFINITIONS
 *****************************************************/
void init_esc()
{
	//attach ESC
	esc.attach(ESC_PIN, 1000, 2000); // min, max
	servo.attach(SERVO_PIN, 1000, 1400);
	delay(2000);

	//send neutral for 3+ seconds (initialization)
	esc.writeMicroseconds(1500);
	servo.writeMicroseconds(1200);

	delay(4000);
	ESP_LOGI(TAG, "ESC and SERVO initialized");
}

void arm_reverse_mode()
{
	Serial.println("Arming reverse mode...");
	esc.writeMicroseconds(1500); // Neutral
	delay(500);
	esc.writeMicroseconds(1380); // Quick backward pulse
	delay(100);
	esc.writeMicroseconds(1500); // Back to neutral
	delay(500);
}

void move_foward()
{
	//int i = 0;
	//for (i = 1550; i <= 1570; ++i)
	//{
	esc.writeMicroseconds(1593);
	//}
	// delay(200);
}

void move_backward()
{
	//int i = 0;
	arm_reverse_mode();
	//for (i = 1445; i >= 1388; --i)
	esc.writeMicroseconds(1345);
	// delay(200);
}

void move_left()
{
	// esc.writeMicroseconds(1583);    // Stop motor first
	// delay(50);
	servo.writeMicroseconds(1400);
	// delay(100);
}

void move_right()
{
	// esc.writeMicroseconds(1583);    // Stop motor first
	// delay(50);
	servo.writeMicroseconds(1000);
	// delay(100);
}

void move_stop()
{
	esc.writeMicroseconds(1500);
}

void move_neutral_servo()
{
	servo.writeMicroseconds(1200);
}