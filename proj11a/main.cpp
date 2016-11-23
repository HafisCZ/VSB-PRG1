#ifndef __PROGTEST__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#endif // __PROGTEST__

struct node {
	struct node* next;
	int val;
	bool set;
	node(void) : set(false) {
		this->next = NULL;
	}
	node(int value) : set(true) {
		this->val = value;
		this->next = NULL;
	}
	void add(int value) {
		if (!this->set) {
			this->val = value;
			this->set = true;
		}
		else if (this->next == NULL) {
			this->next = new node(value);
		}
		else (*(this->next)).add(value);
	}
	void dealloc(void) {
		if (this->next != NULL) {
			(*(this->next)).dealloc();
			this->next = NULL;
		}
		delete this;
	}
	int at(int index) {
		struct node *f = this;
		int it = 0;
		while (it++ < index && f != NULL) {
			f = f->next;
		}
		return f->val;
	}

};

int evenOdd(const char* srcFileName, const char* dstFileName) {
	std::fstream in(srcFileName, std::ios::in);
	int success = 0, sub = 0;
	node* liche = new node;
	node* sude = new node;
	if (in.is_open()) {
		std::string t;
		int l = 0, s = 0, temp;
		while (std::getline(in, t)) {
			std::stringstream ss(t);
			ss >> temp;
			if (ss.fail()) {
				sub++;
				break;
			}
			((temp < 0 ? -temp : temp) % 2 == 0 ? sude : liche)->add(temp);
			((temp < 0 ? -temp : temp) % 2 == 0 ? s : l)++;
		}
		if (sub == 0) {
			std::fstream out(dstFileName, std::ios::out | std::ios::trunc);
			if (out.is_open()) {
				for (int i = 0, max = s + l; i < max; i++) {
                    out << (i < s ? sude : liche)->at((i < s ? i : i - s));
                    if (i < max - 1) out << std::endl;
				}
				success = 1;
				out.close();
			}
		}
		in.close();
	}
	liche->dealloc();
	sude->dealloc();
	return success;
}

#ifndef __PROGTEST__
int main()
{
	std::string in, out;
	std::cout << "Load from: ";
	std::getline(std::cin, in);
	std::cout << "Save to: ";
	std::getline(std::cin, out);
	std::cout << evenOdd(in.c_str(), out.c_str()) << std::endl;
	return 0;
}
#endif // __PROGTEST__
