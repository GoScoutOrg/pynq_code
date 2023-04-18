#include "isr.h"

static int count;
static uint8_t watchdog_flag = 0;

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
    return 0;
}

int isr(int signum){
    set_PL_register(0x50, watchdog_flag);
    set_PL_register(0x80, 0xFF);
    motor_update(0);

    int difference = get_target_position(0) - get_motor_position(0);
    //motor_setSpeed(0,(difference<<1) - 2*motor_velocity[0]);
    motor_setSpeed(0, v);
    set_PL_register(0x80, 0x00);
    watchdog_flag = !watchdog_flag;
    count++;
    return 0;

}
