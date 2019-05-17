#include "Menus.h"

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

//function that will read all my integers instead of a simple cin

//makes a copy of the file so i can user in case sth goes wrong
void makeCopy(string filename)
{
  ifstream ifile;
  string line;
  vector<string> file;
  tokenize(filename, '.', file);

  ifile.open(filename);
  string outname = file.at(0) + "_copy.txt";
  ofstream ofile;
  ofile.open(outname);
  while (getline(ifile, line))
  {
    ofile << line << endl;
  }
  //cout << "Ponto na posição : " << pos;
  ifile.close();
  ofile.close();
}

//"Menu for agency"
int agency_operations(Agency &agency) // implementation of Agency Opening, this is just used to ask for the manager what he want to manage
{
  int op;
  showAgency(agency); // just show's agency information
  cout << "What would you like to manage?: " << endl;
  vector<string> menu = {"Clients", "Package", "Statistics"};
  op = readOptions(menu);
  //attempt to fill the  services & clients structs with data from the files.
  cout << endl;
  return op;
}

void statistics_operations(Agency &agency, vector<Client> &client, vector<Packet> &packs)
{

  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "                 Agency " << agency.getName() << " statistics         " << endl;
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << endl;
  vector<string> menu = {"Agency statistics", "Most visited Places ", "Clients Suggestion"}; // string vector with the options will be required for manage the agency statistics
  int op = readOptions(menu);

  //Total Value and number of sold packages
  if (op == 1)
  {
    totalPackageSold(packs, client);
    while (op > 0)
    {
      op = readInteger("\nWould you like to verify again? \n1 - Yes \n0 - No");
      if (op > 0)
      {
        totalPackageSold(packs, client);
      }
    }
  }
  if (op == 2) // Print's N most visited destinations (by the limit it have);
  {
    printMostVisitedLocals(packs);
    while (op > 0)
    {
      op = readInteger("\nWould you like to verify another ammount of most visited packs? \n1 - Yes \n0 - No");
      if (op > 0)
      {
        printMostVisitedLocals(packs);
      }
    }
  }
  if (op == 3) // Gives a sugestion for each client
  {
    printClientSugestion(client, packs);
    while (op > 0)
    {
      op = readInteger("\nWould you like to suggest another ammount of most visited packs? \n1 - Yes \n0 - No");
      if (op > 0)
      {
        printClientSugestion(client, packs);
      }
    }
  }
}


void clients_operations(Agency &agency, vector<Client> &clients) //To implement the operations of clients management
{
  ifstream clientsFile;
  clientsFile.open(agency.getClients());
  if (clientsFile.good())
  {
    cout << "Clients database up to date. file " << agency.getClients() << " successfully readed from the current directory" << endl;
  }
  else
  {
    cout << "Can't open the clients database file" << agency.getClients() << "it's not on the current directory " << endl;
  }

  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "                             Clients                                  " << endl;
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << endl;
  vector<string> menu = {"Create new Client", "Remove existing Client", "Update Client Information", "Print a specif client", "Print agency clients"}; //string vector containing the options to manage the agency clients
  int op = readOptions(menu);

  if (op == 1) // option where you can actually add new information to clients
  {
    add_client(clients);
    while (op > 0)
    {
      op = readInteger("Do you want to add another client? \n1 - Yes \n0 - No \n");
      if (op == 0)
      {
        print_all_clients(clients); // this is always used to verify if the information have been added
      }
      else
      {
        add_client(clients);
      }
    }
  }
  if (op == 2) // option for removing a client
  {
    remove_client(clients);
    while (op > 0)
    {
      op = readInteger("Do you want to remove another client? \n1 - Yes \n0 - No \n");
      if (op == 0)
      {
        print_all_clients(clients); // this is always used to verify if the information have been removed
      }
      else
      {
        remove_client(clients);
      }
    }
  }
  if (op == 3) // option to update any client information
  {
    update_client(clients);
    while (op > 0)
    {
      op = readInteger("Do you want to update another client? \n1 - Yes \n0 - No \n");
      if (op == 0)
      {
        print_all_clients(clients);// this is always used to verify if the information have been updated
      }
      else
      {
        update_client(clients);
      }
    }
  }
  if (op == 4) // option to print information for a specific client
  {
    printClient(clients);
    while (op > 0)
    {
      op = readInteger("Do you want to see the information of other client? \n1 - Yes \n0 - No \n");
      if (op == 1)
      {
        printClient(clients);
      }
    }
  }
  if (op == 5) // option to print all clients(it's constantly used to verification in other functions thou)
  {
    print_all_clients(clients);
    while (op > 0)
    {
      op = readInteger("Do you want to see the information of clients again? \n1 - Yes \n0 - No \n");
      if (op == 1)
      {
        print_all_clients(clients);
      }
    }
  }
  writeClients(agency.getClients(), clients);
  clientsFile.close();
}

//Operates alongside my vector of packets
void packs_operation(Agency &agency, vector<Packet> &packs, vector<Client> &clients) // implementation of all management with packets
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
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "                             Packages                                 " << endl;
  cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << endl;

  vector<string> menu = {"Create new Package", "Remove existing Package", "Update Package Information", "Visualize Travel Packs", "Sell a package to a client"}; // vector of strings that hold all information for packs management
  int op = readOptions(menu);
  if (op == 1) //It means the agency manager wants to add a new package.
  {
    add_packs(packs);
    while (op > 0)
    {
      op = readInteger("Do you want to add another travel pack? \n1 - Yes \n0 - No \n");
      if (op == 0)
      {
        print_all_packs(packs);
      }
      else
      {
        add_packs(packs);
      }
    }
  }
  if (op == 2) //The manager wants to remove an existing package.
  {
    remove_packs(packs);
    while (op > 0)
    {
      op = readInteger("Do you want to remove another travel pack? \n1 - Yes \n0 - No \n");
      if (op == 0)
      {
        print_all_packs(packs);
      }
      else
      {
        {
          remove_packs(packs);
        }
      }
    }
  }
  if (op == 3)//Agency Manager will update the data of an existing Package
  {
    update_packs(packs);
    while (op > 0)
    {
      op = readInteger("Do you want to update another pack? \n0 - No\n1 - Yes \nAnswer: ");
      if (op == 0)
      {
        print_all_packs(packs);
      }
      else
      {
        update_packs(packs);
      }
    }
  }
  if (op == 4) //All kinds of package visualization
  {
    cout << "How would you like to search for Travel Packs?" << endl;
    vector<string> packsVisualizationOptions = {"All Travel Packs", "Related to a destiny", "Between dates", "Related to a destiny and between dates", "Sold to a client", "Sold to all clients"}; // vector that holds the visualization options for the packets managemet
    op = readOptions(packsVisualizationOptions);
    if (op == 1) // present all agency packets
    {
      print_all_packs(packs);
      while (op > 0)
      {
        op = readInteger("\nWould you like to see all packets again?\n1 - Yes \n0 - No");
        if (op == 1)
        {
          print_all_packs(packs);
        }
      }
    }
    if (op == 2) // present's a package within a specific destiny
    {
      printDestinyPack(packs);
      while (op > 0)
      {
        op = readInteger("\nWould you like to verify the packs of another destiny? \n1 - Yes \n0 - No");
        if (op == 1)
        {
          printDestinyPack(packs);
        }
      }
    }
    if (op == 3) // present's a holiday package within a specific date
    {
      printFromDates(packs);
      while (op > 0)
      {
        op = readInteger("\nWould you like to verify the packs from another date? \n1 - Yes \n0 - No");
        if (op == 1)
        {
          printFromDates(packs);
        }
      }
    }
    if (op == 4)
    {
      printDestinyAndDates(packs); // present's a holiday package within a specific date and for a specific destiny
      while (op > 0)
      {
        op = readInteger("\nWould you like to verify the packs from another destiny & date? \n1 - Yes \n0 - No");
        if (op == 1)
        {
          printDestinyAndDates(packs);
        }
      }
    }
    if (op == 5) // present's the packages that a specific client have
    {
      printToClient(packs, clients);
      while (op > 0)
      {
        op = readInteger("\nWould you like to verify the packs sold to another client? \n1 - Yes \n0 - No");
        if (op == 1)
        {
          printToClient(packs, clients);
        }
      }
    }
    if (op == 6)
    {
      printPackageAllClients(packs, clients); // present's all the packets that a client have and it's in the travel agency
      while (op > 0)
      {
        op = readInteger("\nWould you like to verify the packs sold to the Clients? \n1 - Yes \n0 - No\nAnswer: ");
        if (op > 0)
        {
          printPackageAllClients(packs, clients);
        }
      }
    }
  }
  if (op == 5) // option if the manager want to sell a packet to a client
  {
    sellToClient(packs, clients);
    while (op > 0)
    {
      op = readInteger("Do you want to sell another pack? \n0 - No\n1 - Yes \nAnswer: ");
      if (op > 0)
      {
        sellToClient(packs, clients);
      }
    }
  }
  //makeCopy(agency.getPackets());
  writePacks(agency.getPackets(), packs);
  packsFile.close();
}

void mainMenu(Agency agency) // The menu the manages the other 3
{
  int op;
  op = agency_operations(agency);
  vector<Packet> packages = packData(agency.getPackets()); // create my vector of agency holiday packets
  vector<Client> clients = clientData(agency.getClients()); // create my vector of agency clients
  while (op != 0)
  {
    if (op == 1) // this option means the manager wants to manage the clients
    {
      clients_operations(agency, clients);
      op = readInteger("\nWould you like to keep managing the clients? \n1-Yes \n0-No\nAnswer: ");
      while (op != 0)
      {
        clients_operations(agency, clients);
        op = readInteger("\nWould you like to keep managing the clients? \n1-Yes \n0-No\nAnswer: ");
      }
    }

    if (op == 2) // here to manage the packets
    {
      packs_operation(agency, packages, clients);
      op = readInteger("\nWould you like to keep managing the Packages? \n1-Yes \n0-No\nAnswer: ");
      while (op != 0)
      {
        packs_operation(agency, packages, clients);
        op = readInteger("\nWould you like to keep managing the Packages? \n1-Yes \n0-No\nAnswer: ");
      }
    }
    if (op == 3) // and here to verify all the statistics of the agency
    {
      statistics_operations(agency, clients, packages);
      op = readInteger("\nWould you like to keep acessing the statistics? \n1-Yes \n0-No\nAnswer: ");
      while (op != 0)
      {
        statistics_operations(agency, clients, packages);
        op = readInteger("\nWould you like to keep acessing the statistics? \n1-Yes \n0-No\nAnswer: ");
      }
    }
    op = readInteger("Are you sure you want to quit? \nYes - 0 \nNo - 1\nAnswer: ");

    if (op == 1)
    {
      op = agency_operations(agency);
    }
  }

  cout << "\n Exit sucefull! " << endl;
}
