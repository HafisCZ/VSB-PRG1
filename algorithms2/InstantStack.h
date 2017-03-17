#pragma once

#include <stddef.h>
#include "Node.h"

template <class T> class InstantStack {
	private:
		Node<T> *head;
	public:
		InstantStack() {
			this->head = NULL;
		}
		void operator()(const T& value) {
			Node<T> *child = new Node<T>(value);
			if (this->head == NULL) {
				this->head = child;
			} else {
				child->setChild(this->head);
				this->head = child;
			}
		}
		T operator~() {
			Node<T>* older = this->head->getChild();
			T currentValue = this->head->getValue();
			delete this->head;
			this->head = older;
			return currentValue;
		}
		T peek() {
			return this->head->getValue();
		}
		bool hasContent() {
			return (this->head != NULL);
		}
		void destroy() {
			if (this->head != NULL) {
				this->head->destroy();
			}
		}
};