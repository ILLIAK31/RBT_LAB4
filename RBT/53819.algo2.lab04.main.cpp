// ALGO2 IS1 224B LAB03
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
	if (parent->parent->right == parent && parent->right == kid && parent->parent->left == nullptr)
	{
		parent->red_black = !parent->red_black;
		parent->parent->red_black = !parent->parent->red_black;
		Node<T>* node3 = parent->parent;
		if (node3->parent != nullptr)
		{
			if (node3->parent->left == node3)
				node3->parent->left = parent;
			else
				node3->parent->right = parent;
		}
		parent->parent = node3->parent;
		node3->parent = parent;
		parent->left = node3;
		node3->right = nullptr;
		node3 = nullptr;
		delete node3;
	}
	else if (parent->parent->right == parent && parent->right == kid && parent->parent->left != nullptr)
	{
		if (parent->parent == this->root)
			this->root = kid->parent;
		parent->parent->right = parent->left;
		parent->left = parent->parent;
		parent->parent = parent->parent->parent;
		parent->left->parent = parent;
		parent->red_black = !parent->red_black;
		parent->parent->red_black = !parent->parent->red_black;
	}
	else if (parent->parent->right == parent && parent->left == kid)
	{
		if (parent->parent != nullptr && parent->parent->parent != nullptr)
		{
			if (parent->parent->parent->left == parent->parent)
				parent->parent->parent->left = kid;
			else
				parent->parent->parent->right = kid;
		}
		//1
		parent->left = kid->right;
		kid->right = parent;
		parent->parent->right = kid;
		kid->parent = parent->parent;
		parent->parent = kid;
		//2
		if (kid->parent == this->root)
			this->root = kid;
		kid->parent->right = kid->left;
		kid->left = kid->parent;
		kid->parent = kid->parent->parent;
		kid->left->parent = kid;
		kid->red_black = false;
		kid->left->red_black = true;
	}
}

template <class T>
void RBT<T>::Rotate_right(Node<T>* kid, Node<T>* parent)
{
	if (parent->parent->left == parent && parent->left == kid && parent->parent->right == nullptr)
	{
		parent->red_black = !parent->red_black;
		parent->parent->red_black = !parent->parent->red_black;
		Node<T>* node3 = parent->parent;
		if (node3->parent != nullptr)
		{
			if (node3->parent->left == node3)
				node3->parent->left = parent;
			else
				node3->parent->right = parent;
		}
		parent->parent = node3->parent;
		node3->parent = parent;
		parent->right = node3;
		node3->left = nullptr;
		node3 = nullptr;
		delete node3;
	}
	else if (parent->parent->left == parent && parent->left == kid && parent->parent->right != nullptr)
	{
		if (parent->parent == this->root)
			this->root = kid->parent;
		parent->parent->left = kid->parent->right;
		kid->parent->right = parent->parent;
		kid->parent->parent = parent->parent->parent;
		parent->parent->parent = kid->parent;
		parent->red_black = !parent->red_black;
		parent->right->red_black = !parent->right->red_black;
	}
	else if (parent->parent->left == parent && parent->right == kid)
	{
		if (parent->parent != nullptr)
		{
			if (parent->parent->parent->left == parent->parent)
				parent->parent->parent->left = kid;
			else
				parent->parent->parent->right = kid;
		}
		//1
		parent->parent->left = kid;
		parent->right = kid->left;
		kid->left = parent;
		kid->parent = parent->parent;
		parent->parent = kid;
		//2
		if (kid->parent == this->root)
			this->root = kid;
		kid->parent->left = kid->right;
		kid->right = kid->parent;
		kid->parent = kid->parent->parent;
		kid->right->parent = kid;
		kid->red_black = false;
		kid->right->red_black = true;
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
		if (this->Size == 3)
		{
			if (this->root->left != nullptr && this->root->right != nullptr) {}
			else if (node2->parent->left == node2 && node2->parent->parent->left == node2->parent)
			{
				this->root = node2->parent;
				node2->parent->right = node2->parent->parent;
				node2->parent->parent = node2->parent->parent->parent;
				node2->parent->right->parent = node2->parent;
				this->root->right->left = nullptr;
				this->root->left->red_black = this->root->right->red_black = true;
			}
			else if (node2->parent->right == node2 && node2->parent->parent->left == node2->parent)
			{
				node2->left = this->root->left;
				node2->right = this->root;
				this->root->left->parent = node2;
				this->root->left->right = nullptr;
				this->root->parent = node2;
				this->root->left = nullptr;
				node2->parent = nullptr;
				this->root = node2;
				this->root->left->red_black = this->root->right->red_black = true;
			}
			else if (node2->parent->right == node2 && node2->parent->parent->right == node2->parent)
			{
				node2->parent->left = node2->parent->parent;
				node2->parent->parent->parent = node2->parent;
				node2->parent->parent->right = nullptr;
				node2->parent->parent = nullptr; 
				this->root = node2->parent;
				this->root->left->red_black = this->root->right->red_black = true;
			}
			else
			{
				node2->left = node2->parent->parent;
				node2->right = node2->parent;
				node2->parent->left = nullptr;
				node2->parent->parent->right = nullptr;
				node2->parent->parent->parent = node2;
				node2->parent->parent = node2;
				node2->parent = nullptr;
				this->root = node2;
				this->root->left->red_black = this->root->right->red_black = true;
			}
		}
		while (node2 != this->root && node2 != nullptr)
		{
			if (node2 == this->root)
				node2->red_black = false;
			else
			{
				if (node2->parent->red_black == true && node2 != this->root && this->Size >= 4)
				{
					if (node2->parent->parent->left == node2->parent)
					{
						if (node2->parent->parent->right != nullptr && node2->parent->parent->right->red_black == true)
						{
							node2->parent->parent->red_black = true;
							node2->parent->red_black = node2->parent->parent->right->red_black = false;
							node2 = node2->parent->parent;
							continue;
						}
						else
						{
							Rotate_right(node2, node2->parent);
							if (node2->parent != nullptr)
								node2 = node2->parent->parent;
							else
								break;
						}
					}
					else if (node2->parent->parent->right == node2->parent)
					{
						if (node2->parent->parent->left != nullptr && node2->parent->parent->left->red_black == true)
						{
							node2->parent->parent->red_black = true;
							node2->parent->red_black = node2->parent->parent->left->red_black = false;
							node2 = node2->parent->parent;
							continue;
						}
						else
						{
							Rotate_left(node2, node2->parent);
							if (node2->parent != nullptr)
								node2 = node2->parent->parent;
							else
								break;
						}
					}
				}
				else
					break;
			}
		}
		this->root->red_black = false;
		node3 = nullptr;
		delete node3;
		node2 = nullptr;
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
	// Testing , main , testing func. : (f,h,i)
	RBT<int>* rbt = new RBT<int>();
	Comporator<int> comporator;
	rbt->Add(10,comporator);
	rbt->Add(85, comporator);
	rbt->Add(15, comporator);
	rbt->Add(70, comporator);
	rbt->Add(20, comporator);
	rbt->Add(60, comporator);
	rbt->Add(30, comporator); 
	rbt->Add(50, comporator); // Error
	//rbt->Add(65, comporator);
	//rbt->Add(80, comporator);
	//rbt->Add(90, comporator);
	//rbt->Add(40, comporator);
	//rbt->Add(5, comporator);
	//rbt->Add(55, comporator);
	rbt->Print();
    return 0;
}
