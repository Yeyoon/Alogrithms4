#ifndef _BST_H_
#define _BST_H_
template <class Key, class Value>
class BST : public ST<Key, Value> {
private:
	class Node {
		friend class BST<Key, Value>;
	private:
		Key key;
		Value val;
		Node* left, *right;
		int N;

	public:
		Node(Key key, Value val, int N)
			:key(key), val(val), N(N)
		{

		}
	};

	Node* root;

	int size(Node* r)
	{
		if (r == NULL)
			return 0;
		return r->N;
	}

	Value get(Node* x, Key key)
	{
		if (x == NULL)
		{
			return (Value)NULL;
		}
		
		if (key < x->key)
		{
			return get(x->left, key);
		}
		else if (key > x->key)
		{
			return get(x->right, key);
		}
		else 
		{
			return x->val;
		}
	}

	Node* put(Node* x, Key key, Value val)
	{
		if (x == NULL)
		{
			return new Node(key, val, 1);
		}

		if (key < x->key)
		{
			x->left = put(x->left, key, val);
		}
		else if (key > x->key)
		{
			x->right = put(x->right, key, val);
		}
		else
		{
			x->val = val;
		}

		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}

	Node* del(Node* x, Key key)
	{
		if (x == NULL)
			return NULL;

		if (x->key < key)
		{
			x->left = del(x->left, key);
		}
		else if (x->key > key)
		{
			x->right = del(x->right, key);
		}
		else
		{
			if (x->right == NULL)
			{
				Node* left = x->left;
				delete x;
				return left;
			}

		    if (x->left == NULL)
			{
				Node* right = x->right;
				delete x;
				return right;
			}
			
			Node *t = x;
			x = min(t->right);
			x->right = deleteMin(t->right);
			x->left = t->left;
		}

		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}

	Node* min(Node* x)
	{
		if (x->left == NULL)
			return x;

		return min(x->left);
	}

	Node* deleteMin(Node* x)
	{
		if (x->left == NULL)
		{
			return x->right;
		}

		x->left = deleteMin(x->left);
		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}

	void output(Node* x, ostream & ot)
	{
		if (x == NULL)
			return;

		ot << x->key << ":" << x->val << endl;
		output(x->left,ot);
		output(x->right,ot);
	}

public:
	void deleteMin()
	{
		root = deleteMin(root);
	}

	int size()
	{
		return size(root);
	}

	Value get(Key key)
	{
		return get(root, key);
	}

	void put(Key key, Value val)
	{
		root = put(root, key, val);
	}

	bool contains(Key key)
	{
		if (get(root, key))
			return true;
		return false;
	}

	void del(Key key)
	{
		del(root, key);
	}

	Key min()
	{
		return min(root).key;
	}

	void output(ostream &ot)
	{
		output(root, ot);
	}

	friend ostream & operator<<(ostream & ot, BST<Key, Value> &bst)
	{
		bst.output(ot);
		return ot;
	}
};
#endif
