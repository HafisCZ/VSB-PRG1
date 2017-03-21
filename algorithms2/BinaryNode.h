#pragma once

#include <cstddef>
#include <ostream>

template <class C> class BinaryNode {
	private:
		BinaryNode<C> *left_, *right_;
		C value_;
	public:
		BinaryNode(const C& value) : value_(value) {
			this->left_ = NULL;
			this->right_ = NULL;
		}

		inline BinaryNode<C>* getSide(bool right_side = false) {
			return (right_side ? this->right_ : this->left_);
		}

		inline void setSide(BinaryNode<C> *node, bool right_side = false) {
			(right_side ? this->right_ : this->left_) = node;
		}

		inline void setSide(const C& value, bool right_side = false) {
			(right_side ? this->right_ : this->left_) = new BinaryNode<C>(value);
		}

		inline C getValue() {
			return this->value_;
		}

		void process(void(*f)(C)) {
			(*f)(C);
		}
		void printHyearchy(std::ostream& o, char delim) {
			if (this->left_ != NULL) this->left_->printHyearchy(o, delim);
			o << delim << this->value_;
			if (this->right_ != NULL) this->right_->printHyearchy(o, delim);
		}
		void remove() {
			if (this->left_ != NULL) this->left_->remove();
			if (this->right_ != NULL) this->right_->remove();
			delete this;
		}
};