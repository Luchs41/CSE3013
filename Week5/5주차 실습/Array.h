#ifndef __ARRAY__
#define __ARRAY__

class Array{
	protected:
		int *data;
		int len;
	public:
			Array(int size);
			~Array();

			int length();

			int& operator[](int i);
			int operator[](int i)const;

			void print();
};
#endif
