#ifndef __CLIENT_H_INCLUDED__
#define __CLIENT_H_INCLUDED__

#include "Packet.h"
#include "Address.h"
#include "utils.h"

using namespace std;

class Client
{
private:
  string name;               // name of the client
  unsigned nif;              // VAT number of client
  unsigned short familySize; // number of family members
  Address address;           // client's address
  string packets;            // vector to store client's packets bought
  unsigned totalPurchased;   // total value spent by the client

public:     // empty constructor
  Client(vector<string> clients);                                                                                         // for a new client

  // GET methods

  string getName() const;
  unsigned getNifNumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  string getPacketList() const;
  unsigned getTotalPurchased() const;

  // SET methods

  void setName(string name);
  void setNifNumber(unsigned nif);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(string packets);
  unsigned setTotalPurchased(unsigned totalPurchased);

  // other methods
  
  friend ostream &operator<<(ostream &out, const Client &client);
  friend void update_client(vector<Client> &vec);
  friend void remove_client(vector<Client> &vec);
  friend vector<Client> add_client(vector<Client> &vec);
  friend void printClient(vector<Client> &vec);
  friend void print_all_clients(vector<Client> &vec);
  friend void writeClients(string file_name, vector<Client> &vec);
};

void clients_packs(string line, vector<int> &aux);
vector<string> clientQuestionHandler(vector<string> vec);
vector<string> clients_questions();
vector<Client> clientData(string clientFile);
#endif
