#pragma once

#include <cstddef>
#include "Node.h"
#include "InstantQueue.h"
#include "InstantStack.h"

template <class T> class NodeTree {
	private:
		GenericNode<T> *head_;
	public:
		NodeTree(GenericNode<T>* node) {
			this->head_ = node;
		}
		void BreadthFirstSearch() {
			InstantQueue<GenericNode<T>*> buffer;
			GenericNode<T> *current = NULL;
			buffer(this->head_);
			while (buffer.hasContent()) {
				current = ~buffer;
				std::cout << " " << current->getValue();
				for (unsigned int i = 0; i < current->nSubordinates(); i++) {
					buffer(current->getSubordinate(i));
				}
			}
		}
		GenericNode<T>* BreadthFirstSearch(const T& searchValue) {
			InstantQueue<GenericNode<T>*> buffer;
			GenericNode<T> *current = NULL;
			buffer(this->head_);
			while (buffer.hasContent()) {
				iterations++;
				current = ~buffer;
				if (current->getValue() == searchValue) {
					buffer.destroy();
					return current;
				}
				for (int i = 0; i < current->nSubordinates(); i++) {
					buffer(current->getChild(i));
				}
			}
		}
		void DepthFirstSearch() {
			InstantStack<GenericNode<T>*> buffer;
			GenericNode<T> *current = NULL;
			buffer(this->head_);
			while (buffer.hasContent()) {
				current = ~buffer;
				std::cout << " " << current->getValue();
				for (unsigned int i = 0; i < current->nSubordinates(); i++) {
					buffer(current->getSubordinate(i));
				}
			}
		}
		GenericNode<T>* DepthFirstSearch(const T& searchValue) {
			InstantStack<GenericNode<T>*> buffer;
			GenericNode<T> *current = NULL;
			buffer(this->head_);
			while (buffer.hasContent()) {
				current = ~buffer;
				if (current->getValue() == searchValue) {
					buffer.destroy();
					return current;
				}
				for (int i = 0; i < current->countChildren(); i++) {
					buffer(current->getChild(i));
				}
			}
		}
		void destroy() {
			if (this->head_ != NULL) {
				this->head_->remove(true);
			}
		}
};