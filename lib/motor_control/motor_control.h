#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
/*****************************************************
 *  INCLUDES
 *****************************************************/

/*****************************************************
 *  PROTOTYPES
 *****************************************************/
void init_esc		   (void);
void arm_reverse_mode  (void);
void move_foward	   (void);
void move_backward	   (void);
void move_stop		   (void);
void move_left		   (void);
void move_right		   (void);
void move_neutral_servo(void);

#endif //MOTOR_CONTROL_H
