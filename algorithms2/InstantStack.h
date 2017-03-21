#pragma once

#include <cstddef>
#include "Node.h"

template <class T> class InstantStack {
	private:
		GenericNode<T> *head_;
	public:
		InstantStack() {
			this->head_ = NULL;
		}

		~InstantStack() {
			if (this->head_ != NULL) this->head_->remove(true);
		}

		void operator()(const T& value) {
			GenericNode<T> *child = new GenericNode<T>(value);
			child->setSubordinate(this->head_);
			this->head_ = child;
		}

		T operator~() {
			GenericNode<T>* older = this->head_->getSubordinate();
			T currentValue = this->head_->getValue();
			this->head_->remove();
			this->head_ = older;
			return currentValue;
		}

		T peek() const {
			return this->head_->getValue();
		}

		bool hasContent() {
			return (this->head_ != NULL);
		}
};