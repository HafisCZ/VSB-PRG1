#pragma once

#include <iostream>

template <class C> class Node {
	private:
		Node<C> **child, *parent;
		C value;
		bool set;
		int childCount;
	public:
		Node(Node<C> *parent, const C& value) {
			this->child = NULL;
			this->childCount = 0;
			this->parent = parent;
			if (this->parent != NULL) {
				this->parent->addChild(this);
			}
			this->value = value;
			this->set = true;
		}
		inline Node* getParent() {
			return this->parent;
		}
		Node* getChild() {
			if (this->childCount == 0) return NULL;
			else return this->child[0];
		}
		Node* getChild(int children) {
			if (children >= this->childCount || children < 0) return NULL;
			else return this->child[children];
		}
		Node** getChildren() {
			return this->child;
		}
		void setChild(Node<C> **childs, int childCount) {
			if (child == NULL) {
				this->child = NULL;
				this->childCount = 0;
			} else {
				this->child = childs;
				this->childCount = childCount;
			}
		}
		void setChild(Node<C> *child) {
			if (child == NULL) {
				this->child = NULL;
				this->childCount = 0;
			} else {
				this->child = new Node<C>*[1];
				this->child[0] = child;
				this->childCount = 1;
			}
		}
		void addChild(Node<C> *child) {
			if (child != NULL) {
				if (this->childCount > 0) {
					Node<C>** temporary = new Node<C>*[this->childCount + 1];
					for (int i = 0; i < this->childCount; i++) {
						temporary[i] = this->child[i];
					}
					temporary[this->childCount] = child;
					delete[] this->child;
					this->child = temporary;
				} else {
					this->child = new Node<C>*[1];
					this->child[0] = child;
				}
				this->childCount++;
			}
		}
		void destroy() {
			if (this->childCount > 0) {
				for (int i = 0; i < this->childCount; i++) {
					this->child[i]->destroy();
				}
			}
			delete this;
		}
		inline C getValue() {
			return this->value;
		}
		void setValue(const C& value) {
			this->value = value;
			this->set = true;
		}
		inline bool hasValue() {
			return this->set;
		}
		inline int countChildren() {
			return this->childCount;
		}
		inline bool hasChild() {
			return (this->childCount > 0);
		}
};