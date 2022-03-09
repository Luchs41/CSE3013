#include "rangearray.h"
#include <iostream>

RangeArray::RangeArray(int low, int high)
	: Array(high - low + 1), low(low), high(high)
{
}

RangeArray::~RangeArray()
{
}


int RangeArray::baseValue()
{
	return low;
}

int RangeArray::endValue()
{
	return high;
}

int& RangeArray::operator[](int i)
{
	return Array::operator[](i - low);
}

int RangeArray::operator[](int i) const
{
	return Array::operator[](i - low);
}