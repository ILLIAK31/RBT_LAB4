// ALGO2 IS1 224B LAB03
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>

template <class T>
class Comporator
{
public:
	Comporator() = default;
	~Comporator();
	bool operator()(T x, T y)
	{
		if (x > y)
			return true;
		return false;
	}
};

template <class T>
Comporator<T>::~Comporator() {}

template <class T>
class Node
{
public:
	Node()=default;
	~Node();
	T value;
	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	bool red_black;
	int ID{ 0 };
};

template<class T>
Node<T>::~Node() {}

template <class T>
class RBT
{
public:
	RBT()=default;
	~RBT();
	Node<T>* root = nullptr;
	int Size{ 0 };
	void Rotate_left(Node<T>* kid , Node<T>* parent);
	void Rotate_right(Node<T>* kid, Node<T>* parent);
	void Add(T Value,Comporator<T> comporator);
};

template<class T>
RBT<T>::~RBT() {}

template <class T>
void RBT<T>::Rotate_left(Node<T>* kid, Node<T>* parent)
{
	if (kid->right != nullptr)
	{
		kid->parent = parent->parent;
		kid->left = parent;
		if (kid->left != nullptr)
		{
			parent->right = kid->left;
			kid->left->parent = parent;
		}
		else if (kid->right != nullptr)
		{
			parent->right = kid->right;
			kid->right->parent = parent;
		}
	}
	else
	{
		Rotate_right(kid, parent);
	}
}

template <class T>
void RBT<T>::Rotate_right(Node<T>* kid, Node<T>* parent)
{
	if (parent->left != nullptr)
	{
		if (kid->right != nullptr)
		{
			parent->left = kid->right;
			kid->right->parent = parent;
		}
		kid->right = parent;
		kid->parent = parent->parent;
		parent->parent = kid;
	}
	else 
	{
		Rotate_left(kid,parent);
	}
}

template <class T>
void RBT<T>::Add(T Value, Comporator<T> comporator)
{
	if (this->Size == 0)
	{
		++this->Size;
		Node<T>* node = new Node<T>();
		root = node;
		root->value = Value;
		root->parent = root->left = root->right = nullptr;
		root->ID = this->Size;
		root->red_black = false;
	}
	else
	{
		Node<T>* node2 = this->root;
		while (true)
		{
			if (comporator(Value, node2->value))
			{
				if (node2->right != nullptr)
					node2 = node2->right;
				else
				{
					++this->Size;
					Node<T>* node = new Node<T>();
					node->parent = node2;
					node2->right = node;
					node->left = node->right = nullptr;
					node->value = Value;
					node->ID = this->Size;
					break;
				}
			}
			else
			{
				if (node2->left != nullptr)
					node2 = node2->left;
				else
				{
					++this->Size;
					Node<T>* node = new Node<T>();
					node->parent = node2;
					node2->left = node;
					node->left = node->right = nullptr;
					node->value = Value;
					node->ID = this->Size;
					break;
				}
			}
		}
		if (this->Size >= 3 && node2->parent->parent->right->red_black == true)
		{
			//
		}
		else if (this->Size >= 3 && node2->parent->right == nullptr)
		{
			//
		}
		else if (this->Size >= 3 && node2->parent->left == nullptr)
		{
			//
		}
		else if (this->Size >= 3 && node2->parent->right == node2 && node2->parent->parent->right == node2->parent)
		{
			//
		}
		else if (this->Size >= 3 && node2->parent->left == node2 && node2->parent->parent->left == node2->parent)
		{
			//
		}
		node2 = nullptr;
		delete node2;

	}
}

int main()
{
	RBT<int>* rbt = new RBT<int>();
	Comporator<int> comporator;
	rbt->Add(15,comporator);
	//rbt->Add(5, comporator);
	//rbt->Add(1, comporator);
    return 0;
}
