#ifndef _MY_SIMUMOTOR_H_
#define _MY_SIMUMOTOR_H_

#define NBMOTOR 2
#define VL_MOTORS
// MAXMOTORVAL doit être inférieur à 256
#define MAXMOTORVAL 100
#define NBHOLES 20
#define MASKEDHOLES 3

void simuMotor(void);
void WMOTOR_Display(void);
int WMOTOR_Init(void);
int simuMotorInit(void);
void set_motor_dir(int num_motor, int sens);
int get_motor_val(int i);

#endif
