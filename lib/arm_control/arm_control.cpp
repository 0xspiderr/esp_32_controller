#include "arm_control.h"


static Motor arm_motor(AIN1, AIN2, PWMA, OFFSET_A, STBY);


void drive_arm_motor(int speed)
{
	arm_motor.drive(speed);
}

void stop_arm_motor()
{
	arm_motor.brake();
}