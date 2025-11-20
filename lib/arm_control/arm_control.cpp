/*****************************************************
 *  INCLUDES
 *****************************************************/
#include "arm_control.h"


/*****************************************************
 *  VARIABLES
 *****************************************************/
static Motor arm_motor(AIN1, AIN2, PWMA, OFFSET_A, STBY);
static Servo arm_servo;
static int current_gripper_pos = 0;
bool stop_gripper_movement = false;

/*****************************************************
 *  DEFINITIONS
 *****************************************************/
void drive_arm_motor(int speed)
{
	arm_motor.drive(speed);
}

void stop_arm_motor()
{
	arm_motor.brake();
}

void init_arm_gripper()
{
	arm_servo.attach(ARM_SERVO_PIN);
	arm_servo.write(current_gripper_pos);
}

void open_arm_gripper()
{
	for (int i = 90; i > 0; --i)
	{
		arm_servo.write(i);
		delay(ARM_SERVO_DELAY);
	}
}

void close_arm_gripper()
{
	for (int i = 0; i < 90; ++i)
	{
		arm_servo.write(i);
		delay(ARM_SERVO_DELAY);
	}
}

void stop_arm_gripper()
{
	stop_gripper_movement = true;
}
