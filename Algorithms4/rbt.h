#ifndef _RBT_H_
#define _RBT_H_

#include "symboltable.h"

template <class Key, class Value>
class RBT : public ST<Key, Value> {
private:
	const bool RED = true;
	const bool BLACK = false;
	struct Node {
		Key key;
		Value val;
		int N;
		Node *left, *right, *parent;
		bool color;

		Node(Key key, Value val, int N, bool color)
			: key(key), val(val), N(N), color(color),left(NULL),right(NULL),parent(NULL)
		{
		}
	};	

	Node *root;

	bool isRed(Node* x)
	{
		return x && x->color == RED;
	}

	Node* rotateLeft(Node* h)
	{
		Node* x = h->right;
		h->right = x->left;
		if (x->left) x->left->parent = h;

		x->left = h;
		h->parent = x;

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
		if (x->right) x->right->parent = h;

		x->right = h;
		h->parent = x;

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
			Node* l = put(h->left, key, val);
			h->left = l;
			if (l) l->parent = h;
		}
		else if (key > h->key)
		{
			Node* r = put(h->right, key, val);
			h->right = r;
			if (r) r->parent = h;
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
		h->color = !h->color;
		h->left->color = !h->left->color;
		h->right->color = !h->right->color;
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
		if (x->key == key)
		{
			Node* p = min(x->right);
			if (NULL == p)
			{
				p = x->left;
				if (p) p->parent = x->parent;
				delete x;
				return p;
			}
			else
			{
				Value v = x->val;
				Key k = x->key;
				x->val = p->val;
				x->key = p->key;
				p->val = v;
				p->key = k;
				return deleteMin(x->right);
			}
		}
		else if (x->key < key)
		{
			return del(x->left, key);
		}
		else
		{
			return del(x->right, key);
		}
	}

	Node* deleteMin(Node* x)
	{
		// 1. check if x is the min
		if (x->left == NULL)
		{
			delete x;
			return NULL;
		}

		// 2. check if x->left is 2-node
		if (!isRed(x->left) && !isRed(x->left->left))
		{
			 // a. check if x->left's brother is also a 2-node
			if (!isRed(x->right->left))
			{
				// build a 3-node
				flipColors(x);
				return deleteMin(x->left);
			}
			else
			{
				// lend  a node from x->left's brother 
				x->right = rotateRight(x->right);
				x = rotateLeft(x);
				flipColors(x);
				x->color = !x->color;
				if (x->left->left)
				{
					x->left->left->color = !x->left->left->color;
				}
				return deleteMin(x->left);
			}
		}
		else
		{
			return deleteMin(x->left);
		}

		// last we will delete the min node from a 3-node or 4-node
		if (x->right)
		{
			return rotateLeft(x);
		}
	}

	Node* min(Node* x)
	{
		if (x == NULL)
			return NULL;

		if (x->left == NULL)
			return x;

		return min(x->left);
	}

	void p(Node* x)
	{
		if (x)
		{
			cout << x->key << ":" << x->val << endl;
			p(x->left);
			p(x->right);
		}
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

	void p()
	{
		p(root);
	}

	bool contains(Key key)
	{
		return get(root, key);
	}
};
#endif
