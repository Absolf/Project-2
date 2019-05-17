
#include "utils.h"

void tokenize(string const &str, char delim, vector<string> &out)
{
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim))
    {
        out.push_back(s);
    }
}
//Read options of all my menus/moment of choices
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
    cout << "0 - Quit" << endl;
    option = readInteger("Answer: ");
    return option;
}


template <typename T>
istream &getInput(string prompt, T &input)
{
    cin.clear();
    cout << prompt;
    return cin >> input;
}

//responsible to readIntData
int readInteger(string prompt)
{
    string input;
    while (getInput(prompt, input))
    {
        istringstream is(input);
        int inputAsInt;
		if (is >> inputAsInt)
			return inputAsInt;
        cout << '"' << input << "\" is not valid." << endl;
    }
    // A failure from getInput means something outside the normal realm of events
    // for console input has occurred -- possibly stdin was redirected to a file,
    // and we ran into eof, for example.  Let's consider it exceptional.
    throw runtime_error("Unexpected extraction error in readInteger function\n");
}

//responsible to readDouble data
double readDouble(string prompt)
{
    string input;
    while (getInput(prompt, input))
    {
        istringstream is(input);
        double inputAsDouble;
        if (is >> inputAsDouble)
            return inputAsDouble;
        cout << '"' << input << "\" is not valid." << endl;
    }
    // A failure from getInput means something outside the normal realm of events
    // for console input has occurred -- possibly stdin was redirected to a file,
    // and we ran into eof, for example.  Let's consider it exceptional.
    throw runtime_error("Unexpected extraction error in readDouble function\n");
}

