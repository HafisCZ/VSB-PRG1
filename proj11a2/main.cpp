#ifndef __PROGTEST__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#endif // __PROGTEST__

void push_back(int* &arr, int &size, const int &val) {
	int* temporary = new int[size + 1];
	for (int i = 0; i < size; i++) temporary[i] = arr[i];
	temporary[size] = val;
	if (size > 0) delete[] arr;
	arr = temporary;
	++size;
}

int evenOdd(const char* srcFileName, const char* dstFileName) {
	std::fstream in(srcFileName, std::ios::in);
	int success = 0, sub = 0, s = 0, l = 0;
	int *sude = NULL;
	int *liche = NULL;
	if (in.is_open()) {
		std::string t;
		int temp;
		while (std::getline(in, t)) {
			std::stringstream ss(t);
			ss >> temp;
			if (ss.fail()) {
				sub++;
				break;
			}
			bool is = ((temp < 0 ? -temp : temp) % 2 == 0 ? true : false);
			push_back((is ? sude : liche), (is ? s : l), temp);
		}
		if (sub == 0) {
			std::fstream out(dstFileName, std::ios::out | std::ios::trunc);
			if (out.is_open()) {
				for (int i = 0, max = s + l; i < max; i++) {
					out << (i < s ? sude : liche)[(i < s ? i : i - s)];
					if (i < max - 1) out << std::endl;
				}
				success = 1;
				out.close();
			}
		}
		in.close();
	}
	if (s > 0) delete[] sude;
	if (l > 0) delete[] liche;
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
