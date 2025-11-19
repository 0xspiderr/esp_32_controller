#ifndef ARM_CONTROL_H
#define ARM_CONTROL_H
/*****************************************************
 *  INCLUDES
 *****************************************************/
#include "SparkFun_TB6612.h"
#include "ESP32Servo.h"

/*****************************************************
 *  VARIABLES
 *****************************************************/
extern bool stop_gripper_movement;

/*****************************************************
 *  DEFINES
 *****************************************************/
#define AIN1 14
#define AIN2 27
#define PWMA 26
#define STBY 25
#define OFFSET_A 1
#define ARM_SERVO_PIN 12

#define ARM_SERVO_DELAY 30

/*****************************************************
 *  PROTOTYPES
 *****************************************************/
// arm motor functions
void drive_arm_motor(int);
void stop_arm_motor(void);
// gripper functions
void init_arm_gripper(void);
void open_arm_gripper(void);
void close_arm_gripper(void);
void stop_arm_gripper(void);

#endif //ARM_CONTROL_H
