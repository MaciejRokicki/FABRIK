#ifndef TREE_H
#define TREE_H

#include <functional>

#include "node.h"
#include "modelProgram.h"

template <typename T>
class Tree {
private:
	void Preorder(Node<T>* node, std::function<void(Node<T>*)> func);
public:
	Node<T>* root;
	Tree(Node<T>* root);
	void Preorder(std::function<void(Node<T>*)> func);
};

#endif // !TREE_H