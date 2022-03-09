#include "Array.h"
#include <iostream>

using namespace std;

Array::Array(int size)
{
	if(size <= 0)
	{
		cout << "Array bound error!" << endl;
	}
	else
	{
		data = new int[size];
		for(int i = 0; i < size; i++)
		{
			data[i] = 0;
		}
		len = size;
	}
}

Array::~Array()
{
	delete data;
}

int Array::length()
{
	return len;
}

int& Array::operator[](int i)
{
	static int tmp = 0;
	if(i < 0 || i >= len)
	{
		cout << "Array bound error!" << endl;
		return tmp;
	}
	else
	{
		return data[i];
	}
}

int Array::operator[](int i) const
{
	if(i < 0 || i >= len)
	{
		cout << "Array bound error!" << endl;
		return 0;
	}
	else
	{
		return data[i];
	}
}

void Array::print()
{
	cout << "[";
	for(int i = 0; i < len; i++)
	{
		cout << data[i];
		if(i < len - 1)
		{
			cout << " ";
		}
	}
	cout << "]" << endl;
}


