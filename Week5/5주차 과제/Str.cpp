#include <iostream>
#include "Str.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

Str::Str(int leng)
{
	if(leng < 0)
	{
		cout << "Error : Invalid String" << endl;
	}
	else
	{
		str = new char[leng + 1];
		len = leng;
	}
}

Str::Str(char* neyong)
{
	if(strlen(neyong) < 0)
	{
		cout << "Error : Invalid String" << endl;
	}
	else
	{
		str = new char[len + 1];
		len = strlen(neyong);
		strcpy(str, neyong);
	}
}

Str::~Str()
{
	delete(str);
}

int Str::length(void)
{
	return len;
}

char* Str::contents(void)
{
	return str;
}

int Str::compare(class Str& a)
{
	return strcmp(str, a.contents());
}

int Str::compare(char* a)
{
	return strcmp(str, a);
}

void Str::operator=(char* a)
{
	if(strlen(a) < 0)
	{
		cout << "Error : Invalid String" << endl;
	}
	else
	{
		delete(str);
		len = strlen(a);
		str = new char[len + 1];
		strcpy(str, a);
	}
}

void Str::operator=(class Str& a)
{
	if(a.length() < 0)
	{
		cout << "Error : Invalid String" << endl;
	}
	else
	{
		delete(str);
		len = a.length();
		str = new char[len + 1];
		strcpy(str, a.contents());
	}
}
