
#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <iomanip>
#include <map>
#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include "Date.h"

using namespace std;

void tokenize(string const &str, char delim, vector<string> &out);
int readOptions(const vector<string> &menu);
template <typename T>
istream &getInput(string prompt, T &input);
template <typename T>
istream &getInput(T &input);
int readInteger(string prompt);
int &readInteger();
double readDouble(string prompt);

#endif