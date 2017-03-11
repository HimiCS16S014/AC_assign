#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

uint8_t sbox[256] ={43, 246, 98, 149, 24, 228, 56, 139, 59, 226, 15, 26, 75, 200, 181, 135, 35, 50, 88, 251, 239, 134, 182, 142, 27, 19, 147, 137, 2, 253, 179, 186, 47, 144, 170, 36, 213, 115, 237, 173, 223, 244, 42, 99, 232, 224, 54, 171, 51, 25, 241, 5, 177, 91, 62, 136, 104, 76, 132, 201, 103, 77, 230, 84, 41, 55, 185, 3, 238, 49, 57, 33, 18, 199, 161, 11, 140, 160, 6, 152, 215, 66, 7, 225, 174, 89, 153, 48, 13, 78, 17, 221, 168, 34, 107, 242, 39, 211, 188, 250, 138, 71, 128, 209, 0, 172, 157, 169, 164, 40, 189, 234, 205, 94, 85, 44, 191, 231, 20, 183, 163, 58, 214, 195, 90, 38, 81, 125, 196, 220, 37, 8, 12, 150, 233, 249, 102, 194, 192, 65, 204, 154, 184, 190, 112, 109, 93, 60, 248, 79, 245, 203, 187, 158, 119, 198, 106, 229, 123, 155, 219, 105, 162, 118, 243, 129, 146, 207, 236, 116, 86, 70, 252, 32, 63, 31, 124, 145, 156, 110, 122, 222, 148, 255, 131, 46, 178, 130, 165, 92, 96, 64, 45, 74, 87, 235, 141, 167, 108, 80, 52, 53, 29, 82, 193, 206, 16, 217, 1, 126, 133, 218, 254, 212, 4, 202, 121, 10, 67, 114, 14, 175, 100, 180, 22, 197, 30, 143, 210, 9, 69, 73, 97, 23, 227, 61, 247, 113, 101, 127, 111, 72, 166, 21, 216, 117, 95, 151, 28, 83, 176, 159, 208, 120, 68, 240};

uint8_t onescount[256];
uint8_t degree[8];
uint8_t a=1;
uint8_t Non_afn_form[256][8];
uint8_t AFN_matrix[256][256];
uint8_t afn_form[256][8];
uint8_t  afn[256];
void afn_multiplication( );

void AFN_matrix1() 
{
int H_SIZE=256;  /*length of each code word: you can change. */
int temp,r1,c1,i,j,count=0;

AFN_matrix[0][0]=1;
AFN_matrix[0][1]=1;
AFN_matrix[1][0]=1;
AFN_matrix[1][1]=0;
 
r1=2;
c1=2;

      while (r1<H_SIZE){
       printf("For count =%d\n",count);
            for (i=0;i<r1;i++)
             { /* loop #1: Copying the code matrix itself below for new code matrix */
                for (j=0;j<c1; j++)
               { 
                AFN_matrix[i+r1][j]=AFN_matrix[i][j];
		}	
  	     }
          
                for (j=0; j<c1;j++)
	       {/* Loop#2: Copying the code matrix on right to itself for new matrix */
                for (i=0; i<r1;i++)
 		{
                AFN_matrix[i][j+c1]=0;

                } 
	       }
            
                for (i=0;i<r1;i++)
               {/* Loop#3: Copying cojugate of code matrix for complentary diagonal part */
                for (j=0;j<c1;j++)
                { //temp= (hadamard_matrix[i][j]+1)%2;

                AFN_matrix[i+r1][j+c1]=AFN_matrix[i][j];

                }
               }

      count++;
       r1*=2;
       c1*=2;    
    }
 for (i=0;i<H_SIZE; i++)
 {
    for(j=0; j<H_SIZE;j++)
     {
      printf("%d\t", AFN_matrix[i][j]);
     }
    printf("\n");
  }

}

void non_afn_matrix()
{
	int i,j,temp,c=1;
	//int input[16][8];// {x1,x2,x3,x4,y1,y2,y3,y4}
	
	for(i=0;i<256;i++)
	{       c=1;
		for(j=7;j>=0;j--)
		{	

			
			if(i & c)
				Non_afn_form[i][j]=1;
			else
				Non_afn_form[i][j]=0;	
			//printf("c is \n%d",c);
			
			
			c=c<<1;

		}

	}


	for(i=0;i<256;i++)
	{
		for(j=0;j<8;j++)
		{

			printf("%d\t",Non_afn_form[i][j]);
		}
		
		printf("\n");
	}



}

void afn_multiplication()
{
    int i,j,k;
uint8_t sum;

    
    for (i = 0; i < 256; i++) {
      for (j = 0; j < 8; j++) {
        for (k = 0; k < 256; k++) {
          sum = sum + AFN_matrix[i][k]*Non_afn_form[k][j];
	  sum= sum %2;
        }
	  
        afn_form[i][j] = sum;
        sum = 0;
      }
    }

}


void convertBinaryToDecimal(afn_form)
{
    int decimalNumber = 0, i = 0, sum,j;
    for (j=0;j<256;j++)
    {     sum=0;
	for(i=7;i>=0;i--)
      {
	sum= sum + pow(2, (7-i));
      }
	afn[j]=sum;
}
		
    
}

uint8_t CountOnesFromInteger(uint8_t value) {
    uint8_t count;
    for (count = 0; value != 0; count++, value &= value-1);
    return count;
}


uint8_t max(uint8_t *c)
{
	int i;
	uint8_t max;
	max=0;
	for(i=0;i<256;i++)
	{
		if(c[i]>max)
			max=c[i];
	}
	return max;

}
void check_algebraic_degree(uint8_t *s)
{
	int c;
	uint8_t i,j,temp,temp2;
	for(i=0;i<8;i++)
	{	c=0;
		for(j=0;j<256;j++)
		{
			if(c<256)
			{	temp2=afn[j];
				temp= sbox[temp2] & a;
				if(temp==0)
					onescount[j]=0;
				else
					onescount[j]=CountOnesFromInteger(j);
				c++;
			}
			else
				break;
		}
		
		degree[i]= max(onescount);
		a=a<<1;
	}
	
	for(i=0;i<8;i++)
	{
		printf("Degree of y[%d] = %d\n", i,degree[i]);
	}

}



void main()
{	
	printf("-----------------------ALGEBRAIC DEGREE-----------------------------\n");
	check_algebraic_degree(sbox);
}
