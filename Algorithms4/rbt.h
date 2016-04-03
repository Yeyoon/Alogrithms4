#ifndef _RBT_H_
#define _RBT_H_

#include "symboltable.h"

template <class Key, class Value>
class RBT : public ST<Key, Value> {
private:
	typedef enum {RED,BLACK} Color;
	struct Node {
		Key key;
		Value val;
		int N;
		Node *left, *right;
		Color color;

		Node(Key key, Value val, int N, Color color)
			: key(key), val(val), N(N), color(color),left(NULL),right(NULL)
		{
		}
	};	

	Node *root;

	bool isRed(Node* x)
	{
		return x->color == RED;
	}

	Node* rotateLeft(Node* h)
	{
		Node* x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = RED;
		x->N = h->N;
		h->N = 1 + size(h->left) + size(h->right);
		return x;
	}

	Node* rotateRight(Node* h)
	{
		Node *x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = RED;
		x->N = h->N;
		h->N = 1 + size(h->left) + size(h->right);
		return x;
	}

	Node* put(Node* h, Key key, Value val)
	{
		if (h == NULL)
		{
			return new Node(key, val, 1, RED);
		}

		if (key < h->key)
		{
			h->left = put(h->left, key, val);
		}
		else if (key > h->key)
		{
			h->right = put(h->right, key, val);
		}
		else
		{
			h->val = val;
		}

		if (isRed(h->right) && !isRed(h->left))
		{
			h = rotateLeft(h);
		}
		
		if (isRed(h->left) && isRed(h->left->left))
		{
			h = rotateRight(h);
		}					   

		if (isRed(h->left) && isRed(h->right))
		{
			flipColors(h);
		}

		h->N = size(h->left) + size(h->right) + 1;
		
		return h;
	}

	void flipColors(Node* h)
	{
		h->color = RED;
		h->left->color = BLACK;
		h->right->color = BLACK;
	}

	Node* get(Node* x,Key key)
	{
		if (x == NULL)
			return NULL;

		if (x->key == key)
		{
			return x;
		}
		else if (x->key < key)
		{
			return get(x->right, key);
		}
		else
		{
			return get(x->left, key);
		}
	}

	int size(Node* x)
	{
		if (x == NULL)
			return 0;

		return x->N;
	}

	Node* del(Node* x, Key key)
	{

	}

public:
	RBT():root(NULL){}
	void put(Key key, Value val)
	{
		root = put(root, key, val);
		root->color = BLACK;
	}

	Value get(Key key)
	{
		Node* x = get(root, key);

		if (x)
		{
			return x->val;
		}

		return (Value)NULL;
	}

	bool isContain(Key key)
	{
		return get(root, key) != NULL;
	}

	int size()
	{
		return size(root);
	}

	void del(Key key)
	{
		del(root, key);
	}
};
#endif
