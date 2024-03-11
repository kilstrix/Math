#include <cstdio>
#include "Math.h"
int main()
{
	const char* v1 = "300";
	const char* v2 = "1234";
	char* x = Math::Add(v1,v2);
	int y = Math::Add(5, 1, 2, 3, 4, 5);
	printf("%s ", x);
	printf("%d ", y);
}