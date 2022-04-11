#ifndef LISTELEMENT_H
#define LISTELEMENT_H

template <typename T>
struct ListElement {
	T value;
	ListElement* previous;
	ListElement* next;
};

#endif // !LISTELEMENT_H

