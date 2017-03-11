int check_sac(int * x)
{
	int i,a=1;
	int y,y1,y2;
	int t[8];
	for(i=0;i<8;i++)
	{
		y=Sbox(x);
		x=x^a;
		a=a<<1;
		y1=sbox(x);
		y2=y^y1;
		t[i]=check_balancedness(y2);
	}

	for(i=0;i<8;i++)
	{
		if(t[i]==0)
			break;
		else
			count++;
	}
	if(count==8)
		return 1;
	else
		return 0;

}
			
	
