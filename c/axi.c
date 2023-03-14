#include "stdint.h"
#include "stdio.h"

void main(){
	uint32_t *axi = (uint32_t*)0x41200000;
	*axi = (uint32_t)0x11FF;
//printf("value at %X is %X", axi, *axi);

}
