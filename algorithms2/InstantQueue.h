#pragma once

#include <cstddef>
#include "Node.h"

template <class T> class InstantQueue {
	private:
		GenericNode<T> *youngest_, *oldest_;
	public:
		InstantQueue() {
			this->youngest_ = NULL;
			this->oldest_ = NULL;
		}

		~InstantQueue() {
			if (this->oldest_ != NULL) this->oldest_->remove(true);
		}

		void operator()(const T& value) {
			GenericNode<T> *child = new GenericNode<T>(value);
			if (this->oldest_ == NULL || this->youngest_ == NULL) {
				this->youngest_ = child;
				this->oldest_ = this->youngest_;
			} else {
				this->youngest_->setSubordinate(child);
				this->youngest_ = child;
			}
		}

		T operator~() {
			GenericNode<T> *newer = this->oldest_->getSubordinate();
			T currentValue = this->oldest_->getValue();
			this->oldest_->remove();
			this->oldest_ = newer;
			return currentValue;
		}

		T peek() const {
			return this->oldest_->getValue();
		}

 		bool hasContent() {
			return (this->oldest_ != NULL);
		}
};