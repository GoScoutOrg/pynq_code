#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#include "move.h"
#include "isr.h"

uint16_t ticks_to_distance(){
    return WHEEL_DIAMETER/TICKSPERREV;
}

// uint16_t calc_circumference(){
//     return(2* M_PI * WHEEL_DIAMETER);
// }

long get_distance(long ticks){
    long distance = (ticks / TICKSPERREV) * (WHEEL_DIAMETER * M_PI / GEAR_RATIO);
    return distance;
}

int get_velocity(){
    return (INCR_NUM)/(.001 + 256);
}