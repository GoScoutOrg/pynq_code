# GoScout PYNQ Library - C Code

This directory contains the C source code for the GoScout PYNQ library, which provides a set of functions for controlling various hardware components on the Digilent PYNQ Z1 development board.

### mmio.c: 

Comminication between PS and PL using AXI Memory Mapped IO

- creates global var: mmio for writing to control registers
- creates gloval var: mmio_read for reading from status registers

### motor.c:

Facilitates reading motor encoder positions and writing to pwm registers

### isr.c:

Establishes interrupt service routine to run every 1ms

### led.c:

Writing to onboard RGB leds. 

## Usage:

- Navigate into c directory
- make
- sudo ./roverCore

Note: currently needs root priviledges to read memory tables



