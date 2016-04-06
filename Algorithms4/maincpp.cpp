#include "SequentialSearchST.h"
#include "BinarySearchST.h"
#include "bst.h"
#include "rbt.h"

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

template <class Key, class Value>
void test_two(ST<Key, Value> &st)
{
	int keys[] = { 12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17 };
	for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
	{
		st.put(keys[i], keys[i]);
	}
}

template <class Key, class Value>
void test_del(RBT<Key, Value> &st)
{
	int keys[] = { 12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17 };
	for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
	{
		cout << "del " << keys[i] << ":" << endl;
		st.del(keys[i]);
		st.p();
		cout << "del " << keys[i] << " end" << endl;
	}
}

int main()
{
	/*
	SequentialSearchST<char, int> sqst;
	test_one(sqst);
	cout << sqst << endl;



	BinarySearchST<char, int> bst;
	test_one(bst);
	cout << bst << endl;

	BST<char, int> b;
	test_one(b);
	cout << b << endl;
	*/

	RBT<int, int> r;
	test_two(r);
	r.p();
	cout << endl;

	test_del(r);
	return 0;
}