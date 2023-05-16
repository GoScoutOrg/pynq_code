#include "isr.h"
static steering_motor_t steer1;

static uint32_t count = 0;
static int ind = 0;
static uint64_t total_count = 0;
static uint8_t watchdog_flag = 0;
static steering_motor_t steer1;

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
    timer.it_interval.tv_usec = 1000; //was 1000
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 1000; //was 1000
    setitimer(ITIMER_REAL, &timer, NULL);
    set_target_position(0, 0);


    steer1.index = 0;
    steer1.state = STATE_INITIALIZE;

    for(int i = 0; i<10; i++){
        set_motor_speed(i, 0);
    }

    return 0;
}

int isr(int signum) {
    set_PL_register(WATCHDOG_REG, watchdog_flag);
    set_PL_register(DEBUG_REG, 0xFF);
    if (count == 1000) calibrate(&steer1);
    steering_motor_handle_state(&steer1);
    //set_motor_speed(0, -20);
    //set_motor_speed(MLW, 20);
    //motor_update(MLW);
    //set_motor_speed(MLW,70);
//printf("Pos: %ld\n", get_motor_position(MLW));

//    ind = (ind + 1) % 10;
//    motor_update(ind);
//
//    long long cur_target = get_target_position(ind) + (((long long)speed1<<30));
//    set_target_position(ind, cur_target);

    set_PL_register(DEBUG_REG, 0x00);
    watchdog_flag = !watchdog_flag;
    count++;
    total_count++;

}