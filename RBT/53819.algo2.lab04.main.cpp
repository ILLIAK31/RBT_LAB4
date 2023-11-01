// ALGO2 IS1 224B LAB03
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>
#include <vector>

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
	bool red_black{ true };
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
	Node<T>* Search(T Value, Comporator<T> comporator);
	void Pre_Order(Node<T>* node, std::vector<Node<T>*>& vec);
	void In_Order(Node<T>* node, std::vector<Node<T>*>& vec);
	void Delete(Node<T>* Node);
	void Clear();
	void Search_Height(Node<T>* node, int& height, int& height_max);
	int Get_Height();
	void Print();
};

template<class T>
RBT<T>::~RBT() {}

template <class T>
void RBT<T>::Rotate_left(Node<T>* kid, Node<T>* parent)
{
	if (parent->right != nullptr)
	{
		if (parent == this->root)
			this->root = kid;
		if (kid->left != nullptr)
		{
			parent->right = kid->left;
			kid->left->parent = parent;
			parent->left = nullptr;
		}
		else if (kid->right != nullptr)
		{
			parent->right = kid->right;
			parent->right = nullptr;
		}
		kid->left = parent;
		kid->parent = parent->parent;
		parent->parent = kid;
	}
}

template <class T>
void RBT<T>::Rotate_right(Node<T>* kid, Node<T>* parent)
{
	if (parent->left != nullptr)
	{
		if (parent == this->root)
			this->root = kid;
		if (kid->right != nullptr)
		{
			parent->left = kid->right;
			kid->right->parent = parent;
		}
		else if (kid->left != nullptr)
		{
			parent->left = nullptr;
		}
		kid->right = parent;
		kid->parent = parent->parent;
		parent->parent = kid;
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
					node2 = node;
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
					node2 = node;
					break;
				}
			}
		}
		//
		Node<T>* node3;
		//
		node3 = nullptr;
		delete node3;
		////
		//if (node2->parent->parent == this->root)
		//{
		//	if (this->Size >= 3 && (node2->parent->parent->right == nullptr || node2->parent->parent->right->red_black == false ) && node2->parent->right == node2 && node2->parent->parent->left == node2->parent)
		//	{
		//		Rotate_left(node2->parent, node2->parent->parent);
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->left == nullptr ||node2->parent->parent->left->red_black == false) && node2->parent->left == node2 && node2->parent->parent->right == node2->parent)
		//	{
		//		Rotate_right(node2->parent, node2->parent->parent);
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->right == nullptr || node2->parent->parent->right->red_black == false) && node2->parent->left == node2 && node2->parent->parent->left == node2->parent)
		//	{
		//		Rotate_left(node2->parent, node2->parent->parent);
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->left == nullptr ||node2->parent->parent->left->red_black == false) && node2->parent->right == node2 && node2->parent->parent->right == node2->parent)
		//	{
		//		Rotate_right(node2->parent, node2->parent->parent);
		//	}
		//}
		//else
		//{
		//	if (this->Size >= 3 && node2->parent->parent->right->red_black == true)
		//	{
		//		node2->parent->red_black = !node2->parent->red_black;
		//		node2->parent->parent->red_black = !node2->parent->parent->red_black;
		//		if (node2->parent->parent->right != nullptr)
		//			node2->parent->parent->right->red_black = !node2->parent->parent->right->red_black;
		//		else
		//			node2->parent->parent->left->red_black = !node2->parent->parent->left->red_black;
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->right->red_black == false || node2->parent->parent->right == nullptr) && node2->parent->right == node2 && node2->parent->parent->left == node2->parent)
		//	{
		//		Rotate_left(node2->parent, node2->parent->parent);
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->left->red_black == false || node2->parent->parent->left == nullptr) && node2->parent->left == node2 && node2->parent->parent->right == node2->parent)
		//	{
		//		Rotate_right(node2->parent->parent, node2->parent);
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->right->red_black == false || node2->parent->parent->right == nullptr) && node2->parent->left == node2 && node2->parent->parent->left == node2->parent)
		//	{
		//		Rotate_left(node2->parent, node2->parent->parent);
		//	}
		//	else if (this->Size >= 3 && (node2->parent->parent->left->red_black == false || node2->parent->parent->left == nullptr) && node2->parent->right == node2 && node2->parent->parent->right == node2->parent)
		//	{
		//		Rotate_right(node2->parent, node2->parent->parent);
		//	}
		//}
		////
		node2 = node3 = nullptr;
		delete node2;
	}
}

template<class T>
Node<T>* RBT<T>::Search(T Value, Comporator<T> comporator)
{
	Node<T>* node2 = this->root;
	while (true)
	{
		if (comporator(Value, node2->value))
		{
			if (node2->right != nullptr)
				node2 = node2->right;
			else
				break;
		}
		else
		{
			if (Value == node2->value)
				return node2;
			else if (node2->left != nullptr)
				node2 = node2->left;
			else
				break;
		}
	}
	node2 = nullptr;
	delete node2;
	return nullptr;
}

template<class T>
void RBT<T>::Pre_Order(Node<T>* node, std::vector<Node<T>*>& vec)
{
	if (node != nullptr)
	{
		vec.push_back(node);
		Pre_Order(node->left, vec);
		Pre_Order(node->right, vec);
	}
}

template<class T>
void RBT<T>::In_Order(Node<T>* node, std::vector<Node<T>*>& vec)
{
	if (node != nullptr)
	{
		In_Order(node->left, vec);
		vec.push_back(node);
		In_Order(node->right, vec);
	}
}

template<class T>
void RBT<T>::Delete(Node<T>* node)
{
	Node<T>* Tail;
	Node<T>* Head1;
	if (node->left == nullptr && node->right == nullptr)
	{
		if (this->root != node)
		{
			Tail = node->parent;
			if (Tail->left == node)
				Tail->left = nullptr;
			else
				Tail->right = nullptr;
		}
		else
			this->root = nullptr;
		node->ID = node->value = NULL;
		delete node;
		node = nullptr;
		--this->Size;
	}
	else if (node->left == nullptr && node->right != nullptr)
	{
		if (this->root != node)
		{
			Tail = node->parent;
			Head1 = node->right;
			if (Tail->left == node)
				Tail->left = Head1;
			else
				Tail->right = Head1;
			Head1->parent = Tail;
		}
		else
		{
			node->right->parent = nullptr;
			this->root = node->right;
		}
		node->ID = node->value = NULL;
		delete node;
		node = nullptr;
		--this->Size;
	}
	else if (node->left != nullptr && node->right == nullptr)
	{
		if (this->root != node)
		{
			Tail = node->parent;
			Head1 = node->left;
			if (Tail->left == node)
				Tail->left = Head1;
			else
				Tail->right = Head1;
			Head1->parent = Tail;
		}
		else
		{
			node->left->parent = nullptr;
			this->root = node->left;
		}
		node->ID = node->value = NULL;
		delete node;
		node = nullptr;
		--this->Size;
	}
	else
	{
		Node<T>* node2 = node;
		node2 = node2->right;
		while (true)
		{
			if (node2->left == nullptr)
				break;
			else
				node2 = node2->left;
		}
		node->value = node2->value;
		node->ID = node2->ID;
		this->Delete(node2);
		node2 = nullptr;
		delete node2;
	}
	Tail = Head1 = nullptr;
	delete Tail;
	delete Head1;
}

template<class T>
void RBT<T>::Clear()
{
	while (this->Size != 0)
		this->Delete(this->root);
}

template<class T>
void RBT<T>::Search_Height(Node<T>* node, int& height, int& height_max)
{
	height = 0;
	if (node != nullptr)
	{
		Search_Height(node->left, height, height_max);
		Search_Height(node->right, height, height_max);
		if (node->left == nullptr && node->right == nullptr)
		{
			while (node != nullptr)
			{
				++height;
				node = node->parent;
			}
		}
		height_max = (height > height_max) ? height : height_max;
	}
}

template<class T>
int RBT<T>::Get_Height()
{
	if (this->Size == 0)
		return 0;
	Node<T>* node2 = this->root;
	int height{ 0 }, height_max{ 0 };
	Search_Height(this->root, height, height_max);
	return (height_max - 1);
}

template<class T>
void RBT<T>::Print()
{
	//
}

int main()
{
	// Testing , main
	RBT<int>* rbt = new RBT<int>();
	Comporator<int> comporator;
    return 0;
}
