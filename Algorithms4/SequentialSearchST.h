#ifndef _SEQUENTIAL_SEARCH_ST_H_
#define _SEQUENTIAL_SEARCH_ST_H_

#include "symboltable.h"
#include <iostream>

using namespace std;

template <class Key, class Value> class SequentialSearchSTIter;

template <class Key, class Value>
class SequentialSearchST : public ST<Key,Value> {
public:
	// add for iterator
	typedef SequentialSearchSTIter<Key, Value> iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value value_type;
	typedef Value * pointer;
	typedef Value & reference;

	// main class functions define
	class Node {
	public:
		Key key;
		Value val;
		Node* next;

		Node(Key key, Value val, Node* next = NULL) :
			key(key),
			val(val),
			next(next)
		{
		}
	};

	SequentialSearchST():first(NULL),_size(0){}
	~SequentialSearchST()
	{
		for (Node *x = first; x != NULL; )
		{
			Node *f = x;
			x = x->next;
			free(f);
		}

		first = NULL;
		_size = 0;
	}
	Value get(Key key)
	{
		for (Node *x = first; x != NULL; x = x->next)
		{
			if (key == x->key)
			{
				return x->val;
			}
		}

		return (Value)0;
	}

	void put(Key key, Value val)
	{
		for (Node *x = first; x != NULL; x = x->next)
		{
			if (key == x->key)
			{
				x->val = val;
				return;
			}
		}

		first = new Node(key, val, first);
		_size++;
	}

	void del(Key key)
	{
		Node *p = first;
		for (Node *x = first; x != NULL; x = x->next)
		{
			if (key == x->key)
			{
				if (x == first)
				{
					first = first->next;
				}
				else
				{
					p->next = x->next;
				}

				free(x);
				_size--;
				return;
			}

			p = x;
		}
	}

	virtual bool contains(Key key)
	{
		for (Node *x = first; x != NULL; x = x->next)
		{
			if (key == x->key)
				return true;
		}

		return false;
	}

	int size()
	{
		return _size;
	}

	friend ostream & operator<<(ostream &os, const SequentialSearchST<Key,Value> &st)
	{
		for (Node *x = st.first; x != NULL; x = x->next)
		{
			os << x->key << ":" << x->val << endl;
		}

		return os;
	}

	iterator begin()
	{
		return iterator(*this,first);
	}

	iterator end()
	{
		return iterator(*this, NULL);
	}

private:
		Node* first;
		int _size;
};

template <class Key, class Value>
class SequentialSearchSTIter {
private:
	SequentialSearchST<Key, Value> &st;
	typename SequentialSearchST<Key, Value>::Node *_current;

public:
	typedef SequentialSearchSTIter<Key, Value> iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value value_type;
	typedef Value * pointer;
	typedef Value & reference;
	typedef typename SequentialSearchST<Key, Value>::Node * pNode;
	SequentialSearchSTIter<Key,Value>(SequentialSearchST<Key,Value> & sqst, pNode x)
		: st(sqst), _current(x)
	{
	}

	Value & operator*()
	{
		return _current->val;
	}

	iterator & operator++()
	{
		_current = _current->next;
		return *this;
	}

	iterator operator++(int)
	{
		SequentialSearchSTIter<Key, Value> clone(*this);
		_current = _current->next;
		return clone;
	}

	friend bool operator == (iterator & it1, iterator & it2)
	{
		if(it1._current == it2._current)
			return true;
		return false;
	}

	friend bool operator != (iterator & it, iterator & that)
	{
		return !(that == it);
	}

};

#endif

