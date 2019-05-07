#include "Client.h"

Client::Client(vector<string> clients){
  Address address(clients.at(3));
  vector<int> packets;
  this->name = clients.at(0);
  this->nif = stoi(clients.at(1));
  this->familySize = stoi(clients.at(2));
  this->address = address;
  clients_packs(clients.at(4), packets);
  this->packets = packets;
  this->totalPurchased = stoi(clients.at(5));
}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet> & packets, unsigned totalPurchased): name(name), nif(nif), familySize(familySize), address(address), packets(packets), totalPurchased(totalPurchased) {
}

  // GET methods

string Client::getName() const{
  return name;
}
  
unsigned Client::getNifNumber() const{
  
 return nif;
}

unsigned short Client::getFamilySize() const{
  
 return familySize;
}

Address Client::getAddress() const{
  
  return address;
}

vector<Packet> Client::getPacketList() const{
  
  return packets;
}

unsigned Client::getTotalPurchased() const{
  
 return totalPurchased; 
}
  
  // metodos SET
	  
void Client::setName(string name){
  
  this->name = name;;
}

void Client::setNifNumber(unsigned nif){
  
  this->nif=nif;
}

void Client::setFamilySize(unsigned short familySize){
  
  this->familySize=familySize;
}
void Client::setAddress(Address address){ 
 this->address=address;
}
void Client::setPacketList(vector<Packet> & packets){ 
  this->packets=packets;
}
unsigned Client::setTotalPurchased(unsigned totalPurchased){
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
ostream& operator<<(ostream& out, const Client & client){

  // REQUIRES IMPLEMENTATION 

}
