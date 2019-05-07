#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client{
 private:
  string name; // name of the client
  unsigned nif; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address
  vector<int> packets; // vector to store client's packets bought
  unsigned  totalPurchased; // total value spent by the client

 public:
  Client(vector<string> clients);  // for a new client
  Client(string name, unsigned nif, unsigned short familySize, Address address, vector<Packet> & packets, unsigned totalPurchased);  // client read from file

  // GET methods
  
  string getName() const;
  unsigned getNifNumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Packet> getPacketList() const;
  unsigned getTotalPurchased() const;
  
  // SET methods
  
  void setName(string name);
  void setNifNumber(unsigned nif);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(vector<Packet> & packets);
  unsigned setTotalPurchased(unsigned totalPurchased);
  
  // other methods
  friend vector<Client> clientData(string clientFile);
  friend void clients_packs(string line, vector<int> &aux);

  friend ostream& operator<<(ostream& out, const Client & client);
};
