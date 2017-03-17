#include <iostream>
#include "Node.h"
#include "NodeTree.h"
#include "InstantStack.h"
#include "InstantQueue.h"
#include "BinaryTree.h"

int main() {
	std::cout << "__ Node Tree __" << std::endl << "INS: A";
	Node<char> *headNode = new Node<char>('A');
	for (int i = 0; i < 5; i++) {
		std::cout << " " << (char)(i * 3 + 'B');
		Node<char>* secondaryNode = new Node<char>(i * 3 + 'B', headNode, true);
		for (int j = 0; j < 2; j++) {
			std::cout << " " << (char)(i * 3 + j + 'C');
			new Node<char>(i * 3 + j + 'C', secondaryNode, true);
		}
	}
	NodeTree<char> f(headNode);

	std::cout << std::endl << "DFS:";
	f.DepthFirstSearch();

	std::cout << std::endl << "BFS:";
	f.BreadthFirstSearch();

	f.destroy();

	std::cout << std::endl << std::endl << "__ Instant Stack __" << std::endl;
	std::cout << "I Pattern: A B C D E F G H I J" << std::endl;
	std::cout << "O Pattern:";
	
	InstantStack<char> q;
	for (int i = 0; i < 10; i++) {
		q(i + 'A');
	}
	for (int i = 0; i < 10; i++) {
		std::cout << " " << ~q;
	}
	q.destroy();

	std::cout << std::endl << std::endl << "__ Instant Queue __" << std::endl;
	std::cout << "I Pattern: A B C D E F G H I J" << std::endl;
	std::cout << "O Pattern:";

	InstantQueue<char> r;
	for (int i = 0; i < 10; i++) {
		r(i + 'A');
	}
	for (int i = 0; i < 10; i++) {
		std::cout << " " << ~r;
	}
	r.destroy();
	
	std::cout << std::endl << std::endl << "__ Binary Tree __" << std::endl;
	char input;
	BinaryTree<char> bin;
	do {
		std::cout << "Content:";
		bin.printHyearchy(std::cout);
		std::cout << "\nAdd number: ";
		std::cin >> input;
		if (input < 'A' || input > 'Z') break;
		bin.add(input);
	} while (true);
	
	std::cin.get();
	return 0;
}