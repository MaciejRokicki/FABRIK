#ifndef LIST_H
#define LIST_H

#include <stdexcept>

#include "listElement.h"

template <typename T>
class List {
private:
	ListElement<T>* head_;
	ListElement<T>* last_;
	int count_;
public:
	List() : count_(0) {
		head_ = new ListElement<T>;
		head_->previous = NULL;
		head_->next = NULL;
		last_ = head_;
	}

	int Size() {
		return count_;
	};

	void Push(T& value) {
		count_++;

		ListElement<T>* new_element = new ListElement<T>;
		new_element->value = value;
		new_element->previous = last_;
		new_element->next = NULL;

		last_->next = new_element;
		last_ = new_element;

		if (count_ == 1) {
			head_ = new_element;
		}
	};

	T& At(int index) {
		if (0 < count_ && index >= count_) {
			throw std::out_of_range("");
		}

		ListElement<T>* current_element = head_;

		for (int i = 0; i < index; i++) {
			current_element = current_element->next;
		}

		return current_element->value;
	}

	void Clear() {
		ListElement<T>* current_element = head_->next;

		for (int i = 1; i < count_; i++) {
			delete current_element->previous;
			current_element = current_element->next;
		}

		count_ = 0;
	}

	~List() {
		Clear();
	}
};

#endif // !LIST_H