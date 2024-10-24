#include <stdio.h>
#include <math.h>
#include <float.h>

int main()
{
	float a, b;
	scanf("%f", &a);
	scanf("%f", &b);
	printf("%f\n", fabs(a-b));
	if(fabs(a - b) < FLT_EPSILON)
	{
		printf("A == B\n");
	}
	else
	{
		printf("A != B\n");
	}
}
