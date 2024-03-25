#define _CRT_SECURE_NO_WARNINGS
#include "Number.h"
#include <iostream>
Number::Number(const char* value, int base)
{
	if (base >= 2 && base <= 16)
	{
		nr = new char[strlen(value) + 1];
		strcpy(nr, value);
		nr[strlen(nr)] = '\0';
		this->base = base;
		digits = strlen(nr);
	}
	else return;
}
Number::Number(const Number& obj)
{
	nr = new char[obj.digits + 1];
	strcpy(nr, obj.nr);
	base = obj.base;
	digits = obj.digits;
}
Number::Number(const int value)
{
	base = 10;
	int num = value;
	int tmp = value, n = 0;
	while (tmp)
	{
		n++;
		tmp /= 10;
	}
	digits = n;
	nr = new char[n + 1];
	for (int i = n - 1; i >= 0; i--)
	{
		nr[i] = num % 10 + '0';
		num /= 10;
	}
	nr[n] = '\0';
}
Number::Number(Number&& obj)
{
	nr = obj.nr;
	base = obj.base;
	digits = obj.digits;

	obj.nr = nullptr;
	obj.base = 0;
	obj.digits = 0;
}
Number::~Number()
{
	delete[] nr;
}
Number& Number::operator = (int value)
{
	int num = value;
	int n = 0;
	while (num)
	{
		num /= base;
		n++;
	}
	char* aux = new char[n + 1];
	int i = n - 1;
	while (value > 0)
	{
		int digit = value % base;
		if (digit > 9 && digit < 16)
			aux[i--] = 'A' + digit - 10;
		else aux[i--] = digit + '0';
		value /= base;
	}
	digits = n;
	delete[] nr;
	nr = aux;
	nr[n] = '\0';
	return (*this);
}
Number& Number::operator = (const char* sir)
{
	int value = 0;
	for(int i=0;i<strlen(sir);i++)
	{
		value = value * 10 + sir[i] - '0';
	}
	int n = 0;
	int num = value;
	while (num)
	{
		num /= base;
		n++;
	}
	char* aux = new char[n + 1];
	int i = n - 1;
	while (value > 0)
	{
		int digit = value % base;
		if (digit > 9 && digit < 16)
			aux[i--] = 'A' + digit - 10;
		else aux[i--] = digit + '0';
		value /= base;
	}
	digits = n;
	delete[] nr;
	nr = aux;
	nr[n] = '\0';
	return (*this);
}
Number& Number::operator = (Number&& obj)
{
	if (this != &obj)
	{
		delete[] this->nr;

		this->nr = obj.nr;
		this->digits = obj.digits;
		this->base = obj.base;

		obj.nr = nullptr;
		obj.digits = 0;
		obj.base = 0;
	}
	return (*this);
}
Number& Number::operator += (const Number& obj)
{
	Number tmp1 = *this, tmp2 = obj;
	int b = 0;
	if (tmp1.base > tmp2.base) b = tmp1.base;
	else b = tmp2.base;
	if (tmp1.base != 10) tmp1.SwitchBase(10);
	if (tmp2.base != 10) tmp2.SwitchBase(10);
	int num1 = atoi(tmp1.nr), num2 = atoi(tmp2.nr);
	num1 = num1 + num2;
	Number number = num1;

	delete[] this->nr;

	if (number.base != b) number.SwitchBase(b);
	this->nr = new char[number.digits + 1];
	strcpy(this->nr, number.nr);
	this->nr[number.digits] = '\0';
	this->digits = number.digits;
	this->base = number.base;

	return (*this);
}
Number& Number::operator -- (int value)
{
	this->nr[this->digits - 1] = '\0';
	this->digits--;
	return (*this);
}
Number& Number::operator -- ()
{
	do
	{
		for (int i = 0; i < this->digits - 1; i++)
			this->nr[i] = this->nr[i + 1];
		this->digits--;
		this->nr[this->digits] = '\0';
	} while (this->nr[0] == '0');
	return (*this);
}
Number operator + (Number n1, Number n2)
{
	int b;
	if (n1.GetBase() > n2.GetBase())
		b = n1.GetBase();
	else b = n2.GetBase();
	if (n1.GetBase() != 10) n1.SwitchBase(10);
	if (n2.GetBase() != 10) n2.SwitchBase(10);
	int num1 = atoi(n1.GetNumber()), num2 = atoi(n2.GetNumber());
	num1 = num1 + num2;
	Number number = num1;
	if (number.GetBase() != b) number.SwitchBase(b);
	return number;
}
Number operator - (Number n1, Number n2)
{
	int b;
	if (n1.GetBase() > n2.GetBase())
		b = n1.GetBase();
	else b = n2.GetBase();
	if (n1.GetBase() != 10) n1.SwitchBase(10);
	if (n2.GetBase() != 10) n2.SwitchBase(10);
	int num1 = atoi(n1.GetNumber()), num2 = atoi(n2.GetNumber());
	num1 = num1 - num2;
	Number number = num1;
	if (number.GetBase() != b) number.SwitchBase(b);
	return number;
}
int Number::operator [] (int value)
{
	return this->nr[value];
}
bool Number::operator > (Number obj)
{
	Number tmp = *this;
	if (tmp.base != 10) tmp.SwitchBase(10);
	if (obj.base != 10) obj.SwitchBase(10);
	int num1 = atoi(tmp.nr), num2 = atoi(obj.nr);
	if (num1 > num2) return true;
	return false;
}
bool Number::operator < (Number obj)
{
	Number tmp = *this;
	if (tmp.base != 10) tmp.SwitchBase(10);
	if (obj.base != 10) obj.SwitchBase(10);
	int num1 = atoi(tmp.nr), num2 = atoi(obj.nr);
	if (num1 < num2) return true;
	return false;
}
bool Number::operator <= (Number obj)
{
	Number tmp = *this;
	if (tmp.base != 10) tmp.SwitchBase(10);
	if (obj.base != 10) obj.SwitchBase(10);
	int num1 = atoi(tmp.nr), num2 = atoi(obj.nr);
	if (num1 <= num2) return true;
	return false;
}
bool Number::operator >= (Number obj)
{
	Number tmp = *this;
	if (tmp.base != 10) tmp.SwitchBase(10);
	if (obj.base != 10) obj.SwitchBase(10);
	int num1 = atoi(tmp.nr), num2 = atoi(obj.nr);
	if (num1 >= num2) return true;
	return false;
}
bool Number::operator == (Number obj)
{
	Number tmp = *this;
	if (tmp.base != 10) tmp.SwitchBase(10);
	if (obj.base != 10) obj.SwitchBase(10);
	int num1 = atoi(tmp.nr), num2 = atoi(obj.nr);
	if (num1 == num2) return true;
	return false;
}
bool Number::operator != (Number obj)
{
	Number tmp = *this;
	if (tmp.base != 10) tmp.SwitchBase(10);
	if (obj.base != 10) obj.SwitchBase(10);
	int num1 = atoi(tmp.nr), num2 = atoi(obj.nr);
	if (num1 != num2) return true;
	return false;
}
void Number::SwitchBase(int newBase)
{
	if (this->base == newBase) return;
	else
	{
		if (this->base != 10)
		{
			int num = 0, p = 1;
			for (int i = this->digits - 1; i >= 0; i--)
			{
				if (this->nr[i] >= 'A' && this->nr[i] <= 'F')
					num = num + (this->nr[i] - 'A' + 10) * p;
				else num = num + (this->nr[i] - '0') * p;
				p *= this->base;
			}
			int tmp = num, len = 0;
			while (tmp)
			{
				len++;
				tmp /= 10;
			}
			this->digits = len;
			char* aux = new char[len + 1];
			for (int i = len - 1; i >= 0; i--)
			{
				aux[i] = num % 10 + '0';
				num /= 10;
			}
			delete[] this->nr;
			this->nr = aux;
			this->nr[len] = '\0';
			this->base = 10;
		}
		if (newBase != 10)
		{
			int num = atoi(this->nr);
			int tmp = num;
			int n = 0;
			while (tmp)
			{
				tmp /= newBase;
				n++;
			}
			char* aux = new char[n + 1];
			int i = n - 1;
			while (num > 0)
			{
				int digit = num % newBase;
				if (digit > 9 && digit < 16)
					aux[i--] = 'A' + digit - 10;
				else aux[i--] = digit + '0';
				num /= newBase;
			}
			this->digits = n;
			delete[] this->nr;
			this->nr = aux;
			this->nr[n] = '\0';
		}
	}
	this->base = newBase;
}
void Number::Print()
{
	printf("Number: %s Base: %d Digits: %d\n", this->nr, this->base, this->digits);
}
int Number::GetDigitsCount()
{
	return this->digits;
}
int Number::GetBase()
{
	return this->base;
}
char* Number::GetNumber()
{
	return this->nr;
}
