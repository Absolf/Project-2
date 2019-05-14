#pragma once
#include "utils.h"

void tokenize(string const &str, const char delim, vector<string> &out)
{
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim))
    {
        out.push_back(s);
    }
}
int readOptions(const vector<string> &menu)
{
  int option;
  cout << ":::::::::::::::::::::::::::::::::::" << endl;
  cout << "             options             " << endl;
  cout << ":::::::::::::::::::::::::::::::::::" << endl;
  for (size_t i = 0; i < menu.size(); i++)
  {
    cout << i + 1 << " - " << menu.at(i) << endl;
  }
  cout << "0 - Quit\nAnswer: ";
  cin >> option;
  return option;
}
