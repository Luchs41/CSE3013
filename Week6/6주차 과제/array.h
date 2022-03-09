#ifndef __ARRAY__
#define __ARRAY__

#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class Array{
	protected:
		T *data;
		int len;
	public:
			Array(int size)
			{
				if(size <= 0)
				{
					cout << "Array bound error!" << endl;
				}
				else
				{
					data = new T[size];
					for(int i = 0; i < size; i++)
					{
						data[i] = 0;
					}
					len = size;
				}
			}
			~Array()
			{
				delete[] data;
			}

			int length()
			{
				return len;
			}

			virtual T& operator[](int i)
			{
				static T tmp = 0;
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
			virtual T operator[](int i)const
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

			void print()
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
};
#endif
