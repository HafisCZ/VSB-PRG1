#pragma once

#include <cstddef>
#include <ostream>
#include "Node.h"
#include "Structures.h"

enum SearchType {
	BREADTH_FIRST_SEARCH, DEPTH_FIRST_SEARCH
};

template <class C> class TreeBase {
	protected:
		Node<C>* base_node_;
	public:
		TreeBase() {
			this->base_node_ = NULL;
		}

		virtual ~TreeBase() {
			if (this->base_node_ != NULL) {
				this->base_node_->remove(true);
			}
		}

		virtual inline const bool hasContent() const {
			return this->base_node_ != NULL;
		}
};

template <class C> class Tree : public TreeBase<C> {
	public:
		Tree(Node<C>* node_structure) {
			this->base_node_ = node_structure;
		}

		inline void setContent(Node<C>* node_structure) {
			this->base_node_ = node_structure;
		}

		Node<C>* findValue(const C value, SearchType search_type) {
			StructureBase<Node<C>*>* buffer;
			if (search_type == SearchType::BREADTH_FIRST_SEARCH) {
				buffer = new Queue<Node<C>*>;
			} else {
				buffer = new Stack<Node<C>*>;
			}
			Node<C>* select = NULL;
			buffer->add(this->base_node_);
			while (buffer->hasContent()) {
				select = buffer->remove();
				if (select->getValue() == value) {
					break;
				}
				for (unsigned int i = 0; i < select->nSubordinates(); i++) {
					buffer->add(select->getSubordinate(i));
				}
			}
			delete buffer;
			return select;
		}
};

template <class C> class BinaryTree : public TreeBase<C> {
	private:
		void print(Node<C>* node, std::ostream& o, char suffix = ' ') {
			if (node->getSubordinate(0) != NULL) {
				print(node->getSubordinate(0), o);
			}
			o << node->getValue() << suffix;
			if (node->getSubordinate(1) != NULL) {
				print(node->getSubordinate(1), o);
			}
		}
	public:
		void add(const C& value) {
			Node<C>* new_node = new Node<C>(value);
			new_node->expand(2);
			if (this->base_node_ == NULL) {
				this->base_node_ = new_node;
			} else {
				Node<C> *select = this->base_node_, *target = NULL;
				while (select != NULL) {
					target = select->getSubordinate(select->getValue() >= value ? 0 : 1);
					if (target == NULL) select->setSubordinate(new_node, select->getValue() < value ? 1 : 0);
					select = (target == NULL ? NULL : target);
				}
			}
		}

		void print(std::ostream& o) {
			if (this->base_node_ != NULL) {
				print(this->base_node_, o);
			}
		}
};