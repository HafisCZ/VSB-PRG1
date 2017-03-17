#pragma once

#include <stddef.h>
#include "Node.h"
#include "InstantQueue.h"
#include "InstantStack.h"

template <class T> class NodeTree {
	private:
		Node<T> *head;
	public:
		NodeTree(Node<T>* node) {
			this->head = node;
		}
		void BreadthFirstSearch() {
			InstantQueue<Node<T>*> buffer;
			Node<T> *current = NULL;
			buffer(this->head);
			while (buffer.hasContent()) {
				current = ~buffer;
				std::cout << " " << current->getValue();
				for (int i = 0; i < current->countChildren(); i++) {
					buffer(current->getChild(i));
				}
			}
			buffer.destroy();
		}
		Node<T>* BreadthFirstSearch(const T& searchValue) {
			InstantQueue<Node<T>*> buffer;
			Node<T> *current = NULL;
			buffer(this->head);
			while (buffer.hasContent()) {
				iterations++;
				current = ~buffer;
				if (current->getValue() == searchValue) {
					buffer.destroy();
					return current;
				}
				for (int i = 0; i < current->countChildren(); i++) {
					buffer(current->getChild(i));
				}
			}
			buffer.destroy();
		}
		void DepthFirstSearch() {
			InstantStack<Node<T>*> buffer;
			Node<T> *current = NULL;
			buffer(this->head);
			while (buffer.hasContent()) {
				current = ~buffer;
				std::cout << " " << current->getValue();
				for (int i = 0; i < current->countChildren(); i++) {
					buffer(current->getChild(i));
				}
			}
			buffer.destroy();
		}
		Node<T>* DepthFirstSearch(const T& searchValue) {
			InstantStack<Node<T>*> buffer;
			Node<T> *current = NULL;
			buffer(this->head);
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
			buffer.destroy();
		}
		void destroy() {
			if (this->head != NULL) {
				this->head->destroy();
			}
		}
};