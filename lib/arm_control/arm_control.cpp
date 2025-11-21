/*****************************************************
 *  INCLUDES
 *****************************************************/
#include "arm_control.h"


/*****************************************************
 *  VARIABLES
 *****************************************************/
// static Motor arm_motor(AIN1, AIN2, PWMA, OFFSET_A, STBY);
static Servo arm_servo;
static Servo lift_servo;
static int current_gripper_pos = 0;
bool stop_gripper_movement = false;

/*****************************************************
 *  DEFINITIONS
 *****************************************************/
void init_arm_motor()
{
	pinMode(ENA, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
}

void drive_arm_motor(int speed)
{
	digitalWrite(ENA, HIGH);
	if (speed <= 0)
	{
		digitalWrite(IN1, LOW);
		digitalWrite(IN2, HIGH);
	}
	else
	{
		digitalWrite(IN1, HIGH);
		digitalWrite(IN2, LOW);
	}
}

void stop_arm_motor()
{
	digitalWrite(ENA, LOW);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
}

void init_arm_gripper()
{
	arm_servo.attach(ARM_SERVO_PIN);
	arm_servo.write(current_gripper_pos);
	lift_servo.attach(14);
	lift_servo.write(current_gripper_pos);
}

void open_arm_gripper()
{
	for (int i = 90; i > 20; --i)
	{
		arm_servo.write(i);
		delay(ARM_SERVO_DELAY);
	}
}

void close_arm_gripper()
{
	for (int i = 20; i < 90; ++i)
	{
		arm_servo.write(i);
		delay(ARM_SERVO_DELAY);
	}
}

void stop_arm_gripper()
{
	stop_gripper_movement = true;
}
