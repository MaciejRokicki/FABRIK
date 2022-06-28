#include "headers/node.h"

template<typename T>
Node<T>::Node() { }

template<typename T>
Node<T>::Node(T value) {
	this->value = value;
}

template<typename T>
void Node<T>::next(T value) {
	Node<T>* newNode = new Node<T>();
	newNode->parent = this;
	newNode->value = value;

	this->child.push_back(newNode);
}