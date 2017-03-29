/**
	@{
		Multipurpose node class.

		@author Hiraishin Software
		@version V3.0
	@}
*/

#pragma once

#include <cstddef>

enum UpdateMode {
	IGNORE, APPEND, OVERRIDE
};

template <class C> class Node {
	protected:
		Node<C>** subordinates_;
		Node<C>* superior_; 
		unsigned int subordinates_size_; 
		C value_; 

		/**
			Expands subordinate array.

			@param size Size of expanded subordinate array.
		*/
		void _expand(unsigned int size) {
			if (size > this->subordinates_size_) {
				Node<C> **temporary = new Node<C>*[size];
				for (unsigned int i = 0; i < this->subordinates_size_; i++) temporary[i] = this->subordinates_[i];
				for (unsigned int i = this->subordinates_size_; i < size; i++) temporary[i] = NULL;
				delete[] this->subordinates_;
				this->subordinates_ = temporary;
				this->subordinates_size_ = size;
			}
		}
	public:
		/**
			Explicit constructor.

			@param value Value of node
			@param superior Superior Node
			@param update_mode Action, that should be applied on the superior node.
		*/
		explicit Node(const C& value, Node<C> *superior = NULL, UpdateMode update_mode = UpdateMode::IGNORE) : value_(value) {
			this->subordinates_ = NULL;
			this->subordinates_size_ = 0;
			this->superior_ = superior;
			if (this->superior_ != NULL) {
				if (update_mode == UpdateMode::APPEND) {
					this->superior_->pushSubordinate(this);
				} else if (update_mode == UpdateMode::OVERRIDE) {
					this->superior_->setSubordinate(this, 0);
				}
			}
		}

		/**
			Virtual destructor.
		*/
		virtual ~Node() {
			
		}
		
		/**
			@return Value of node.
		*/
		inline const C& getValue() const {
			return this->value_;
		}

		/**
			@param value New value of node.
		*/
		inline void setValue(const C& value) {
			this->value_ = value;
		}

		/**
			@return Superior of this node.
		*/
		inline Node<C>* getSuperior() const {
			return this->superior_;
		}

		/**
			@return Size of subordinate array.
		*/
		inline unsigned int nSubordinates() const {
			return this->subordinates_size_;
		}

		/**
			@param count New size of subordinate array.
			@deprecated Requires precise set / get calls.
		*/
		void expand(unsigned int count) {
			_expand(count);
		}

		/**
			@param index Position of subordinate in array.
			@return Selected subordinate.
		*/
		inline Node<C>* getSubordinate(unsigned int index = 0) const {
			return (index < this->subordinates_size_ ? this->subordinates_[index] : NULL);
		}

		/**
			Insert new subordinate node at position. Use ignore_null if NULL subordinates needs to be used aswell, or they will be ignored.
			If out of bounds, expands subordinate array and sets new subordinate to furthest position.

			@param subordinate Subordinate node that will be stored at position.
			@param position Position of new subordinate node in subordinate array.
			@param ignore_null If false, NULL subordinate will be ignored.
		*/
		void setSubordinate(Node<C> *subordinate, unsigned int position = 0, bool ignore_null = false) {
			if (subordinate != NULL || ignore_null) {
				if (position >= this->subordinates_size_) {
					_expand(this->subordinates_size_ + 1);
				}
				this->subordinates_[position] = subordinate;
			}
		}
		
		/**
			Insert new subordinate to next not allocated position. Expands size of subordinate array by one. 
			Use ignore_null if NULL subordinates needs to be used aswell, or they will be ignored.

			@param subordinate Subordinate node that will be inserted
			@param ignore_null If false, NULL subordinate will be ignored.
		*/
		void pushSubordinate(Node<C> *subordinate, bool ignore_null = false) {
			if (subordinate != NULL || ignore_null) {
				_expand(this->subordinates_size_ + 1);
				this->subordinates_[this->subordinates_size_ - 1] = subordinate;
			}
		}

		/**
			Virtual method that removes node itself and possibly all of its subordinates by cascading manner.

			@param cascading Use true to remove all subordinates aswell (this function will be called as recursive on all subordinates).
		*/
		virtual void remove(bool cascading = false) {
			if (this->subordinates_size_ > 0) {
				for (unsigned int i = 0; i < this->subordinates_size_ && cascading; i++) {
					if (this->subordinates_[i] != NULL) {
						this->subordinates_[i]->remove(true);
					}
				}
				delete[] this->subordinates_;
			}
			delete this;
		}
};