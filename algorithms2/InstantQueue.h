#pragma once

#include <iostream>
#include "Node.h"

template <class T> class InstantQueue {
	private:
		Node<T> *youngest, *oldest;
	public:
		InstantQueue() {
			this->youngest = NULL;
			this->oldest = NULL;
		}
		void operator()(const T& value) {
			Node<T> *child = new Node<T>(NULL, value);
			if (this->oldest == NULL || this->youngest == NULL) {
				this->youngest = child;
				this->oldest = this->youngest;
			} else {
				this->youngest->setChild(child);
				this->youngest = child;
			}
		}
		T operator~() {
			Node<T> *newer = this->oldest->getChild();
			T currentValue = this->oldest->getValue();
			delete this->oldest;
			this->oldest = newer;
			return currentValue;
		}
		T peek() const {
			if (this->oldest == NULL) return NULL;
			else return this->oldest->getValue();
		}
		T top() const {
			if (this->youngest == NULL) return NULL;
			else return this->youngest->getValue();
		}
 		bool hasContent() {
			return (this->oldest != NULL);
		}
		void destroy() {
			if (this->oldest != NULL) {
				this->oldest->destroy();
			}
		}
};