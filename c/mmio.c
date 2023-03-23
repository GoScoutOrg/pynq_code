#include "mmio.h"

volatile unsigned int *mmio_init() {
    int memfd;
    mmio =0;
    // Open the /dev/mem device file
    memfd = open("/dev/mem", O_RDWR | O_SYNC);

    // Map the I/O register to the virtual memory space
    mmio = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, memfd, IOMEM_ADDRESS);

    // Close the /dev/mem device file
    close(memfd);

    if (mmio == MAP_FAILED) {
        perror("Failed to mmap");
        exit(EXIT_FAILURE);
    }

    mmio_read = (uint8_t *)(mmio+READ_OFFSET);

    return (volatile unsigned int *)mmio;
}

int close_mem() {
    // Unmap the virtual memory
    munmap((void *)mmio, getpagesize());
    return 0;
}



