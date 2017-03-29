#pragma once

#include <cstddef>

enum UpdateMode {
	IGNORE, APPEND, OVERRIDE
};

template <class C> class Node {
	protected:
		Node<C> **subordinates_, *superior_;
		unsigned int subordinate_count_;
		C value_;

		void _expand(unsigned int count) {
			if (count > this->subordinate_count_) {
				Node<C> **temporary = new Node<C>*[count];
				for (unsigned int i = 0; i < this->subordinate_count_; i++) temporary[i] = this->subordinates_[i];
				for (unsigned int i = this->subordinate_count_; i < count; i++) temporary[i] = NULL;
				delete[] this->subordinates_;
				this->subordinates_ = temporary;
				this->subordinate_count_ = count;
			}
		}
	public:
		explicit Node(const C& value, Node<C> *superior = NULL, UpdateMode force_update = UpdateMode::IGNORE) : value_(value) {
			this->subordinates_ = NULL;
			this->subordinate_count_ = 0;
			this->superior_ = superior;
			if (this->superior_ != NULL) {
				if (force_update == UpdateMode::APPEND) {
					this->superior_->pushSubordinate(this);
				} else if (force_update == UpdateMode::OVERRIDE) {
					this->superior_->setSubordinate(this, 0);
				}
			}
		}

		virtual ~Node() {

		}
		
		inline const C& getValue() const {
			return this->value_;
		}

		inline void setValue(const C& value) {
			this->value_ = value;
		}

		inline Node<C>* getSuperior() const {
			return this->superior_;
		}

		inline unsigned int nSubordinates() const {
			return this->subordinate_count_;
		}

		void expand(unsigned int count) {
			_expand(count);
		}

		inline Node<C>* getSubordinate(unsigned int index = 0) const {
			return (index < this->subordinate_count_ ? this->subordinates_[index] : NULL);
		}
		
		void setSubordinate(Node<C> *child, unsigned int position = 0, bool ignore_null = false) {
			if (child != NULL || ignore_null) {
				if (position >= this->subordinate_count_) {
					_expand(position + 1);
				}
				this->subordinates_[position] = child;
			}
		}

		void pushSubordinate(Node<C> *child, bool ignore_null = false) {
			if (child != NULL || ignore_null) {
				_expand(this->subordinate_count_ + 1);
				this->subordinates_[this->subordinate_count_ - 1] = child;
			}
		}

		virtual void remove(bool cascading = false) {
			if (this->subordinate_count_ > 0) {
				for (unsigned int i = 0; i < this->subordinate_count_ && cascading; i++) {
					if (this->subordinates_[i] != NULL) {
						this->subordinates_[i]->remove(true);
					}
				}
				delete[] this->subordinates_;
			}
			delete this;
		}
};