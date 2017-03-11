#include <stdio.h>
#include <math.h>
//#include <conio.h>
 
int hadamard_matrix[256][256];
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

int check_nonlinearity(int *y)
{
   int i,j,k, count,a=1,temp;
   int c[256],min_hd[8];
   
	for(k=0;k<8;k++)
	{
		for(i=0;i<256;i++)
		{
			for(j=0;j<256;j++)
			{
				temp=y[j] & a;
				if(temp!=hadamard_matrix[i][j])
					count++;
			}
			
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
	minimum=0;
	for(i=0;i<256;i++)
	{
		if(c[i]<minimum)
			minimum=c[i];
	}
	return minimum;

}

void main()
{
	hadamard();
	
}
