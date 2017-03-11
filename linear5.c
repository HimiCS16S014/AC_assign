#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))
int count1=0, count2=0, count3=0;

//uint8_t sbox[256];

/*uint8_t sbox[256] ={43, 246, 98, 149, 24, 228, 56, 139, 59, 226, 15, 26, 75, 200, 181, 135, 35, 50, 88, 251, 239, 134, 182, 142, 27, 19, 147, 137, 2, 253, 179, 186, 47, 144, 170, 36, 213, 115, 237, 173, 223, 244, 42, 99, 232, 224, 54, 171, 51, 25, 241, 5, 177, 91, 62, 136, 104, 76, 132, 201, 103, 77, 230, 84, 41, 55, 185, 3, 238, 49, 57, 33, 18, 199, 161, 11, 140, 160, 6, 152, 215, 66, 7, 225, 174, 89, 153, 48, 13, 78, 17, 221, 168, 34, 107, 242, 39, 211, 188, 250, 138, 71, 128, 209, 0, 172, 157, 169, 164, 40, 189, 234, 205, 94, 85, 44, 191, 231, 20, 183, 163, 58, 214, 195, 90, 38, 81, 125, 196, 220, 37, 8, 12, 150, 233, 249, 102, 194, 192, 65, 204, 154, 184, 190, 112, 109, 93, 60, 248, 79, 245, 203, 187, 158, 119, 198, 106, 229, 123, 155, 219, 105, 162, 118, 243, 129, 146, 207, 236, 116, 86, 70, 252, 32, 63, 31, 124, 145, 156, 110, 122, 222, 148, 255, 131, 46, 178, 130, 165, 92, 96, 64, 45, 74, 87, 235, 141, 167, 108, 80, 52, 53, 29, 82, 193, 206, 16, 217, 1, 126, 133, 218, 254, 212, 4, 202, 121, 10, 67, 114, 14, 175, 100, 180, 22, 197, 30, 143, 210, 9, 69, 73, 97, 23, 227, 61, 247, 113, 101, 127, 111, 72, 166, 21, 216, 117, 95, 151, 28, 83, 176, 159, 208, 120, 68, 240};*/

uint8_t sbox_linear_approx[16][16];
uint8_t sbox[16] =   {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12,5, 9, 0, 7};

//-----------------------------------------


void print_table_latex(uint8_t sbox_linear_approx[16][16]) {
    unsigned int j,k;

    
printf("\t");
    for (k=0; k < 15; k++) {
        printf("%d\t ", k);
    }
    printf("%d\n", k);

    for (j=0; j < 16; j++) {
        printf("%d\t ", j);
        for (k=0; k < 15; k++) {
            printf("%d\t ", sbox_linear_approx[j][k]);
        }
        printf("%d\n", sbox_linear_approx[j][k]);
    }
    printf("\\end{tabular}\n");
}


inline unsigned char get_parity(unsigned int word) {
    unsigned char parity = 0;

    while (word) {
      parity = !parity;
      word = word & (word - 1);
    }

    return parity;
}


void generate_approx_table() {
    printf("hi0\n");

    uint8_t input, mask_input, mask_output;
    uint8_t output, masked_input, masked_output;

    // initializing sbox_linear_approx
    memset(sbox_linear_approx, 0, 16*16);
		printf("hi1\n");
	count3=0;
    for (input=0; input < 16; input++) 
    {

      if(count3<256)
      { 
        output = sbox[input];
	//printf("hi2\t");
	count2=0;
        for (mask_input=0; mask_input < 16; mask_input++) 
	{
	    if(count2<256)
	    {
              masked_input = input & mask_input;   
              //printf("hi3\t");
		count1=0;
              for (mask_output=0; mask_output < 16; mask_output++) 
		{
			if(count1<256)
			{
                		masked_output = output & mask_output;
				//printf("hi4\t");
               			if (!get_parity(masked_input ^ masked_output))
                       		sbox_linear_approx[mask_input][mask_output]++;
				count1++;
			}
			else
				break;
                }
		count2++;
	    }
	     else
		break;
	   
         }
	count3++;	
        }
	else
	   
	   break;

    }

   print_table_latex(sbox_linear_approx);
}


void main()
{
	int i;
	//initialize_aes_sbox();
	/*for(i=0;i<256;i++)
	{
		printf("%x ",SubstituteByte(i));
	}*/
	generate_approx_table();
}
