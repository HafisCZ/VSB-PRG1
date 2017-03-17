#pragma once

#include <stddef.h>
#include "Node.h"
#include "InstantStack.h"

template <class T> class BinaryTree {
	private:
		BinaryNode<T> *head_;
	public:
		BinaryTree(const T& value) {
			this->head_ = new BinaryNode<T>(value);
		}
		void add(const T& value) {
			BinaryNode<T> *selected = this->head_, *left = NULL, *right = NULL;
			do {
				left = selected->getLeft();
				right = selected->getRight();
				if (selected->getValue() >= value) {
					if (left == NULL) {
						selected->setLeft(value);
						selected = NULL;
					} else selected = left;
				} else {
					if (right == NULL) {
						selected->setRight(value);
						selected = NULL;
					} else selected = right;
				}
			} while (selected != NULL);
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
			this->head_->printHyearchy(o, ' ');
		}
};