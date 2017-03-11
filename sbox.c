#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))

static const uint32_t sb[64] = {  
    14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1,  
     3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8,  
     4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7,  
    15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13  
};  

static const uint32_t sbo[64] = {15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  2,  3,  8,  4, 14,
     9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5,
     0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2,
     5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 15,  9};
uint8_t sbox[256];

int hadamard_matrix[256][256];

void initialize_aes_sbox() {
	/* loop invariant: p * q == 1 in the Galois field */
	uint8_t p = 1, q = 1;
	do {
		/* multiply p by x+1 */
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);
		//printf("printing p... \n");
		//printf("%d \n",p);
		/* divide q by x+1 */
		q ^= q << 1;
		q ^= q << 2;
		q ^= q << 4;
		q ^= q & 0x80 ? 0x09 : 0;
		//printf("printing q... \n");
		//printf("%d \n",q);
		/* compute the affine transformation */
		sbox[p] = 0x63 ^ q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);
	} while (p != 1);
	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
}

int SubstituteByte(int x)
{
	return (sbox[x]);
}


int check_balancedness(uint8_t *s)
{
	int i,j,c0=0,c1=0,count=0,a=1,temp;
	int c[8];
	for(i=0;i<8;i++)
	{
		c0=0;
		c1=0;
		for(j=0;j<256;j++)
		{
			temp=s[j] & a;
			//printf("temp = %d \n",temp);
			if(temp==0)
				c0++;
			else
				c1++;
		}
		printf("\nc0= %d \n",c0);
		printf("\nc1= %d \n",c1);
		
		if(c0==c1)
			c[i]=1;
		else
			c[i]=0;
		a=a<<1;

	}

	for(i=0;i<8;i++)
	{
		if(c[i]==0)
			break;
		else
			count++;
	}
	printf("count= %d\n",count);
	if(count==8)
		printf("balanced\n");		
//return 1;
		
	else
		printf("unbalanced\n");


}

int CountOnesFromInteger(uint8_t value) {
    int count;
    for (count = 0; value != 0; count++, value &= value-1);
    return count;
}

int check_sac()
{
	int i,a=128,b=1;
	int y,y1,y2,x,count,j;
	uint8_t t[256];
	//for(i=0;i<8;i++)
	{
		for(j=0;j<256;j++)
		{
	
			/*y=sbox[j] & b;
			x=j^a;
			//a=a<<1;
			y1=sbox[x] & b;
			y2=y^y1;
			t[j]=y2;*/

			y=sbox[j];
			x=j^a;
			y1=sbox[x];
			y2=y^y1;
			t[j]=y2;
			//printf("y=%d\n", y2);
			//printf("\nones: %d\n",CountOnesFromInteger(y2));
			
	
		}
		check_balancedness(t);
	}

	/*for(i=0;i<8;i++)
	{
		if(t[i]==0)
			break;
		else
			count++;
	}
	if(count==8)
		return 1;
	else
		return 0;*/

}

void hadamard() {
int H_SIZE=256;  /*length of each code word: you can change. */
int temp,r1,c1,i,j,count=0;

hadamard_matrix[0][0]=0;
hadamard_matrix[0][1]=0;
hadamard_matrix[1][0]=0;
hadamard_matrix[1][1]=1;
 
r1=2;
c1=2;

      while (r1<H_SIZE){
       printf("For count =%d\n",count);
            for (i=0;i<r1;i++)
             { /* loop #1: Copying the code matrix itself below for new code matrix */
                for (j=0;j<c1; j++)
               { 
                hadamard_matrix[i+r1][j]=hadamard_matrix[i][j];
		}	
  	     }
          
                for (j=0; j<c1;j++)
	       {/* Loop#2: Copying the code matrix on right to itself for new matrix */
                for (i=0; i<r1;i++)
 		{
                hadamard_matrix[i][j+c1]=hadamard_matrix[i][j];

                } 
	       }
            
                for (i=0;i<r1;i++)
               {/* Loop#3: Copying cojugate of code matrix for complentary diagonal part */
                for (j=0;j<c1;j++)
                { temp= (hadamard_matrix[i][j]+1)%2;

                hadamard_matrix[i+r1][j+c1]=temp;

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
      printf("%d\t", hadamard_matrix[i][j]);
     }
    printf("\n");
  }



}

int check_nonlinearity(uint8_t *y)
{
   int i,j,k, count=0,a=1,temp;
   int c[256],min_hd[8];
   
	for(k=0;k<8;k++)
	{
		for(i=0;i<256;i++)
		{
			count=0;
			
			for(j=0;j<256;j++)
			{
				temp=y[j] & a;
				if(temp!=hadamard_matrix[j][i])
					count++;
			}
			//printf("\ncount=%d\n",count);
			c[i]=count;

		}
		a=a<<1;
		
		min_hd[k]=min(c);  //finding min hamming distance
   		printf("\nmin_hd=%d\n",min_hd[k]);

	}


}

int min(int *c)
{
	int minimum,i;
	minimum=256;
	for(i=0;i<256;i++)
	{
		if(c[i]<minimum)
			minimum=c[i];
	}
	return minimum;

}
		

main()
{
	int i;
	initialize_aes_sbox();
	for(i=0;i<256;i++)
	{
		printf("%x ",SubstituteByte(i));
	}
	check_balancedness(sbox);
	check_sac();
	printf("\nones: %d\n",CountOnesFromInteger(240));

	//hadamard();
	//check_nonlinearity(sbox);
}

