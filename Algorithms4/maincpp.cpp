#include "SequentialSearchST.h"

#include <iostream>
#include <string>

using namespace std;

void test_one(SequentialSearchST<char, int> &st)
{
	string str("SEARCHEXAMPLE");
	for (int i = 0; i < str.length(); i++)
	{
		st.put(str[i], i);
	}
}

void test_iter(SequentialSearchST<char, int> &st)
{
	SequentialSearchST<char, int>::iterator it = st.begin();
	for (; it != st.end(); it++)
	{
		cout << *it << endl;
	}
}

int main()
{
	SequentialSearchST<char, int> sqst;
	test_one(sqst);
	cout << sqst << endl;

	cout << "TEST ITERATOR" << endl;
	test_iter(sqst);
	return 0;
}