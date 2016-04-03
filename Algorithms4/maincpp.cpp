#include "SequentialSearchST.h"
#include "BinarySearchST.h"
#include "bst.h"

#include <iostream>
#include <string>


using namespace std;

template <class Key, class Value>
void test_one(ST<Key, Value> &st)
{
	string str("SEARCHEXAMPLE");
	for (int i = 0; i < str.length(); i++)
	{
		st.put(str[i], i);

	}
}

//template <class Key, class Value>
//void test_iter(ST<Key, Value> &st)
//{
//	SequentialSearchST<Key, Value> sst = (SequentialSearchST<Key, Value>)st;
//	SequentialSearchST<Key, Value>::iterator it = sst.begin();
//	for (; it != sst.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}



int main()
{
	SequentialSearchST<char, int> sqst;
	test_one(sqst);
	cout << sqst << endl;



	BinarySearchST<char, int> bst;
	test_one(bst);
	cout << bst << endl;

	BST<char, int> b;
	test_one(b);
	cout << b << endl;
	return 0;
}