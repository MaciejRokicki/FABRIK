#ifndef TREE_H
#define TREE_H

#include <functional>

#include "node.h"
#include "modelProgram.h"

template <typename T>
class Tree {
private:
	Node<T>* root;
	void Preorder(Node<T>* node, std::function<void(T*)> func);
public:
	Tree(Node<T>* root);
	void Preorder(std::function<void(T*)> func);
};

#endif // !TREE_H