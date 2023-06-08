//
// Created by Tyler Bovenzi on 3/23/23.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#include "stdint.h"
#include "motor.h"
#include "mmio.h"
#include "rover.h"
#include "steering_motor.h"
#include "led.h"

#ifndef ROVERCORE_ISR_H
#define ROVERCORE_ISR_H

int speed1;

int isr_init();

int isr(int signum);

#endif //ROVERCORE_ISR_H
