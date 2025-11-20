/*****************************************************
 *  INCLUDES
 *****************************************************/
#include "camera_control.h"


/*****************************************************
 *  VARIABLES
 *****************************************************/
static Servo camera_servo;
static int current_servo_pos = 90;


/*****************************************************
 *  DEFINITIONS
 *****************************************************/
void init_camera_servo()
{
	camera_servo.attach(CAMERA_SERVO_PIN);
	camera_servo.write(current_servo_pos);
	delay(1000);
}

void rotate_camera_servo_right()
{
	current_servo_pos -= CAMERA_SERVO_STEP;
	current_servo_pos = check_servo_rot_value();
	camera_servo.write(current_servo_pos);
}

void rotate_camera_servo_left()
{
	current_servo_pos += CAMERA_SERVO_STEP;
	current_servo_pos = check_servo_rot_value();
	camera_servo.write(current_servo_pos);
}

static int check_servo_rot_value()
{
	if (current_servo_pos >= 180)
		return 180;
	if (current_servo_pos <= 0)
		return 0;

	return current_servo_pos;
}