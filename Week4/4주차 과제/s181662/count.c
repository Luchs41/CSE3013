#include "header.h"

void countNum(int n)
{

	int i;
	int num[10] = {0, };
	
	
	for(i = 1; i <= n; i++)
	{
		num[i % 10]++;
		for(int j = 10; j < 1000000001 ; j *= 10)
		{
			if((i / j) != 0)
			{
				num[(i % (10 * j)) / j]++;
			}
		}
	}
	printResult(num);
}

