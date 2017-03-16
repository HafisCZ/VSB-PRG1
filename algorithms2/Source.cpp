#include <iostream>
#include "NodeTree.h"
#include "InstantStack.h"
#include "InstantQueue.h"

int main() {
	Node<int> *headNode = new Node<int>(NULL, 0);
	for (int i = 1; i < 5; i++) {
		Node<int>* secondaryNode = new Node<int>(headNode, i);
		for (int j = 1; j < 3; j++) {
			new Node<int>(secondaryNode, i * 10 + j);
		}
	}
	NodeTree<int> f(headNode);

	std::cout << "Depth First Search:" << std::endl;

	f.DepthFirstSearch();
	std::cout << std::endl << std::endl << "Breadth First Search:" << std::endl;

	f.BreadthFirstSearch();
	std::cout << std::endl << std::endl << "Instant Stack Release Pattern:" << std::endl;

	f.destroy();

	InstantStack<int> q;
	for (int i = 1; i < 11; i++) {
		q(i);
	}
	for (int i = 0; i < 10; i++) {
		std::cout << " " << ~q;
	}
	q.destroy();

	std::cout << std::endl << std::endl << "Instant Queue Release Pattern:" << std::endl;

	InstantQueue<int> r;
	for (int i = 1; i < 11; i++) {
		r(i);
	}
	for (int i = 0; i < 10; i++) {
		std::cout << " " << ~r;
	}
	r.destroy();

	return 0;
}