#pragma once

#include <cstddef>
#include "Node.h"

template <class T> class InstantStack {
	private:
		Node<T> *head_;
	public:
		InstantStack() {
			this->head_ = NULL;
		}
		void operator()(const T& value) {
			Node<T> *child = new Node<T>(value);
			if (this->head_ == NULL) {
				this->head_ = child;
			} else {
				child->setSubordinate(this->head_);
				this->head_ = child;
			}
		}
		T operator~() {
			Node<T>* older = this->head_->getSubordinate();
			T currentValue = this->head_->getValue();
			delete this->head_;
			this->head_ = older;
			return currentValue;
		}
		T peek() {
			return this->head_->getValue();
		}
		bool hasContent() {
			return (this->head_ != NULL);
		}
		void destroy() {
			if (this->head_ != NULL) {
				this->head_->destroy();
			}
		}
};