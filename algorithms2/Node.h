#pragma once

#include <cstddef>

template <class C> class GenericNode {
	protected:
		GenericNode<C> **subordinates_, *superior_;
		unsigned int subordinate_count_;
		C value_;

		void expand(unsigned int count) {
			if (count > this->subordinate_count_) {
				GenericNode<C> **temporary = new GenericNode<C>*[count];
				for (unsigned int i = 0; i < this->subordinate_count_; i++) temporary[i] = this->subordinates_[i];
				for (unsigned int i = this->subordinate_count_; i < count; i++) temporary[i] = NULL;
				delete[] this->subordinates_;
				this->subordinates_ = temporary;
				this->subordinate_count_ = count;
			}
		}
	public:
		GenericNode(const C& value, GenericNode<C> *superior = NULL, bool force_update = false) : value_(value) {
			this->subordinates_ = NULL;
			this->subordinate_count_ = 0;
			this->superior_ = superior;
			if (this->superior_ != NULL && force_update) {
				this->superior_->pushSubordinate(this);
			}
		}

		inline C getValue() const {
			return this->value_;
		}

		inline void setValue(const C& value) {
			this->value_ = value;
		}

		inline GenericNode<C>* getSuperior() const {
			return this->superior_;
		}

		inline GenericNode<C>** getSubordinates() const {
			return this->subordinates_;
		}

		inline unsigned int nSubordinates() const {
			return this->subordinate_count_;
		}

		inline void setSubordinates(GenericNode<C> **child, unsigned int count) {
			this->subordinates_ = child;
			this->subordinate_count_ = (child == NULL ? 0 : count);
		}

		inline GenericNode<C>* getSubordinate(unsigned int index = 0) const {
			return (index < this->subordinate_count_ ? this->subordinates_[index] : NULL);
		}

		void setSubordinate(GenericNode<C> *child, unsigned int position = 0, bool ignore_null = false) {
			if (child != NULL || ignore_null) {
				if (position >= this->subordinate_count_) {
					expand(position + 1);
				}
				this->subordinates_[position] = child;
			}
		}

		void pushSubordinate(GenericNode<C> *child) {
			expand(this->subordinate_count_ + 1);
			this->subordinates_[this->subordinate_count_ - 1] = child;
		}

		void remove(bool cascading = false) {
			if (this->subordinate_count_ > 0) {
				for (unsigned int i = 0; i < this->subordinate_count_ && cascading; i++) {
					this->subordinates_[i]->remove(true);
				}
				delete[] this->subordinates_;
			}
			delete this;
		}
};