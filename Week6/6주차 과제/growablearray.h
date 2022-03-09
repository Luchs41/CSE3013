#include "array.h"

template <class T>
class GrowableArray : public Array<T>
{
	public :
		GrowableArray(int size) : Array<T>(size) {}
		~GrowableArray() {}

		virtual T& operator[](int i)
		{
			if(i >= this->len)
			{
				int newSize = 2 * i;
				T* newArray;
				newArray = new T[newSize];

				for(int j = 0; j < newSize; j++)
				{
					newArray[j] = 0;
				}
				for( int j = 0; j < (this->len); j++)
				{
					newArray[j] = (this->data)[j];
				}
				delete[] (this->data);
				this->data = newArray;
				this->len = newSize;
			}

			return Array<T>::operator[](i);
		}

		virtual T operator[](int i) const
		{
			return Array<T>::operator[](i);
		}
};
