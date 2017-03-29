#pragma once

#include <cstddef>
#include "Node.h"

template <class C> class StructureBase {
	protected:
		Node<C>* base_node_;
	public:
		StructureBase() {
			this->base_node_ = NULL;
		}

		/**
			Remove structure and all its content in cascading manner.
		*/
		virtual ~StructureBase() {
			if (this->base_node_ != NULL) {
				this->base_node_->remove(true);
			}
		}

		/**
			@return If structure holds any value.
		*/
		virtual inline const bool hasContent() const {
			return this->base_node_ != NULL;
		}

		/**
			@return First value that would be removed in the structure.
		*/
		virtual inline const C& peek() const {
			return this->base_node_->getValue();
		}

		/**
			@deprecated Use only overriden remove function from derived classes.
		*/
		virtual void add(const C& value) { 
		
		}

		/**
			@deprecated Use only overriden remove function from derived classes.
		*/
		virtual const C remove() {
			return NULL;
		}
};

template <class C> class Stack : public StructureBase<C> {
	public:
		/**
			Add new value into the stack.

			@param value Value to be added.
		*/
		void add(const C& value) {
			Node<C>* new_node = new Node<C>(value);
			new_node->setSubordinate(this->base_node_);
			this->base_node_ = new_node;
		}

		/**
			Remove value from the stack.

			@return Removed value.
		*/
		const C remove() {
			Node<C>* follow_node = this->base_node_->getSubordinate();
			C current_value = this->base_node_->getValue();
			this->base_node_->remove(false);
			this->base_node_ = follow_node;
			return current_value;
		}
};

template <class C> class Queue : public StructureBase<C> {
	private:
		Node<C>* terminal_node_;
	public:
		Queue() : StructureBase() {
			this->terminal_node_ = NULL;
		}

		/**
			Add new value into the queue.

			@param value Value to be added.
		*/
		void add(const C& value) {
			Node<C>* new_node = new Node<C>(value);
			if (this->base_node_ == NULL || this->terminal_node_ == NULL) {
				this->terminal_node_ = new_node;
				this->base_node_ = this->terminal_node_;
			} else {
				this->terminal_node_->setSubordinate(new_node);
				this->terminal_node_ = new_node;
			}
		}

		/**
			Remove value from the queue.

			@return Removed value.
		*/
		const C remove() {
			Node<C>* follow_node = this->base_node_->getSubordinate();
			C current_value = this->base_node_->getValue();
			this->base_node_->remove(false);
			this->base_node_ = follow_node;
			return current_value;
		}
};

template <class C> class List : private StructureBase<C> {
	private:
		Node<C>* terminal_node_;
		unsigned int length_;
	public:
		/**
			Create new list with edge markers. Fake node is inserted to the top and is used as anchor for all following nodes inside the list.
		*/
		List() {
			this->base_node_ = new Node<C>(NULL);
			this->terminal_node_ = this->base_node_;
			this->length_ = 0;
		}

		/**
			@return If list holds any value inside.
		*/
		inline const bool hasContent() const {
			return this->base_node_->getSubordinate() != NULL;
		}

		/**
			@return First value that would be removed from the list.
		*/
		inline const C& peek() const {
			return this->base_node_->getSubordinate()->getValue();
		}

		/**
			@return Amount of values stored inside the list.
		*/
		inline const unsigned int size() const {
			return this->length_;
		}
 
		/**
			Insert value to the end of the list.

			@param value Value to be inserted.
		*/
		void push_back(const C& value) {
			Node<C>* new_node = new Node<C>(value);
			this->terminal_node_->setSubordinate(new_node);
			this->terminal_node_ = new_node;
			this->length_++;
		}

		/**
			Insert value to the front of the list.

			@param value Value to be inserted.
		*/
		void push_front(const C& value) {
			Node<C>* shift = this->base_node_->getSubordinate();
			Node<C>* parent = new Node<C>(value, this->base_node_, UpdateMode::OVERRIDE);
			parent->setSubordinate(shift);
			this->length_++;
		}

		/**
			Returns value at selected index. If index is out of bounds, then returns last value in the list.

			@param index Index of value in list we want to retrieve.
			@return Value at selected index.
		*/
		const C& get(unsigned int index) const {
			Node<C>* select = this->base_node_;
			for (unsigned int i = 0; i < this->length_ && index < this->length_; i++) {
				select = select->getSubordinate();
				if (i == index) return select->getValue();
			}
			return select->getValue();
		}

		/**
			Insert value at position.

			@param value Value to be inserted.
			@param index Position in the list.
		*/
		void insert(const C& value, unsigned int index = 0) {
			if (index == 0) {
				push_front(value);
			} else if (index >= this->length_) {
				push_back(value);
			} else {
				Node<C>* select = this->base_node_;
				for (unsigned int i = 0; i < index; i++) select = select->getSubordinate();
				Node<C>* new_node = new Node<C>(value), *shift = select->getSubordinate();
				new_node->setSubordinate(shift);
				select->setSubordinate(new_node);
				this->length_++;
			}
		}

		/**
			Removes value at position from the list.

			@param index Position of value to be removed.
			@return Removed value.
		*/
		const C remove(unsigned int index = 0) {
			if (index == 0) {
				return pop_front();
			} else if (index >= this->length_) {
				return pop_back();
			} else {
				Node<C>* select = this->base_node_;
				for (unsigned int i = 0; i < index; i++) select = select->getSubordinate();
				Node<C>* deletion = select->getSubordinate(), *shift = deletion->getSubordinate();
				C current_value = deletion->getValue();
				delete deletion;
				select->setSubordinate(shift, 0, true);
				this->length_--;
				return current_value;
			}
		}

		/**
			Removes value from the front of the list.

			@return Removed value.
		*/
		const C pop_front() {
			Node<C>* deletion = this->base_node_->getSubordinate(), *shift = deletion->getSubordinate();
			C current_value = deletion->getValue();
			delete deletion;
			this->base_node_->setSubordinate(shift, 0, true);
			this->length_--;
			return current_value;
		}

		/**
			Removes value from the end of the list.

			@return Removed value.
		*/
		const C pop_back() {
			C current_value = this->terminal_node_->getValue();
			Node<C>* select = this->base_node_;
			while (select->getSubordinate() != this->terminal_node_) select = select->getSubordinate();
			delete this->terminal_node_;
			select->setSubordinate(NULL, 0, true);
			this->terminal_node_ = select;
			this->length_--;
			return current_value;
		}
};