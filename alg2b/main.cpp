#include <iostream>
#include <string>

using namespace std;

string compress (string input) {
    string compressed;
    unsigned int len;
    for (unsigned int i = 0; i < input.size(); i++) {
        len = 1;
        for (unsigned int j = i + 1; j < input.size() && j < i + 12; j++) {
           if (input[i] == input[j]) len++;
        }
        if (len > 3) {
            compressed += '#';
            compressed += input[i];
            compressed += ('0' + len - 3);
        } else {
            for (unsigned int k = 0; k < len; k++) {
                compressed += input[i];
            }
        }
        i += len - 1;
    }
    return compressed;
}

int main()
{
    cout << compress("AAAAAAbbbbsskkkkkkkkkkkwWWWWWWWWoDFFFFFFFFF") << endl;
    return 0;
}
