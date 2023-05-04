#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#include "move.h"
#include "isr.h"


//ENTER THIS 
uint16_t ticks_to_distance(){
    return WHEEL_DIAMETER/TICKS_PER_REV_6;
}

// uint16_t calc_circumference(){
//     return(2* M_PI * WHEEL_DIAMETER);
// }

long get_distance(long ticks){
    long distance = (ticks / TICKS_PER_REV_6) * (WHEEL_DIAMETER * M_PI / GEAR_RATIO_6);
    return distance;
}

int distance_to_ticks(int distance){
    return distance * TICKS_PER_REV_6 / (WHEEL_DIAMETER * M_PI / GEAR_RATIO_6);
}

int enter_distance(int input_distance){
    printf("Enter a distance: ");
    scanf("%d", &input_distance);
    int ticks = distance_to_ticks(input_distance);
    return ticks;
}

// int get_velocity(){
//     return (INCR_NUM)/(.001 + 256);
// }