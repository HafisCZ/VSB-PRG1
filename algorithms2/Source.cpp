#include <iostream>
#include "vld.h" /// Visual Leak Detector
#include "Node.h"
#include "Structures.h"
#include "TreeStructures.h"

int main() {
	List<int> list;
	for (unsigned int i = 0; i < 10; i++) {
		list.push_back(i + 1);
	}

	for (unsigned int i = 0; i < list.size(); i++) {
		std::cout << list.get(i);
	}

	
	/*
	/// QUEUE & STACK
	Stack<char> stack;
	Queue<char> queue;

	std::cout << "__ STRUCTURES __" << std::endl << "INPUT: ";
	for (unsigned int i = 0; i < 10; i++) {
		queue.add(i + 'A');
		stack.add(i + 'A');
		std::cout << static_cast<char>(i + 'A') << " ";
	}

	std::cout << std::endl << "STACK: ";
	while (stack.hasContent()) std::cout << stack.remove() << " ";
	std::cout << std::endl << "QUEUE: ";
	while (queue.hasContent()) std::cout << queue.remove() << " ";

	/// TREE
	std::cout << std::endl << std::endl << "__ Binary Tree __" << std::endl;
	char input;
	BinaryTree<char> bin;
	do {
		std::cout << "Content:";
		bin.print(std::cout);
		std::cout << "\nAdd capital letter: ";
		std::cin >> input;
		if (input < 'A' || input > 'Z') break;
		bin.add(input);
	} while (true);
	


	/*
	std::cout << "__ Node Tree __" << std::endl << "INS: A";
	Node<char> *headNode = new Node<char>('A');
	for (int i = 0; i < 5; i++) {
		std::cout << " " << (char)(i * 3 + 'B');
		Node<char>* secondaryNode = new Node<char>(i * 3 + 'B', headNode, UpdateMode::APPEND);
		for (int j = 0; j < 2; j++) {
			std::cout << " " << (char)(i * 3 + j + 'C');
			new Node<char>(i * 3 + j + 'C', secondaryNode, UpdateMode::APPEND);
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
	while (q.hasContent()) std::cout << " " << ~q;

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
	
	std::cout << std::endl << std::endl << "__ List __" << std::endl;
	std::cout << "I Pattern : A B C D E F G H I J" << std::endl;
	std::cout << "Push Back : ";
	List<char> my_list2;
	for (unsigned int i = 0; i < 10; i++) {
		my_list2.push_back(i + 'A');
	}
	for (unsigned int i = 0; i < my_list2.countContent(); i++) {
		std::cout << my_list2.get(i) << " ";
	}
	std::cout << std::endl << "Push Front: ";
	List<char> my_list;
	for (unsigned int i = 0; i < 10; i++) {
		my_list.push_front(i + 'A');
	}
	for (unsigned int i = 0; i < my_list.countContent(); i++) {
		std::cout << my_list.get(i) << " ";
	}

	std::cout << std::endl << std::endl << "__ Binary Tree __" << std::endl;
	char input;
	BinaryTree<char> bin;
	do {
		std::cout << "Content:";
		bin.printHyearchy(std::cout);
		std::cout << "\nAdd capital letter: ";
		std::cin >> input;
		if (input < 'A' || input > 'Z') break;
		bin.add(input);
	} while (true);
	*/

	std::cin.get();
	std::cin.get();
	return 0;
}