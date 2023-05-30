#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#include "move.h"
#include "isr.h"

int MAX_SPEED = 130;

int entered_distance; 
int current_distance;
int entered_distance_in_ticks;
int increment = 7;
int last_speed;

long long error;
static long long ticks_moved_so_far = 0;
long long time_in_ms; //essentially time in ms
int done_moving = 0;


int update_distance(int update){
    current_distance += update;
}

int finished_moving(){
    return done_moving;
}

// void speed_up(){
//     increment += 100;
// }

// int get_distance_moved(){
//     return ;
// }

// uint16_t ticks_to_distance(){
//     return WHEEL_DIAMETER/TICKS_PER_REV_6;
// }

// uint16_t calc_circumference(){
//     return(2* M_PI * WHEEL_DIAMETER);
// }

long ticks_to_distance(long ticks){
    long distance = (ticks / TICKS_PER_REV_6) * (WHEEL_DIAMETER * M_PI / GEAR_RATIO_6);
    return distance;
}

int distance_to_ticks(int distance){
    return (distance * TICKS_PER_REV_6) / (WHEEL_DIAMETER * M_PI / GEAR_RATIO_6);
}

int enter_distance(){
    int input_distance;
    printf("Enter a distance: ");
    scanf("%d", &input_distance);
    entered_distance = input_distance;
    entered_distance_in_ticks = distance_to_ticks(input_distance);
    printf("Given distance: %d in mm\t Distance in ticks: %d\n", input_distance, entered_distance_in_ticks);
    return 1;
}

int enter_speed_and_distance(int input_distance, long long * inc){
    int input_speed;
    int speed;
    printf("Enter a distance: ");
    scanf("%d", &input_distance);
    int ticks = distance_to_ticks(input_distance);
    printf("Enter a speed: ");
    scanf("%d", &input_speed);
    speed = (input_distance/input_speed >> 3);
    inc = &speed;
    return ticks;
}

int rover_move(){
    long long difference;
    long long speed;
    long long initial_position = get_motor_position(0);
    long long cur_target = get_target_position(0) + ((long long)increment<<24);

    set_target_position(0, cur_target);

    //int entered_distance_in_ticks = distance_to_ticks(entered_distance);
    ticks_moved_so_far += increment;
    done_moving = 0;
    

    //printf("%llu %llu %llu\n", time_in_ms, ticks_moved_so_far, initial_position);


    //check if movement is complete
    if(ticks_moved_so_far >= entered_distance_in_ticks){
        increment = 0;
        ticks_moved_so_far = 0;
        time_in_ms = 0;
        printf("i finished\n");
        done_moving = 1;
    }

    //calc the difference and speed
    difference = get_target_position(0) - ((long long)(get_motor_position(0))<<30); 
    speed = ((KP * difference)>>32) -  ( KV * get_motor_velocity(0) );
    // //top off speed at 130
    // if(speed > MAX_SPEED){
    //     speed = MAX_SPEED;
    // }

    //choose a point when to start decelerating 
    if(((entered_distance_in_ticks - ticks_moved_so_far) < 500)&& (increment > 0)){
        //printf("im deramping: %d distance left %d\n", increment, entered_distance_in_ticks - ticks_moved_so_far);
        //increment = increment - 1;
        
        if(MAX_SPEED > 20){
            MAX_SPEED -= 2;
            speed = MAX_SPEED;
        }
        printf("deramp: %llu\t, %d\t left: %d\n", speed, MAX_SPEED, entered_distance_in_ticks - ticks_moved_so_far);

    }
    // else if(increment < 7){
    //     increment++;
    // }
    
    //apply the speed to the motors
    set_motor_speed(1, -speed);
    set_motor_speed(3, -speed);
    set_motor_speed(5, speed);
    set_motor_speed(7, speed);
    set_motor_speed(8, speed);
    set_motor_speed(9, -speed);

    //update time and tick counters. 
    ticks_moved_so_far += get_motor_position(0) - initial_position;
    time_in_ms++; 
    return 0;
}