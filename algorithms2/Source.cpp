#include <iostream>
#include <string>

#include "vld.h" /// Visual Leak Detector

#include "Node.h"
#include "Structures.h"
#include "TreeStructures.h"

using namespace std;

int main() {
	Stack<Queue<int>*> stack; // Create new Stack, that contains Queues of ints
	stack.add(new Queue<int>); // Create new Queue and add it into the stack
	delete stack.remove(); // Remove the Queue from stack and delete it

	BinaryTree<int> binary_tree;
	binary_tree.add(5);
	binary_tree.add(2);
	binary_tree.add(1);
	binary_tree.add(3);
	binary_tree.add(7);
	binary_tree.print(cout);

	cin.get();
	return 0;
}