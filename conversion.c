unsigned char
dec2oct(int val)
{
	int i;
	unsigned char oct;
	for(i = 8; i < val; i *= 8)

	if(i > val)
		i /= 8;

	while(i > 0)
	{
		oct += val / i % 8;
		i /= 8;
		if(i != 0)
			oct *= 10;
	}
	return(oct);
}

unsigned char
inaddr2buf(struct in_addr addr)
{
	int i;
	for(i = 0; i < 4; i++)
		buf[i] = (unsigned char)((addr.s_addr >> (i * 8)) & 0xFF);
	return(buf);
}

int
main(int argc, char **argv)
{
	return(0);
}
