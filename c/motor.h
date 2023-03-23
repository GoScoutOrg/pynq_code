//
// Created by Tyler Bovenzi on 3/23/23.
//

#ifndef ROVERCORE_MOTOR_H
#define ROVERCORE_MOTOR_H

#include <stdint.h>
#include "mmio.h"

#define MOTOR_READ_REG 0x3000
#define MOTOR_WRITE_REG 0x2000

#define MAX_MOTORS 16
#define MOTOR_DATA_SIZE 8

#define UPPER_MASK 0xFFFFFF00
#define LOWER_MASK 0x000000FF

#define HIGH_THRESH 206 //256-50
#define LOW_THRESH 50

long motor_abs_pos[16];
long motor_velocity[16];

uint8_t motor_raw_pos[16];
uint8_t motor_pwm[16];

int motor_update(uint8_t motor_index);
int motor_setSpeed(int speed);

#endif //ROVERCORE_MOTOR_H
