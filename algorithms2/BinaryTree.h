#pragma once

#include <cstddef>
#include "BinaryNode.h"
#include "InstantStack.h"

template <class T> class BinaryTree {
	private:
	BinaryNode<T> *head_;
	public:
		BinaryTree() {
			this->head_ = NULL;
		}
		~BinaryTree() {
			if (this->head_ != NULL) this->head_->remove();
		}
		void add(const T& value) {
			if (this->head_ == NULL) this->head_ = new BinaryNode<T>(value);
			else {
				BinaryNode<T> *selected = this->head_, *target = NULL;
				while (selected != NULL) {
					target = selected->getSide(selected->getValue() >= value ? false : true);
					if (target == NULL) selected->setSide(value, selected->getValue() < value);
					selected = (target == NULL ? NULL : target);
				}
			}
		}
		void process(void (*f)(T)) {
			InstantStack<BinaryNode<T>*> buffer;
			BinaryNode<T> *current = NULL;
			buffer(this->head_);
			while (buffer.hasContent()) {
				current = ~buffer;
				(*f)(current->getValue());
				if (current->hasLeft()) buffer(current->getLeft());
				if (current->hasRight()) buffer(current->getRight());
			}
			buffer.destroy();
		}
		void printHyearchy(std::ostream& o) {
			if (this->head_ != NULL) this->head_->printHyearchy(o, ' ');
		}
};