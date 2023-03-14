
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

// Memory address of the I/O register
#define IOMEM_ADDRESS 0x41200000

int main() {
    int memfd;
    void *mmio;

    // Open the /dev/mem device file
    memfd = open("/dev/mem", O_RDWR | O_SYNC);

    // Map the I/O register to the virtual memory space
    mmio = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, memfd, IOMEM_ADDRESS);

    if (mmio == MAP_FAILED) {
        perror("Failed to mmap");
        exit(EXIT_FAILURE);
    }

while(1){

    // Write a value to the I/O register
    //*((volatile unsigned int*)mmio) = 0x2000+127;
    int8_t pos = *((volatile unsigned int *)mmio + 2);
    printf("Read: %d\n", pos);
    int8_t speed = (128 - pos)*2;
    *((volatile unsigned int*)mmio) = 0x2000+speed;
	
}
    // Unmap the virtual memory
    munmap(mmio, getpagesize());

    // Close the /dev/mem device file
    close(memfd);

    return 0;
}
