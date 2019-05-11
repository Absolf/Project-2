#pragma once
#include "Menus.h"
#include "Packet.cpp"
#include "Client.cpp"
#include "Agency.cpp"

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
  vector<string> menu = {"Agency statistics", "Most visited Places ", "Clients Sugestion"};
  int op = readOptions(menu);

  //Total Value and number of sold packages
  if (op == 1)
  {
    totalPackageSold(packs, client);
    while (op > 0)
    {
      cout << "\nWould you like to verify again? \n1 - Yes \n0 - No" << endl;
      cin >> op;
      if (op > 0)
      {
        totalPackageSold(packs, client);
      }
    }
  }
  if (op == 2)
  {
    printMostVisitedLocals(packs);
    while (op > 0)
    {
      cout << "\nWould you like to verify another ammount of most visited packs? \n1 - Yes \n0 - No" << endl;
      cin >> op;
      if (op > 0)
      {
        printMostVisitedLocals(packs);
      }
    }
  }
  if (op == 3)
  {
    printClientSugestion(client, packs);
    while (op > 0)
    {
      cout << "\nWould you like to sugest another ammount of most visited packs? \n1 - Yes \n0 - No" << endl;
      cin >> op;
      if (op > 0)
      {
        printClientSugestion(client, packs);
      }
    }
  }
}

//To implement the operations with my clients
void clients_operations(Agency &agency, vector<Client> &clients)
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
  vector<string> menu = {"Create new Client", "Remove existing Client", "Update Client Information", "Print a specif client", "Print agency clients"};
  int op = readOptions(menu);
  /*
    if (op == 1)
    {
        add_client(clients);
        while (op == 1)
        {
            cout << "Do you want to add another client? \n1 - Yes \n0 - No \n"
                 << endl;
            op = readInteger();
            if (op == 0)
            {
                print_all_clients(clients);
            }
            else
            {
                add_client(clients);
            }
        }
    }

    if (op == 2)
    {
        remove_client(clients);
        while (op > 0)
        {
            cout << "Do you want to remove another client? \n1 - Yes \n0 - No \n"
                 << endl;
            op = readInteger();
            if (op == 0)
            {
                print_all_clients(clients);
            }
            else
            {
                remove_client(clients);
            }
        }
    }
    if (op == 3)
    {
        update_client(clients);
        while (op > 0)
        {
            cout << "Do you want to update another client? \n1 - Yes \n0 - No \n"
                 << endl;
            op = readInteger();
            if (op == 0)
            {
                print_all_clients(clients);
            }
            else
            {
                update_client(clients);
            }
        }
    }
    if (op == 4)
    {
        printClient(clients);
        while (op > 0)
        {
            cout << "Do you want to see the information of other client? \n1 - Yes \n0 - No \n"
                 << endl;
            op = readInteger();
            if (op == 1)
            {
                printClient(clients);
            }
        }
    }
    if (op == 5)
    {
        print_all_clients(clients);
    }
    */
  clientsFile.close();
}

//Operates alongside my vector of packets
void packs_operation(Agency &agency, vector<Packet> &packs, vector<Client> &clients)
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

  vector<string> menu = {"Create new Package", "Remove existing Package", "Update Package Information", "Visualize Travel Packs", "Sell a package to a client"};
  int op = readOptions(menu);
  //It means the agency manager wants to add a new package.
  if (op == 1)
  {
    add_packs(packs);
    while (op > 0)
    {
      cout << "Do you want to add another travel pack? \n1 - Yes \n0 - No \n"
           << endl;
      cin >> op;
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
  //The manager wants to remove an existing package.
  if (op == 2)
  {
    remove_packs(packs);
    while (op > 0)
    {
      cout << "Do you want to remove another travel pack? \n1 - Yes \n0 - No \n"
           << endl;
      cin >> op;
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
  //Agency Manager will update the data of an existing Package
  if (op == 3)
  {
    update_packs(packs);
    while (op > 0)
    {
      cout << "Do you want to update another pack? \n0 - No\n1 - Yes \nAnswer: ";
      cin >> op;
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
  //All kinds of package visualization
  if (op == 4)
  {
    cout << "How would you like to search for Travel Packs?" << endl;
    vector<string> packsVisualizationOptions = {"All Travel Packs", "Related to a destiny", "Between dates", "Related to a destiny and between dates", "Sold to a client", "Sold to all clients", "Most visited places"};
    op = readOptions(packsVisualizationOptions);
    if (op == 1)
    {
      print_all_packs(packs);
      while (op > 0)
      {
        cout << "\nWould you like to see all packets again?\n1 - Yes \n0 - No" << endl;
        cin >> op;
        if (op == 1)
        {
          print_all_packs(packs);
        }
      }
    }
    if (op == 2)
    {
      printDestinyPack(packs);
      while (op > 0)
      {
        cout << "\nWould you like to verify the packs of another destiny? \n1 - Yes \n0 - No" << endl;
        cin >> op;
        if (op == 1)
        {
          printDestinyPack(packs);
        }
      }
    }
    if (op == 3)
    {
      printFromDates(packs);
      while (op > 0)
      {
        cout << "\nWould you like to verify the packs from another date? \n1 - Yes \n0 - No" << endl;
        cin >> op;
        if (op == 1)
        {
          printFromDates(packs);
        }
      }
    }
    if (op == 4)
    {
      printDestinyAndDates(packs);
      while (op > 0)
      {
        cout << "\nWould you like to verify the packs from another destiny & date? \n1 - Yes \n0 - No" << endl;
        cin >> op;
        if (op == 1)
        {
          printDestinyAndDates(packs);
        }
      }
    }
    if (op == 5)
    {
      printToClient(packs, clients);
      while (op > 0)
      {
        cout << "\nWould you like to verify the packs sold to another client? \n1 - Yes \n0 - No" << endl;
        cin >> op;
        if (op == 1)
        {
          printToClient(packs, clients);
        }
      }
    }
    if (op == 6)
    {
      printPackageAllClients(packs, clients);
      while (op > 0)
      {
        cout << "\nWould you like to verify the packs sold to the Clients? \n1 - Yes \n0 - No" << endl;
        cin >> op;
        if (op > 0)
        {
          printPackageAllClients(packs, clients);
        }
      }
    }
  }
  //Sell a package to a client
  if (op == 5)
  {
    sellToClient(packs, clients);
    while (op > 0)
    {
      cout << "Do you want to sell another pack? \n0 - No\n1 - Yes \nAnswer: ";
      cin >> op;
      if (op > 0)
      {
        sellToClient(packs, clients);
      }
    }
  }
  packsFile.close();
}

unsigned mainMenu(Agency agency)
{
  int op;
  op = agency_operations(agency);
  vector<Packet> packages = packData(agency.getPackets());
  vector<Client> clients = clientData(agency.getClients());
  while (op != 0)
  {
    if (op == 1)
    {
      clients_operations(agency, clients);
      cout << "\nWould you like to keep managing the clients? \n1-Yes \n0-No" << endl;
      cin >> op;
      while (op != 0)
      {
        clients_operations(agency, clients);
        cout << "\nWould you like to keep managing the clients? \n1-Yes \n0-No" << endl;
        cin >> op;
      }
    }

    if (op == 2)
    {
      packs_operation(agency, packages, clients);
      cout << "\nWould you like to keep managing the Packages? \n1-Yes \n0-No" << endl;
      cin >> op;
      while (op != 0)
      {
        packs_operation(agency, packages, clients);
        cout << "\nWould you like to keep managing the Packages? \n1-Yes \n0-No" << endl;
        cin >> op;
      }
    }
    if (op == 3)
    {
      statistics_operations(agency, clients, packages);
      cout << "\nWould you like to keep acessing the statistics? \n1-Yes \n0-No" << endl;
      cin >> op;
      while (op != 0)
      {
        statistics_operations(agency, clients, packages);
        cout << "\nWould you like to keep acessing the statistics? \n1-Yes \n0-No" << endl;
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
