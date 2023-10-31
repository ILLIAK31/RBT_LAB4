#include <iostream>

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
Node<T>::~Node(){}

template <class T>
class RBT
{
public:
	RBT()=default;
	~RBT();
	Node<T>* root = nullptr;
	int Size{ 0 };
};

template<class T>
RBT<T>::~RBT(){}

int main()
{
    //
    return 0;
}
