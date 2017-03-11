int check_balancedness(int *y)
{
	int i,j,c0,c1,count=0;
	int c[8];
	for(i=0;i<8;i++)
	{
		for(j=0;j<256;j++)
		{
			if(y[i][j]==0)
				c0++;
			else
				c1++;
		}
		
		if(c0==c1)
			c[i]=1;
		else
			c[i]=0;

	}

	for(i=0;i<8;i++)
	{
		if(c[i]==0)
			break;
		else
			count++;
	}
	if(count==8)
		return 1;
	else
		return 0;


}
