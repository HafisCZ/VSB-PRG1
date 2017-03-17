#pragma once

#include <cstddef>
#include <ostream>

template <class C> class Node {
	private:
		Node<C> **subordinate_, *superior_;
		C value_;
		int subordinate_count_;
		bool set_;
	public:
		Node(const C& value, Node<C> *superior = NULL, bool update_superior = false) {
			this->subordinate_ = NULL;
			this->subordinate_count_ = 0;
			this->superior_ = superior;
			if (this->superior_ != NULL && update_superior) this->superior_->addSubordinate(this);
			this->value_ = value;
			this->set_ = true;
		}
		inline Node** getSubordinates() {
			return this->subordinate_;
		}
		inline Node* getSuperior() {
			return this->superior_;
		}
		inline Node* getSubordinate() {
			return (this->subordinate_count_ > 0 ? this->subordinate_[0] : NULL);
		}
		inline Node* getSubordinateAt(int index) {
			return (index >= 0 && index < this->subordinate_count_ ? this->subordinate_[index] : NULL);
		}
		inline C getValue() {
			return this->value_;
		}
		inline int nSubordinates() {
			return this->subordinate_count_;
		}
		inline bool isSet() {
			return this->set_;
		}
		inline bool hasSubordinate() {
			return (this->subordinate_count_ > 0);
		}
		inline bool hasSuperior() {
			return (this->subordinate_ != NULL);
		}
		void fill(int count) {
			if (count == 0) this->subordinate_ = NULL;
			else if (count > 0 && count != this->subordinate_count_) {
				Node<C> **temporary = new Node<C>*[count];
				for (int i = 0; i < this->subordinate_count_; i++) temporary[i] = this->subordinate_[i];
				for (int i = this->subordinate_count_; i < count; i++) temporary[i] = NULL;
				delete[] this->subordinate_;
				this->subordinate_ = temporary;
				this->subordinate_count_ = count;
			}
		}
		void setSubordinates(Node<C> **child, int count) {
			this->subordinate_ = child;
			this->subordinate_count_ = (child == NULL ? 0 : count);
		}
		void setSubordinateAt(Node<C> *child, int position) {
			if (position >= 0) {
				if (position >= this->subordinate_count_) fill(position + 1);
				this->subordinate_[position] = child;
			}
		}
		inline void setSubordinate(Node<C> *child) {
			setSubordinateAt(child, 0);
		}
		void addSubordinate(Node<C> *child) {
			fill(this->subordinate_count_ + 1);
			this->subordinate_[this->subordinate_count_ - 1] = child;
		}
		void destroy() {
			if (this->subordinate_count_ > 0) {
				for (int i = 0;i < this->subordinate_count_; i++) this->subordinate_[i]->destroy();
			}
			delete this;
		}
		inline void setValue(const C& value) {
			this->value_ = value;
		}
		void process(void (*f)(C)) {
			(*f)(C);
		}
};

template <class C> class BinaryNode {
	private:
		BinaryNode<C> *left_, *right_;
		bool set_;
		C value_;
	public:
		BinaryNode(const C& value) {
			this->value_ = value;
			this->set_ = true;
			this->left_ = NULL;
			this->right_ = NULL;
		}
		inline BinaryNode<C>* getLeft() {
			return this->left_;
		}
		inline BinaryNode<C>* getRight() {
			return this->right_;
		}
		inline C getValue() {
			return this->value_;
		}
		inline bool hasLeft() {
			return (this->left_ != NULL);
		}
		inline bool hasRight() {
			return (this->right_ != NULL);
		}
		inline bool isSet() {
			return (this->set_);
		}
		void setLeft(BinaryNode<C> *left) {
			this->left_ = left;
		}
		void setLeft(const C& value) {
			this->left_ = new BinaryNode<C>(value);
		}
		void setRight(BinaryNode<C> *right) {
			this->right_ = right;
		}
		void setRight(const C& value) {
			this->right_ = new BinaryNode<C>(value);
		}
		void setSide(BinaryNode<C> *node, bool side) {
			(side ? this->right_ : this->left_) = node;
		}
		void setSide(const C& value, bool side) { 
			(side ? this->right_ : this->left_) = new BinaryNode<C>(value);
		}
		void process(void(*f)(C)) {
			(*f)(C);
		}
		void printHyearchy(std::ostream& o, char delim) {
			if (this->left_ != NULL) this->left_->printHyearchy(o, delim);
			o << delim << this->value_;
			if (this->right_ != NULL) this->right_->printHyearchy(o, delim);
		}
		void destroy() {
			if (this->left_ != NULL) this->left_->destroy();
			if (this->right_ != NULL) this->right_->destroy();
			delete this;
		}
};