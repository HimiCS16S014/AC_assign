#include<stdio.h>
#include<stdint.h>
#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))

void main() {
	uint8_t xformed,q;
	q=9;
	
	
	 xformed =  q ^ ROTL8(q, 1) ;
	printf("\n%x\n",xformed);

		
}
