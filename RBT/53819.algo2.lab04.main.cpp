// ALGO2 IS1 224B LAB04
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>
#include <vector>
#include <string>

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
	Node<T>* nоdе3 = kid->right;
	if (nоdе3 != nullptr)
	{
		kid->right = nоdе3->left; // back to node which we add in left
		if (nоdе3->left != nullptr)
			nоdе3->left->parent = kid;
		nоdе3->parent = kid->parent;
		if (kid->parent == nullptr) // check pos opt1
			this->root = nоdе3; // root is node
		else if (kid != kid->parent->left) // opt2
			kid->parent->right = nоdе3; // n.r
		else // opt3
			kid->parent->left = nоdе3; // n.l
		nоdе3->left = kid;
		kid->parent = nоdе3;
	}
	nоdе3 = nullptr;
	delete nоdе3;
}

template <class T>
void RBT<T>::Rotate_right(Node<T>* kid, Node<T>* parent)
{
	Node<T>* nоdе3 = kid->left;
	if (nоdе3 != nullptr)
	{
		kid->left = nоdе3->right; // back to node which we add in right
		if (nоdе3->right != nullptr)
			nоdе3->right->parent = kid;
		nоdе3->parent = kid->parent;
		if (kid->parent == nullptr) // check pos opt1
			this->root = nоdе3; // root is node
		else if (kid != kid->parent->right) // opt2
			kid->parent->left = nоdе3; // n.l
		else // opt3
			kid->parent->right = nоdе3; // n.r
		nоdе3->right = kid;
		kid->parent = nоdе3;
	}
	nоdе3 = nullptr;
	delete nоdе3;
}

template <class T>
void RBT<T>::Add(T Value, Comporator<T> comporator)
{
	Node<T>* node2 = this->root; //part 1
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
					node->value = Value;
					node->ID = this->Size;
					node->left = node->right = nullptr;
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
	}
	while (node2 != this->root && node2 != nullptr && node2->parent->red_black == true) // part 2
	{
		if (node2->parent->parent->right == node2->parent) // if path is right
		{
			if (node2->parent->parent->left != nullptr && node2->parent->parent->left->red_black == true) // option 1 with path to left and color red
			{
				node2->parent->parent->red_black = true; //change color to red
				node2->parent->red_black = node2->parent->parent->left->red_black = false; // color to black
				node2 = node2->parent->parent; // back 2 time
			}
			else // else option
			{
				if (node2->parent->left == node2)
				{
					node2 = node2->parent; // back 1 time
					Rotate_right(node2, node2->parent); // rot.r  
				}
				node2->parent->parent->red_black = true; // color to red
				node2->parent->red_black = false; // color to black
				Rotate_left(node2->parent->parent, node2->parent->parent->parent); //rot.l 
			}
		}
		else // path is left
		{
			if (node2->parent->parent->right != nullptr && node2->parent->parent->right->red_black == true) // option 1 with path to right and color red
			{
				node2->parent->parent->red_black = true; // color to red
				node2->parent->red_black = node2->parent->parent->right->red_black = false; // color to black
				node2 = node2->parent->parent; // back 2 time
			}
			else // else option
			{
				if (node2->parent->right == node2)
				{
					node2 = node2->parent; // back 1 time
					Rotate_left(node2, node2->parent); // rot.l
				}
				node2->parent->parent->red_black = true; // color to red
				node2->parent->red_black = false; // color to black
				Rotate_right(node2->parent->parent, node2->parent->parent->parent); // rot.r 
			}
		}
		if (node2 == this->root) // breaking when root
			break;
	}
	node2 = nullptr;
	delete node2;
	this->root->red_black = false; // root always black
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
	std::cout << "\t| BST |\n" << "\t| Size : " << this->Size << " |\n";
	std::cout << "\t| Height : " << this->Get_Height() << " |\n";
	std::vector<Node<T>*> vec;
	Pre_Order(this->root, vec);
	for (Node<T>* node : vec)
	{
		std::string parent, left, right , color;
		color = (node->red_black) ? "Red" : "Black";
		parent = (node->parent == nullptr) ? "NULL" : std::to_string(node->parent->ID);
		left = (node->left == nullptr) ? "NULL" : std::to_string(node->left->ID);
		right = (node->right == nullptr) ? "NULL" : std::to_string(node->right->ID);
		std::cout << "| ID : " << node->ID << " | " << color  << ", p : " << parent << " , l : " << left << " , r : " << right << " | Value : " << node->value << " |\n";
	}
}

int main()
{
	// Testing main, main , testing functions without adding
	RBT<int>* rbt = new RBT<int>();
	Comporator<int> comporator;
	rbt->Add(10,comporator);
	rbt->Add(85, comporator);
	rbt->Add(15, comporator);
	rbt->Add(70, comporator);
	rbt->Add(20, comporator);
	rbt->Add(60, comporator);
	rbt->Add(30, comporator); 
	rbt->Add(50, comporator);
	rbt->Add(65, comporator);
	rbt->Add(80, comporator);
	rbt->Add(90, comporator);
	rbt->Add(40, comporator);
	rbt->Add(5, comporator);
	rbt->Add(55, comporator);
	rbt->Print();
    return 0;
}
