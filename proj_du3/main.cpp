#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#define EASTER_OK 0
#define EASTER_INVALID_FILENAME 1
#define EASTER_INVALID_YEARS 2
#define EASTER_IO_ERROR 3

#endif // __PROGTEST__

/**
    Month names.
*/
const string monthNames[12] = {"leden", "unor", "brezen", "duben", "kveten", "cerven", "cervenec", "srpen", "zari", "rijen", "listopad", "prosinec"};

/**
    Calculate day and month of easter from year, returns values by parameters.

    @param year Year for which to calculate day and month for.
    @param day Calculated day of easter.
    @param month Calculated month of easter.
*/
void getEaster(const int &year, int &day, int &month) {
    int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    month = (h + l - 7 * m + 114) / 31 - 1;
    day = (h + l - 7 * m + 114) % 31 + 1;
}

/**
    Expand dynamic array by 1 and push value to last position.

    @param arr Reference to pointer to array.
    @param currentSize Size of array, function will use parameter by reference and increment.
    @param val Value to be stored.
*/
void pushToDynamicArray(int* &arr, unsigned int &currentSize, const int& val) {
    int* temporary = new int[currentSize + 1];
    for (unsigned int i = 0; i < currentSize; i++) temporary[i] = arr[i];
    temporary[currentSize] = val;
    if (currentSize > 0) delete[] arr;
    arr = temporary;
    ++currentSize;
}

/**
    Check filename if is valid.

    @param name String path to file to be validated.
    @return If check passed.
*/
bool checkFileName(string name) {
    if (name.size() > 6 && name.substr(name.size() - 5, name.size()) == ".html") {
        for (unsigned int i = 0; i < name.size() - 5; i++) {
            if (!isalnum(name.at(i)) && name.at(i) != '\\' && name.at(i) != '/' && name.at(i) != '.') return false;
        }
        return true;
    } else return false;
}

/**
    Extract all years from string, formats: (XXXX to XXXX, and XXXX-YYYY to XXXX-YYYY with incremental change, comma separated).

    @param str_in String to be parsed.
    @param output Reference to pointer to array where to store years.
    @return Amount of extracted years - return 0 when VALUE_NOT_EXPECTED.
*/
unsigned int getDates(string str_in, int* &output) {
    unsigned int temporary, size = 0;
    string clean_in = "";
    if (str_in.size() < 4) return 0;
    for (unsigned int i = 0; i < str_in.size(); i++) {
        if (isdigit(str_in.at(i))) {
            for (unsigned int j = i; j < i + 4; j++) {
                if (isdigit(str_in.at(j))) {
                    clean_in += str_in.at(j);
                } else return 0;
            }
            i += 3;
        } else if (str_in.at(i) == ',' || str_in.at(i) == '-') clean_in += str_in.at(i);
        else if (str_in.at(i) == ' ') continue;
        else return 0;
    }
    if ((clean_in.size() + 1) % 5 != 0) return 0;
    for (unsigned int i = 0; i < (clean_in.size() + 1) / 5; i++) {
        temporary = atoi(clean_in.substr(0 + i * 5, 3 + i + 5).c_str());
        if (temporary <= 1582 || temporary >= 2200) return 0;
        if (clean_in.size() > 4 + i * 5 && clean_in.at(4 + i * 5) == '-') {
            unsigned int temporary2 = atoi(clean_in.substr(0 + (i + 1) * 5, 3 + (i + 1) * 5).c_str());
            if (temporary2 <= 1582 || temporary2 >= 2200 || temporary2 < temporary) return 0;
            if (clean_in.size() > 4 + (i + 1) * 5) if (clean_in.at(4 + (i + 1) * 5) == '-') return 0;
            for (unsigned int j = temporary; j <= temporary2; j++) pushToDynamicArray(output, size, j);
            ++i;
        } else pushToDynamicArray(output, size, temporary);
    }
    return size;
}

/**
    Extract years from input string and write HTML table with all easter dates to output file.

    @param years C type string with years to be parsed.
    @param outFileName C type string with path to file.
    @return EASTER return value.
*/
int easterReport (const char * years, const char * outFileName) {
    if (!checkFileName(string(outFileName))) return EASTER_INVALID_FILENAME;
    fstream outputFStream(outFileName, ios::out | ios::trunc);
    if (outputFStream.is_open()) {
        int *yearList = NULL, day, month;
        int size = getDates(string(years), yearList);
        if (size < 1) return EASTER_INVALID_YEARS;
        outputFStream << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">" << endl << "<html>" << endl << "<head>" << endl;
        outputFStream << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" << endl << "<title>C++</title>" << endl;
        outputFStream << "</head>" << endl << "<body>" << endl << "<table width=\"300\">" << endl;
        outputFStream << "<tr><th width=\"99\">den</th><th width=\"99\">mesic</th><th width=\"99\">rok</th></tr>" << endl;
        for (int i = 0; i < size; i++) {
            getEaster(yearList[i], day, month);
            outputFStream << "<tr><td>" << day << "</td>";
            outputFStream << "<td>" << monthNames[month] << "</td>";
            outputFStream << "<td>" << yearList[i] << "</td></tr>" << endl;
        }
        outputFStream << "</table>" << endl << "</body>" << endl << "</html>";
        delete[] yearList;
        outputFStream.close();
        return EASTER_OK;
    } else {
        return EASTER_IO_ERROR;
    }
}

#ifndef __PROGTEST__
int main () {
    cout << " " << easterReport("1583-21002199", "out0.html");
    return 0;
}
#endif // __PROGTEST__
