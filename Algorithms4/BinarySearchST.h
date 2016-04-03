#ifndef _BINARY_SEARCH_ST_
#define _BINARY_SEARCH_ST_

#include "symboltable.h"

template <class Key, class Value>
class BinarySearchST : public ST<Key, Value> {
private:
	Key *keys;
	Value *vals;
	int N;

public:
	BinarySearchST(int capacity = 100)
		:N(0)
	{
		keys = new Key[capacity];
		vals = new Value[capacity];
	}

	int size()
	{
		return N;
	}

	Value get(Key k)
	{
		if (isEmpty()) return (Value)0;
		int i = rank(k);
		if (i < N && keys[i] == k)
			return vals[i];
		return (Value)0;
	}

	void put(Key key, Value val)
	{
		int i = rank(key);

		if (i < N && keys[i] == key)
		{
			vals[i] = val;
			return;
		}

		for (int j = N; j > i; j--)											  
		{
			keys[j] = keys[j - 1];
			vals[j] = vals[j - 1];
		}

		keys[i] = key;
		vals[i] = val;
		N++;
	}

	void del(Key key)
	{
		int i = rank(key);
		for (int j = i; j < N - 1; j++)
		{
			keys[j] = keys[j + 1];
			vals[j] = vals[j + 1];
		}
	}

	int rank(Key key)
	{
		int lo = 0, hi = N - 1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;
			if (key < keys[mid])
			{
				hi = mid - 1;
			}
			else if (key > keys[mid])
			{
				lo = mid + 1;
			}
			else
			{
				return mid;
			}
		}

		return lo;
	}

	bool contains(Key key)
	{
		int i = rank(key);
		return keys[i] == key;
	}

	friend ostream & operator <<(ostream & ot, BinarySearchST<Key, Value> & st)
	{
		for (int i = 0; i < st.N; i++)
		{
			ot << st.keys[i] << ":" << st.vals[i] << endl;
		}

		return ot;
	}
};
#endif
