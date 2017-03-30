#include <iostream>
#include <string>

#include "vld.h" /// Visual Leak Detector

#include "Node.h"
#include "Structures.h"
#include "TreeStructures.h"

using namespace std;

int main() {

	List<Stack<int>*> list;
	list.push_back(new Stack<int>);
	for (size_t i = 0; i < 10; i++) list.peek()->add(i);
	while (list.peek()->hasContent()) cout << list.peek()->remove();
	delete list.pop_back();

	cin.get();
	return 0;
}