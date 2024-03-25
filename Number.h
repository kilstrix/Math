#pragma once
class Number
{
	char* nr;
	int base, digits;
public:
	Number(const char* value, int base);
	~Number();
	Number(const Number& obj);
	Number(Number&& obj);
	Number(const int value);
	Number& operator = (int value);
	Number& operator = (const char* sir);
	Number& operator = (Number&& obj);
	Number& operator += (const Number& obj);
	Number& operator -- (int value);
	Number& operator -- ();
	int operator [] (int value);
	bool operator > (Number obj);
	bool operator < (Number obj);
	bool operator <= (Number obj);
	bool operator >= (Number obj);
	bool operator == (Number obj);
	bool operator != (Number obj);
	friend Number operator + (Number n1, Number n2);
	friend Number operator - (Number n1, Number n2);
	void SwitchBase(int newBase);
	void Print();
	int  GetDigitsCount();
	int  GetBase();
	char* GetNumber();
};
