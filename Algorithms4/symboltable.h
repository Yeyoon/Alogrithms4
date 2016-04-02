#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

using namespace std;

template <class Key, class Value>
class ST{
public:
	virtual void put(Key key, Value val) = 0;
	virtual Value get(Key key) = 0;
	virtual void del(Key key) = 0;
	virtual bool contains(Key key) = 0;
	bool isEmpty()
	{
		return size() == 0;
	}
	virtual int size() = 0;
};

#endif 
