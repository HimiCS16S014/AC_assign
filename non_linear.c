int check_nonlinearity(int *y, int *hadamard_matrix)
{
   int i,j,k, count;
   int c[256],min_hd[8];
   
	for(k=0;k<8;k++)
	{
		for(i=0;i<256;i++)
		{
			for(j=0;j<256;j++)
			{
				if(y[k][j]!=hadamard_matrix[i][j])
					count++;
			}
			
			c[i]=count;

		}
		
		min_hd[k]=min(c);  //finding min hamming distance
   

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
