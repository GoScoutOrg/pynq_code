//
// Created by Tyler Bovenzi on 3/23/23.
//

#include "stdint.h"
#include "motor.h"

#include "led.h"
#include "mmio.h"
//#include "isr.h"
#include "move.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

static uint16_t count = 0;
static long long total_count = 0;
static uint8_t watchdog_flag = 0;

//float error, last_error = 0.0, total = 0.0;

int distance_in_ticks;

void sigint_handler(int sig){
    printf("Received SIGINT signal\n");
    if(mmio_is_valid()) set_PL_register(0x20, 0x00);
    exit(0);
}

int isr(int signum){
    set_PL_register(WATCHDOG_REG, watchdog_flag);
    set_PL_register(DEBUG_REG, 0xFF);

    motor_update(0);

    long long increment = (7);
    long long cur_target = get_target_position(0) + ((long long)increment<<25);
    set_target_position(0, cur_target);
    total_count += increment;
    printf("total count %llu\n", total_count);
    if(total_count >= distance_in_ticks){
        set_motor_speed(0, 0);

        printf("i finished\n");
        exit(EXIT_SUCCESS);
    }
    
    long long difference = get_target_position(0) - ((long long)(get_motor_position(0))<<32);
    //printf("difference: %llu\t", difference);
    long long speed = ((KP * difference)>>32) -  ( KV * get_motor_velocity(0) );
    //printf("speed: %llu\n", speed);
    set_motor_speed(0, speed);

    set_PL_register(DEBUG_REG, 0x00);
    watchdog_flag = !watchdog_flag;
    count++;
    
    return 0;
}

int isr_init(){
    struct sigaction sa;
    struct itimerval timer;

    // Install the ISR
    sa.sa_handler = (void *)isr;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    // Set the timer to trigger every 1ms
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 1000;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 1000;
    setitimer(ITIMER_REAL, &timer, NULL);
    set_target_position(0, 0);

    return 0;
}



int main() {

    distance_in_ticks = enter_distance();
    printf("given distance in ticks: %d\n", distance_in_ticks);
    signal(SIGINT, sigint_handler);
    mmio_init();
    isr_init();
    set_led_status();
    set_brightness( 000, 000, 010);
    while(1){
        //scanf("%d", &num);
        //set_target_position(0, num);

    }

    close_mem();


}
