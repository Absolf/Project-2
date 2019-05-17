#ifndef __CLIENT_H_INCLUDED__
#define __CLIENT_H_INCLUDED__

#include "Packet.h"
#include "Address.h"
#include "utils.h"

using namespace std;

class Client
{
private:
  string name;                 // name of the client
  unsigned nif{};              // VAT number of client
  unsigned short familySize{}; // number of family members
  Address address;             // client's address
  string packets;              // vector to store client's packets bought
  double totalPurchased;       // total value spent by the client

public:
  Client(); // empty constructor
  Client(vector<string> clients);
  //Client(){}// for a new client

  // GET methods

  string getName() const;
  unsigned getNifNumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  string getPacketList() const;
  double getTotalPurchased() const;

  // SET methods

  void setName(string name);
  void setNifNumber(unsigned nif);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(string packets);
  void setTotalPurchased(double totalPurchased);

  // other methods

  friend ostream &operator<<(ostream &out, const Client &client); //Overload of "<<" operator to display all client's info
  friend void update_client(vector<Client> &vec); //Update/change the information of a client;
  friend void remove_client(vector<Client> &vec); //Remove a client from the clients vector (remove all data of that client)
  friend vector<Client> add_client(vector<Client> &vec); //Add new client (using the function client_questions)
  friend void printClient(vector<Client> &vec); //Displays a specific client in the screen
  friend void print_all_clients(vector<Client> &vec); //Displays all clients in the screen
  friend void writeClients(string file_name, vector<Client> &vec); //Saves the clients vector in the client file
};

void clients_packs(string line, vector<int> &aux); //creates a vector of packets id (for a client)
vector<string> clientQuestionHandler(vector<string> vec); //it will automate de clients_question job
vector<string> clients_questions(); //creates a new vector<string> with the data needed to create my new client
vector<Client> clientData(string clientFile); //Creates a vector with all of the Objects of the Class Clients contained in the clients file
#endif
