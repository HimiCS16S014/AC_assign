#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <stdint.h>
#include "shield.h"





static const uint8_t sbox[256] = {0x2b, 0xf6, 0x62, 0x95, 0x18, 0xe4, 0x38, 0x8b, 0x3b, 0xe2, 0xf, 0x1a, 0x4b, 0xc8, 0xb5, 0x87, 0x23, 0x32, 0x58, 
	0xfb, 0xef, 0x86, 0xb6, 0x8e, 0x1b, 0x13, 0x93, 0x89, 0x2, 0xfd, 0xb3, 0xba, 0x2f, 0x90, 0xaa, 0x24, 0xd5, 0x73, 0xed, 0xad, 0xdf, 0xf4, 0x2a,
	 0x63, 0xe8, 0xe0, 0x36, 0xab, 0x33, 0x19, 0xf1, 0x5, 0xb1, 0x5b, 0x3e, 0x88, 0x68, 0x4c, 0x84, 0xc9, 0x67, 0x4d, 0xe6, 0x54, 0x29, 0x37, 0xb9,
	  0x3, 0xee, 0x31, 0x39, 0x21, 0x12, 0xc7, 0xa1, 0xb, 0x8c, 0xa0, 0x6, 0x98, 0xd7, 0x42, 0x7, 0xe1, 0xae, 0x59, 0x99, 0x30, 0xd, 0x4e, 0x11, 0xdd,
	   0xa8, 0x22, 0x6b, 0xf2, 0x27, 0xd3, 0xbc, 0xfa, 0x8a, 0x47, 0x80, 0xd1, 0x0, 0xac, 0x9d, 0xa9, 0xa4, 0x28, 0xbd, 0xea, 0xcd, 0x5e, 0x55, 0x2c,
	    0xbf, 0xe7, 0x14, 0xb7, 0xa3, 0x3a, 0xd6, 0xc3, 0x5a, 0x26, 0x51, 0x7d, 0xc4, 0xdc, 0x25, 0x8, 0xc, 0x96, 0xe9, 0xf9, 0x66, 0xc2, 0xc0, 0x41,
	     0xcc, 0x9a, 0xb8, 0xbe, 0x70, 0x6d, 0x5d, 0x3c, 0xf8, 0x4f, 0xf5, 0xcb, 0xbb, 0x9e, 0x77, 0xc6, 0x6a, 0xe5, 0x7b, 0x9b, 0xdb, 0x69, 0xa2,
	      0x76, 0xf3, 0x81, 0x92, 0xcf, 0xec, 0x74, 0x56, 0x46, 0xfc, 0x20, 0x3f, 0x1f, 0x7c, 0x91, 0x9c, 0x6e, 0x7a, 0xde, 0x94, 0xff, 0x83, 0x2e,
	       0xb2, 0x82, 0xa5, 0x5c, 0x60, 0x40, 0x2d, 0x4a, 0x57, 0xeb, 0x8d, 0xa7, 0x6c, 0x50, 0x34, 0x35, 0x1d, 0x52, 0xc1, 0xce, 0x10, 0xd9, 0x1,
	        0x7e, 0x85, 0xda, 0xfe, 0xd4, 0x4, 0xca, 0x79, 0xa, 0x43, 0x72, 0xe, 0xaf, 0x64, 0xb4, 0x16, 0xc5, 0x1e, 0x8f, 0xd2, 0x9, 0x45, 0x49, 
	        0x61, 0x17, 0xe3, 0x3d, 0xf7, 0x71, 0x65, 0x7f, 0x6f, 0x48, 0xa6, 0x15, 0xd8, 0x75, 0x5f, 0x97, 0x1c, 0x53, 0xb0, 0x9f, 0xd0, 0x78, 0x44, 0xf0};


static uint8_t key[6][8] = {{0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79}, {0x20, 0x4b, 0x75, 0x6e, 0x67, 0x20, 0x46, 0x75}, 
{0xe2, 0x32, 0xfc, 0xf1, 0x91, 0x12, 0x91, 0x88},{0xb1, 0x59, 0xe4, 0xe6, 0xd6, 0x79, 0xa2, 0x93}, {0x56, 0x8, 0x20, 0x7,0xc7, 0x1a, 0xb1, 0x8f},
 {0x76, 0x43, 0x55, 0x69, 0xa0, 0x3a, 0xf7, 0xfa}};
 
uint8_t pt[128] = {0x54 , 0x77, 0x6F , 0x20, 0x4F, 0x6E, 0x65, 0x20, 0x4E, 0x69, 0x6E, 0x65, 0x20, 0x54, 0x77, 0x6F};

uint8_t segment[nbytes],segment_l[nbytes/2],segment_r[128],state_temp[nbytes],segment_temp[nbytes] ; //, 0x4E, 0x69, 0x6E, 0x65, 0x20, 0x54, 0x77, 0x6F};

void init_pt()
{
	size_t i=0 ,j=0, k;
	for(k=0;k<16;k++)
	{
		segment_r[k]=pt[k];
	}
	for(k=0;k<nbytes/2;k++)
	{
		//segment_temp[k]=pt[k];
		segment[k]=pt[k+4];
		segment[k+4]=pt[k+8];
		//segment_temp[k+12]=pt[k+12];

	}

}


void  AddroundKey(int rn)
{
	
	size_t i,j,k;

	for(i=0;i<nbytes;i++)
	{
		segment[i]=segment[i] ^ key[rn][i];
	}

	
}







void SubByte()
{
	size_t i,j;
	for(i=0;i<nbytes;i++)
	{
			segment[i]= SubstituteByte(segment[i]);
	}
	
}


uint8_t SubstituteByte(int x)
{
	return (sbox[x]);
}





uint8_t f1(uint8_t s1, uint8_t s2)
{
	int c;
	c=(s1+s2) % 256;
	return c;
}

uint8_t f2(uint8_t s1, uint8_t s2)
{
	int c;
	c=(s1-s2) % 256;
	return c;
}

uint8_t f3(uint8_t s1, uint8_t s2)
{
	int c;
	c=s1^s2;
	return c;
}

uint8_t f4(uint8_t s1, uint8_t s2)
{
	int c;
	c=~(s1^s2);
	return c;
}

void perm()
{
	
	int i,j,k;
	uint8_t a1,a2,a3,a4,b1,b2,c1,temp[nbytes];
	uint16_t t1,t2,t3,t4;
	a1= f1(segment[0], segment[2]);
	a2= f2(segment[1], segment[4]);
	a3= f3(segment[3], segment[6]);
	a4= f4(segment[5], segment[7]);
	b1= f2(a1,a2);
	b2= f3(a3,a4);
	c1= f1(b1,b2);

	temp[0]=a1;
	temp[2]=a2;
	temp[4]=a3;
	temp[6]=a4;
	temp[1]= temp[3]= temp[5]= temp[7] = c1;
	
	t1= (uint16_t)temp[1]^ ((uint16_t)temp[0]<<8);
	t2= (uint16_t)temp[3]^ ((uint16_t)temp[2]<<8);
	t3= (uint16_t)temp[5]^ ((uint16_t)temp[4]<<8);
	t4= (uint16_t)temp[7]^ ((uint16_t)temp[8]<<8);

	t1=ROTL16(t1,4);
	t2=ROTL16(t1,5);
	t3=ROTL16(t1,2);
	t4=ROTL16(t1,6);


	temp[1]= (uint8_t)(t1 & 0x00ff);
	temp[0]=(uint8_t)ROTR16(t1,8);
	temp[3]= (uint8_t)(t2 & 0x00ff);
	temp[2]=(uint8_t)ROTR16(t2,8);
	temp[5]= (uint8_t)(t3 & 0x00ff);
	temp[4]=(uint8_t)ROTR16(t3,8);
	temp[7]= (uint8_t)(t4 & 0x00ff);
	temp[6]=(uint8_t)ROTR16(t4,8);

	for(i=0; i<nbytes;i++)
	{
		segment[i]=temp[i];
	}

	/*printf("\nt1=%d\n",t1 );
	printf("Temp[0]=%d  \n",(uint16_t)temp[0] );
	printf("Temp[1]=%d   \n", (uint16_t)temp[1] );


	
	//t1=ROTL16();


	printf("\na1= %d\n",a1 ); 
	printf("\na2= %d\n",a2 ); 
	printf("\na3= %d\n",a3 );
	printf("\na4= %d\n",a4 );  */



}

void fiestel_xor()
{
	int i,j;
	for(i=0;i<nbytes;i++)
	{
		if(i<4)
		{
			segment[i]= segment[i] ^ segment_r[i];
		}
		else
			segment[i]= segment[i] ^ segment_r[i+12];
		
	}
}

void store()
{
	int i,j,k;
	for(i=0;i<nbytes/2;i++)
	{
		segment_r[i]=segment_r[i+4];
		segment_r[i+12]=segment_r[i+8];
	}
	for(i=0;i<nbytes;i++)
	{
		segment_r[i+4]=segment[i];
	}

}

void fiestel_func(int r)
{
	void AddroundKey(r);	
	void SubByte();
	void perm();
}


void print_segment()
{
	int i,j;
	printf("\nPrinting Segment:\n");
	for(i=0;i<nbytes*2;i++)
	{

		printf("%x\t",segment_r[i] );
	}
	printf("\n");
}

void encryption()
{
	int r=0;

	void fiestel_func(r);
	void fiestel_xor();
	void store();
}

int main()
{

	uint8_t res;
	
	void init_pt();
	void print_segment();
	void encryption();
	
	
	void print_segment();


	
	return 0;

}