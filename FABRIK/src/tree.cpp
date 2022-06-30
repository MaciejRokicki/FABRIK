#include "headers/tree.h"

template <typename T>
Tree<T>::Tree(Node<T>* root) {
	this->root = root;
}

template <typename T>
void Tree<T>::Preorder(std::function<void(Node<T>*)> func) {
	Preorder(this->root, func);
}

template<typename T>
void Tree<T>::Preorder(Node<T>* node, std::function<void(Node<T>*)> func) {
	if (node) {
		func(node);

		for (int i = 0; i < node->child.size(); i++) {
			Preorder(node->child.at(i), func);
		}
	}
}

template <typename T>
void Tree<T>::Inorder(std::function<void(Node<T>*)> func) {
	Inorder(this->root, func);
}

template<typename T>
void Tree<T>::Inorder(Node<T>* node, std::function<void(Node<T>*)> func) {
	if (node) {
		for (int i = 0; i < node->child.size(); i++) {
			Inorder(node->child.at(i), func);
		}

		func(node);
	}
}