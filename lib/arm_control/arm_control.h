#ifndef ARM_CONTROL_H
#define ARM_CONTROL_H

#include "SparkFun_TB6612.h"

#define AIN1 14
#define AIN2 27
#define PWMA 26
#define STBY 25
#define OFFSET_A 1

void drive_arm_motor(int);
void stop_arm_motor(void);

#endif //ARM_CONTROL_H
