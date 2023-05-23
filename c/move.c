#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#include "move.h"
#include "isr.h"



uint16_t ticks_to_distance(){
    return WHEEL_DIAMETER/TICKS_PER_REV_6;
}

// uint16_t calc_circumference(){
//     return(2* M_PI * WHEEL_DIAMETER);
// }

long get_distance(long ticks){
    long distance = (ticks / TICKS_PER_REV_6) * (WHEEL_DIAMETER * M_PI / GEAR_RATIO);
    return distance;
}

int distance_to_ticks(int distance){
    return distance * TICKS_PER_REV_6 / (WHEEL_DIAMETER * M_PI / GEAR_RATIO);
}

void enter_distance(int input_distance){
    printf("Enter a distance: ");
    scanf("%d", &input_distance);
    printf("given distance: %d\n", input_distance);
    int ticks = distance_to_ticks(input_distance);
}

int enter_speed_and_distance(int input_distance, long long * increment){
    int input_speed;
    int speed;
    printf("Enter a distance: ");
    scanf("%d", &input_distance);
    int ticks = distance_to_ticks(input_distance);
    printf("Enter a speed: ");
    scanf("%d", &input_speed);
    speed = (input_distance/input_speed >> 3);
    increment = &speed;
    return ticks;
}