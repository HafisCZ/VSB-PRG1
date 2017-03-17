#pragma once

#include <stddef.h>
#include <ostream>

template <class C> class Node {
	protected:
		Node<C> **child, *parent;
		C value;
		bool set;
		int childCount;
	public:
		Node(const C& value, Node<C> *parent = NULL, bool updateParent = false) {
			this->child = NULL;
			this->childCount = 0;
			this->parent = parent;
			if (this->parent != NULL && updateParent) this->parent->addChild(this);
			this->value = value;
			this->set = true;
		}
		inline Node** getChildren() {
			return this->child;
		}
		inline Node* getParent() {
			return this->parent;
		}
		inline Node* getChild() {
			return (this->childCount > 0 ? this->child[0] : NULL);
		}
		inline Node* getChild(int index) {
			return (index >= 0 && index < this->childCount ? this->child[index] : NULL);
		}
		inline C getValue() {
			return this->value;
		}
		inline int countChildren() {
			return this->childCount;
		}
		inline bool hasValue() {
			return this->set;
		}
		inline bool hasChild() {
			return (this->childCount > 0);
		}
		void fill(int count) {
			if (count == 0) this->child = NULL;
			else if (count > 0 && count != this->childCount) {
				Node<C> **temporary = new Node<C>*[count];
				for (int i = 0; i < this->childCount; i++) temporary[i] = this->child[i];
				for (int i = this->childCount; i < count; i++) temporary[i] = NULL;
				delete[] this->child;
				this->child = temporary;
				this->childCount = count;
			}
		}
		void setChild(Node<C> **child, int count) {
			this->child = child;
			this->childCount = (child == NULL ? 0 : count);
		}
		void setChild(Node<C> *child, int position) {
			if (position >= 0) {
				if (position >= this->childCount) fill(position + 1);
				this->child[position] = child;
			}
		}
		void setChild(Node<C> *child) {
			setChild(child, 0);
		}
		void addChild(Node<C> *child) {
			fill(this->childCount + 1);
			this->child[this->childCount - 1] = child;
		}
		void destroy() {
			if (this->childCount > 0) {
				for (int i = 0;i < this->childCount; i++) this->child[i]->destroy();
			}
			delete this;
		}
		void setValue(const C& value) {
			this->value = value;
		}
		void process(void (*f)(C)) {
			(*f)(C);
		}
};

template <class C> class BinaryNode {
	private:
		BinaryNode<C> *left, *right;
		bool set;
		C value;
	public:
		BinaryNode(const C& value) {
			this->value = value;
			this->set = true;
			this->left = NULL;
			this->right = NULL;
		}
		inline BinaryNode<C>* getLeft() {
			return this->left;
		}
		inline BinaryNode<C>* getRight() {
			return this->right;
		}
		inline C getValue() {
			return this->value;
		}
		inline bool hasLeft() {
			return (this->left != NULL);
		}
		inline bool hasRight() {
			return (this->right != NULL);
		}
		inline bool hasValue() {
			return (this->set);
		}
		void setLeft(BinaryNode<C> *left) {
			this->left = left;
		}
		void setLeft(const C& value) {
			this->left = new BinaryNode<C>(value);
		}
		void setRight(BinaryNode<C> *right) {
			this->right = right;
		}
		void setRight(const C& value) {
			this->right = new BinaryNode<C>(value);
		}
		void process(void(*f)(C)) {
			(*f)(C);
		}
		void printHyearchy(std::ostream& o, char delim) {
			if (hasLeft()) this->getLeft()->printHyearchy(o, delim);
			o << delim << this->value;
			if (hasRight()) this->getRight()->printHyearchy(o, delim);
		}
};