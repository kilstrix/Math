#include "Math.h"
#include <cstdarg>
#include <cstdio>
#include <corecrt_malloc.h>
int Math::Add(int v1, int v2)
{
	return v1 + v2;
}
int Math::Add(int v1, int v2, int v3)
{
	return v1 + v2 + v3;
}
int Math::Add(double v1, double v2)
{
	return v1 + v2;
}
int Math::Add(double v1, double v2, double v3)
{
	return v1 + v2 + v3;
}
int Math::Mul(int v1, int v2)
{
	return v1 * v2;
}
int Math::Mul(int v1, int v2, int v3)
{
	return v1 * v2 * v3;
}
int Math::Mul(double v1, double v2)
{
	return v1 * v2;
}
int Math::Mul(double v1, double v2, double v3)
{
	return v1 * v2 * v3;
}
int Math::Add(int count, ...)
{
	int sum = 0;
	va_list argptr;
	va_start(argptr, count);
	for (int i = 0; i < count; ++i)
	{
		int num = va_arg(argptr, int);
		sum = sum + num;
	}
	va_end(argptr);
	return sum;
}
char* Math::Add(const char* v1, const char* v2)
{
	if (v1 == nullptr || v2 == nullptr) return nullptr;
	int num1 = 0, num2 = 0;
	for (int i = 0; v1[i] != '\0'; i++)
		num1 = num1 * 10 + v1[i] - '0';
	for (int i = 0; v2[i] != '\0'; i++)
		num2 = num2 * 10 + v2[i] - '0';
	int sum = num1 + num2;
	int sum2 = 0;
	while (sum != 0)
	{
		sum2 = sum2 * 10 + sum % 10;
		sum = sum / 10;
	}
	char* v3 = (char*)malloc(10 * sizeof(char));
	int i = 0;
	while (sum2 != 0)
	{
		v3[i] = sum2 % 10 + '0';
		sum2 = sum2 / 10;
		i++;
	}
	v3[i] = '\0';
	
	return v3;
}