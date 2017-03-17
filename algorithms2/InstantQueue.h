#pragma once

#include <stddef.h>
#include "Node.h"

template <class T> class InstantQueue {
	private:
		Node<T> *youngest_, *oldest_;
	public:
		InstantQueue() {
			this->youngest_ = NULL;
			this->oldest_ = NULL;
		}
		void operator()(const T& value) {
			Node<T> *child = new Node<T>(value);
			if (this->oldest_ == NULL || this->youngest_ == NULL) {
				this->youngest_ = child;
				this->oldest_ = this->youngest_;
			} else {
				this->youngest_->setSubordinate(child);
				this->youngest_ = child;
			}
		}
		T operator~() {
			Node<T> *newer = this->oldest_->getSubordinate();
			T currentValue = this->oldest_->getValue();
			delete this->oldest_;
			this->oldest_ = newer;
			return currentValue;
		}
		T peek() const {
			if (this->oldest_ == NULL) return NULL;
			else return this->oldest_->getValue();
		}
		T top() const {
			if (this->youngest_ == NULL) return NULL;
			else return this->youngest_->getValue();
		}
 		bool hasContent() {
			return (this->oldest_ != NULL);
		}
		void destroy() {
			if (this->oldest_ != NULL) {
				this->oldest_->destroy();
			}
		}
};