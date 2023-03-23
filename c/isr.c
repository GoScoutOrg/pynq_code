//
// Created by Tyler Bovenzi on 3/23/23.
//

#include "isr.h"



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

    target_pos = 0;

    return 0;
}

int isr(int signum){
    *mmio=0x80FF;

    motor_update(0);
    int difference = target_pos - motor_abs_pos[0];
    motor_setSpeed((difference<<2) - motor_velocity[0]);
    motor_setSpeed(0);
    *mmio = 0x8000;
    return 0;

}
