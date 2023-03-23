//
// Created by Tyler Bovenzi on 3/23/23.
//

#ifndef LED_H
#define LED_H

#include <stdint.h>

#define LED_R_REG 0x1000
#define LED_G_REG 0x1100
#define LED_B_REG 0x1200

#define LED_MODE_REG 0x1300

void set_brightness(uint8_t r, uint8_t g, uint8_t b);
void set_led_status();

#endif