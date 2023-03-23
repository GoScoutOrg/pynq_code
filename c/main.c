//
// Created by Tyler Bovenzi on 3/23/23.
//

#include "led.h"
#include "mmio.h"
#include "isr.h"
#include <signal.h>

void sigint_handler(int sig) {
    printf("Received SIGINT signal\n");
    if(mmio) *mmio = 0x2000;
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    mmio_init();
    isr_init();
    set_led_status();
    set_brightness( 000, 000, 010);

    while(1){
        target_pos = 500;
//        sleep(1);
//        target_pos = 100;
//        sleep(1);
    }

    close_mem();


}