#pragma once
#include "Menus.h"
#include "Packet.h"
#include "Packet.cpp"

//function that will read all my integers instead of a simple cin

/*int readInteger()
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
*/

//Function that will represent all my menus options;
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

//"Menu for agency"
int agency_operations(Agency &agency)
{
  //simple user interface
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "                          Welcome to the agency " << agency.getName() << endl;
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << endl;
  int op;
  cout << "What would you like to manage?: " << endl;
  vector<string> menu = {"Clients", "Package"};
  cout << "teste 1" << endl;
  op = readOptions(menu);

  cout << " so far i'm working here" << endl;
  //attempt to fill the  services & clients structs with data from the files.
  cout << endl;
  return op;
}

void packs_operation(Agency &agency, vector<Packet> &packs)
{
  ifstream packsFile;
  packsFile.open(agency.getPackets());
  cout << "Opening file: " << agency.getPackets() << endl;
  cout << endl;
  if (packsFile.good())
  {
    cout << "Services database up to date. file " << agency.getPackets() << " successfully readed from the current directory" << endl;
  }
  else
  {
    cout << "Can't open the services database file" << agency.getPackets() << "it's not on the current directory " << endl;
  }
  cout << endl;
  //Uses the function that creates my vector of Travel Packs to actually make a vector filled with information
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "                             Packages                                 " << endl;
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << endl;

  vector<string> menu = {"Create new Package", "Remove existing Package", "Update Package Information", "Visualize Travel Packs", "Sell a package to a client", "Nº of sold Packages and total value"};
  int op = readOptions(menu);
  //It means the agency manager wants to add a new package.
  if (op == 1)
  {
    add_packs(packs);
    while (op > 0)
    {
      cout << "Do you want to add another travel pack? \n1 - Yes \n0 - No \n"<< endl;
      cin >> op;
      if (op == 0)
      {
        //print_all_packs(packs);
      }
      else
      {
        add_packs(packs);
      }
    }
  }
  packsFile.close();
}

unsigned mainMenu(Agency agency)
{
  int op;
  op = agency_operations(agency);
  vector<Packet> packages;
  packages = packData(agency.getPackets());
  while (op != 0)
  {
    if (op == 2)
    {
      packs_operation(agency, packages);
      cout << "\nWould you like to keep managing the Packages? \n1-Yes \n0-No" << endl;
      cin >> op;
      while (op != 0)
      {
        packs_operation(agency, packages);
        cout << "\nWould you like to keep managing the Packages? \n1-Yes \n0-No" << endl;
        cin >> op;
      }
    }
    cout << "Are you sure you want to quit? \nYes - 0 \nNo - 1" << endl;
    cin >> op;
    if (op == 1)
    {
      op = agency_operations(agency);
    }
  }

  cout << "\n Exit sucefull! " << endl;
  return 0;
}
