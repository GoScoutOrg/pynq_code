//
// Created by Tyler Bovenzi on 3/23/23.
//
#ifndef ROVERCORE_MMIO_H
#define ROVERCORE_MMIO_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

// Memory address of the I/O register
#define IOMEM_ADDRESS 0x41200000
#define ADDRESS_OFFSET 8
#define READ_OFFSET 2

volatile unsigned int* mmio;
uint8_t * mmio_read;


// Function prototypes
volatile unsigned int *mmio_init(void);
int close_mem();

#endif //ROVERCORE_MMIO_H
