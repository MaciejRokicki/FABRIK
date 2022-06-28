#include "headers/tree.h"

template <typename T>
Tree<T>::Tree(Node<T>* root) {
	this->root = root;
}

template<typename T>
void Tree<T>::Preorder(Node<T>* node, std::function<void(T*)> func) {
	if (node) {
		func(&node->value);

		for (int i = 0; i < node->child.size(); i++) {
			Preorder(node->child.at(i), func);
		}
	}
}

template <typename T>
void Tree<T>::Preorder(std::function<void(T*)> func) {
	Preorder(this->root, func);
}