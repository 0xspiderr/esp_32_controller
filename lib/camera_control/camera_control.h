#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H
/*****************************************************
 *  INCLUDES
 *****************************************************/
#include "ESP32Servo.h"

/*****************************************************
 *  DEFINES
 *****************************************************/
#define CAMERA_SERVO_PIN   14
#define CAMERA_SERVO_STEP  1


/*****************************************************
 *  PROTOTYPES
 *****************************************************/
void init_camera_servo		    (void);
void rotate_camera_servo_right  (void);
void rotate_camera_servo_left   (void);
static int check_servo_rot_value(void);

#endif //CAMERA_CONTROL_H
