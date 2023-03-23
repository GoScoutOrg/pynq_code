//
// Created by Tyler Bovenzi on 3/23/23.
//

#include "motor.h" // Include the header file "motor.h"

// This function updates the position of a motor with the given index.
int motor_update(uint8_t motor_index){
    uint8_t last; // Variable to store the last position of the motor
    long last_long; // Variable to store the last position of the motor as a long integer

    // Check if the motor index is out of range
    if(motor_index>=MAX_MOTORS){
        perror("Motor Index Out Of Range"); // Print an error message
        return 1; // Return an error code
    }

    // Set the I/O register address to read the motor position
    *mmio = MOTOR_READ_REG + (motor_index<<ADDRESS_OFFSET);

    last = motor_raw_pos[motor_index]; // Save the last position of the motor
    last_long = motor_abs_pos[motor_index];
    // Read the current position of the motor from the I/O register
    motor_raw_pos[motor_index] = *mmio_read;

    // Check if the motor has crossed a threshold in either direction
    if ((last > HIGH_THRESH) && (motor_raw_pos[motor_index] < LOW_THRESH)){
        motor_abs_pos[motor_index] += 1<<MOTOR_DATA_SIZE; // Increment the absolute position of the motor
    }
    if ((last < LOW_THRESH) && (motor_raw_pos[motor_index] > HIGH_THRESH)){
        motor_abs_pos[motor_index] -= 1<<MOTOR_DATA_SIZE; // Decrement the absolute position of the motor
    }

    motor_abs_pos[motor_index] &= UPPER_MASK; // Mask the upper bits of the absolute position
    motor_abs_pos[motor_index] += motor_raw_pos[motor_index]; // Add the raw position to the absolute position

    motor_velocity[motor_index] = motor_abs_pos[motor_index] - last_long;

    printf("%ld\n",motor_abs_pos[motor_index]); // Print the absolute position of the motor
    printf("%ld\n",motor_velocity[motor_index]);
    printf("\n");

    return 0; // Return success code
}


int motor_setSpeed(int speed) {
    if (speed >  127) speed =  127;
    if (speed < -127) speed = -127;
    if (speed >= 0) *mmio = (0x2000 + speed);
    else *mmio = (0x2080 + 127 + speed);
    return 0;
}