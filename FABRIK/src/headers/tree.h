#ifndef TREE_H
#define TREE_H

#include "node.h"

template <typename T>
class Tree {
public:
	Node<T>* root;

	Tree(Node<T>* root);
	void Preorder(std::function<void(Node<T>*)> func);
	void Preorder(Node<T>* node, std::function<void(Node<T>*)> func);
	void Inorder(std::function<void(Node<T>*)> func);
	void Inorder(Node<T>* node, std::function<void(Node<T>*)> func);
};

#endif // !TREE_H