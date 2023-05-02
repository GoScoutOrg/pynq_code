#include "isr.h"

static uint16_t count = 0;
static uint64_t total_count = 0;
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
    set_target_position(0, 0);

    return 0;
}

int isr(int signum){
    set_PL_register(WATCHDOG_REG, watchdog_flag);
    set_PL_register(DEBUG_REG, 0xFF);

    motor_update(0);

    long long cur_target = get_target_position(0) + (((long long)1<<24));
    set_target_position(0, cur_target);

    long long difference = get_target_position(0) - ((long long)(get_motor_position(0))<<32);
    set_motor_speed(0, ((KP * difference)>>32) -  ( KV * get_motor_velocity(0) ));

    set_PL_register(DEBUG_REG, 0x00);
    watchdog_flag = !watchdog_flag;
    count++;total_count++;
    
    return 0;
}
