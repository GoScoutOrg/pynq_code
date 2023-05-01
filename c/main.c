//
// Created by Tyler Bovenzi on 3/23/23.
//

#include "led.h"
#include "mmio.h"
#include "isr.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigint_handler(int sig){
    printf("Received SIGINT signal\n");
    if(mmio_is_valid()) set_PL_register(0x20, 0x00);
    exit(0);
}
float error, last_error = 0.0, total = 0.0;
int main() {
    int num;
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