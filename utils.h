
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
using namespace std;
using namespace std;

void tokenize(string const &str, const char delim, vector<string> &out);
int readOptions(const vector<string> &menu);

