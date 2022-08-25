#ifndef NODE_H
#define NODE_H

#include <vector>

template <typename T>
struct Node {
	T value;
	std::vector<Node<T>*> child;
	Node<T>* parent = NULL;

	Node();
	Node(T value);
	void Next(T value);
};

#endif // !NODE_H