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

		virtual ~StructureBase() {
			if (this->base_node_ != NULL) {
				this->base_node_->remove(true);
			}
		}

		virtual inline const bool hasContent() const {
			return this->base_node_ != NULL;
		}

		virtual inline const C& peek() const {
			return this->base_node_->getValue();
		}

		virtual void add(const C& value) { }

		virtual const C remove() {
			return NULL;
		}
};

template <class C> class Stack : public StructureBase<C> {
	public:
		void add(const C& value) {
			Node<C>* new_node = new Node<C>(value);
			new_node->setSubordinate(this->base_node_);
			this->base_node_ = new_node;
		}

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

		void _fix() {
			Node<C>* select = this->base_node_;
			if (this->length_ == 0) {
				this->terminal_node_ = this->base_node_;
			} else {
				while ((select = select->getSubordinate()) != NULL);
				this->terminal_node_ = select;
			}
		}
	public:
		List() {
			this->base_node_ = new Node<C>(NULL);
			this->terminal_node_ = NULL;
			this->length_ = 0;
		}

		inline const bool hasContent() const {
			return this->base_node_->getSubordinate() != NULL;
		}

		inline const C& peek() const {
			return this->base_node_->getSubordinate()->getValue();
		}

		inline const unsigned int size() const {
			return this->length_;
		}

		void push_back(const C& value) {
			if (this->terminal_node_ == NULL) _fix();
			Node<C>* new_node = new Node<C>(value);
			this->terminal_node_->setSubordinate(new_node);
			this->terminal_node_ = new_node;
			this->length_++;
		}

		void push_front(const C& value) {
			Node<C>* shift = this->base_node_->getSubordinate();
			Node<C>* parent = new Node<C>(value, this->base_node_, UpdateMode::OVERRIDE);
			parent->setSubordinate(shift);
			if (this->terminal_node_ == NULL) _fix();
			this->length_++;
		}

		const C& get(unsigned int index) const {
			Node<C>* select = this->base_node_;
			for (unsigned int i = 0; i < this->length_ && index < this->length_; i++) {
				select = select->getSubordinate();
				if (i == index) return select->getValue();
			}
			return select->getValue();
		}

		void insert(const C& value, unsigned int index = 0) {
			if (this->terminal_node_ == NULL) _fix();
			Node<C>* select = this->base_node_;
			for (unsigned int i = 0; i < this->length_ && index < this->length_; i++) {
				select = select->getSubordinate();
			}
			Node<C>* new_node = new Node<C>(value);
			new_node->setSubordinate(select->getSubordinate(), 0, false);
			select->setSubordinate(new_node, 0, false);
			this->length_++;
		}
};