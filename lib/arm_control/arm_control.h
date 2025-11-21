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
#define IN1 33
#define IN2 32
#define ENA 25
#define ARM_SERVO_PIN 12
#define ARM_SERVO_DELAY 80

/*****************************************************
 *  PROTOTYPES
 *****************************************************/
// arm motor functions
void init_arm_motor	  (void);
void drive_arm_motor  (int);
void stop_arm_motor	  (void);
// gripper functions
void init_arm_gripper (void);
void open_arm_gripper (void);
void close_arm_gripper(void);
void stop_arm_gripper (void);

#endif //ARM_CONTROL_H
