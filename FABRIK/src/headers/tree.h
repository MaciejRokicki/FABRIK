#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "listElement.h"

template <typename T>
class Tree {
private:
	List<List<T>>* nodes;
public:
	Tree() {
		nodes = new List<List<T>>();
		nodes->Push(List<T>());
	}

	int Size() {
		return nodes->Size();
	}

	List<T>& At(int list_index) {
		if (0 < nodes->Size() && list_index >= nodes->Size()) {
			throw std::out_of_range("");
		}

		return nodes->At(list_index);;
	}

	T& At(int list_index, int index) {
		if (0 < nodes->Size() && list_index >= nodes->Size()) {
			throw std::out_of_range("");
		}

		List<T>& current_list = nodes->At(list_index);

		if (0 < current_list.Size() && index >= current_list.Size()) {
			throw std::out_of_range("");
		}

		return current_list.At(index);
	}

	~Tree() {
		delete nodes;
	}
};

#endif // !TREE_H
