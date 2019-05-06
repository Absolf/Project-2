#include "Menus.h"

//function that will read all my integers instead of a simple cin
int readInteger()
{
  int x;
  cin >> x;
  while (cin.fail())
  {

    cout << "Please type a integer number\n";
    cin >> x;
    if (cin.fail())
    {
      cin.clear();
      cin.ignore();
      cout << "You have entered a wrong input \n";
      cin >> x;
    }
    if (!cin.fail())
    {
      return x;
    }
  }
  return x;
}

//Function that will represent all my menus options;
int readOptions(const vector<string> &menu)
{
  cout << ":::::::::::::::::::::::::::::::::::" << endl;
  cout << "             options             " << endl;
  cout << ":::::::::::::::::::::::::::::::::::" << endl;
  for (size_t i = 0; i < menu.size(); i++)
  {
    cout << i + 1 << " - " << menu.at(i) << endl;
  }
  cout << "0 - Quit\nAnswer: ";
  int option = readInteger(); //Function yet to finish
  while (option < 0 || option > menu.size())
  {
    option = readInteger();
  }
  return option;
}

//"Menu for agency"
int agency_operations(Agency &agency){
    //simple user interface
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<< endl;
    cout << "                          Welcome to the agency " << agency.getName()<< endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<< endl;
    cout << endl;
    int op;
    cout << "What would you like to manage?: " << endl;
    vector<string> menu = {"Clients","Package"};
    op = readOptions(menu);
    cout << endl;
    //attempt to fill the  services & clients structs with data from the files.
    cout << endl;
    return op;
} 

unsigned mainMenu(Agency agency){

  cout << "starting \n";
  int op;
  op = agency_operations(agency);
  
  return 0;
}
    