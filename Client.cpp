#pragma once
#include "Client.h"

Client::Client(vector<string> clients)
{
  this->name = clients.at(0);
  stringstream nif(clients.at(1));
  nif >> this->nif;
  stringstream famSize(clients.at(2));
  famSize >> this->familySize;
  Address address(clients.at(3));
  this->address = address;
  this->packets = clients.at(4);
  stringstream totPurch(clients.at(5));
  totPurch >> this->totalPurchased;
}

Client::Client(string name, unsigned nif, unsigned short familySize, Address address, string packets, unsigned totalPurchased) : name(name), nif(nif), familySize(familySize), address(address), packets(packets), totalPurchased(totalPurchased)
{
}

// GET methods

string Client::getName() const
{
  return name;
}

unsigned Client::getNifNumber() const
{

  return nif;
}

unsigned short Client::getFamilySize() const
{

  return familySize;
}

Address Client::getAddress() const
{

  return address;
}

string Client::getPacketList() const
{

  return packets;
}

unsigned Client::getTotalPurchased() const
{

  return totalPurchased;
}

// metodos SET

void Client::setName(string name)
{

  this->name = name;
  ;
}

void Client::setNifNumber(unsigned nif)
{

  this->nif = nif;
}

void Client::setFamilySize(unsigned short familySize)
{

  this->familySize = familySize;
}
void Client::setAddress(Address address)
{
  this->address = address;
}
void Client::setPacketList(string packets)
{
  this->packets = packets;
}
unsigned Client::setTotalPurchased(unsigned totalPurchased)
{
  this->totalPurchased = totalPurchased;
}

// outros metodos

vector<Client> clientData(string clientFile)
{
  vector<Client> client_info;
  ifstream file;
  string lines;
  vector<string> client_temp;
  file.open(clientFile);
  while (getline(file, lines, '\n'))
  {
    if (lines == "::::::::::")
    {
      Client newClient(client_temp);
      client_info.push_back(newClient);
      client_temp.clear();
    }
    else
    {
      client_temp.push_back(lines);
    }
  }
  Client newClient(client_temp);
  client_info.push_back(newClient);
  file.close();
  return client_info;
}

ostream &operator<<(ostream &out, const Client &client)
{

  // REQUIRES IMPLEMENTATION
}

//creates a vector of packets id
void clients_packs(string line, vector<int> &aux)
{
  line = regex_replace(line, regex(";"), " ");
  istringstream test(line);
  int i;
  while (test >> i)
  {
    aux.push_back(i);
  }
}

