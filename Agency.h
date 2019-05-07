#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "Address.h"
#include "Date.h"
#include "defs.h"
//#include "Client.h"


using namespace std;

class Agency
{
private:
  string name;     // name of the  agency
  string nif;      // VAT number of the agency
  Address address; // address of the agency
  string url;      // URL of the agency Web site
  string clients;  // vector to store the existing clients
  string packets;  // vector to store the existing packets

  /*
  bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
  bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
  unsigned int maxClientsId; // maximum value among all clients identifiers
  unsigned int maxPacketsId; // maximum value among all packets identifiers
  */
public:
  Agency();
  Agency(string fileName);

  // methods GET
  string getName() const;
  string getNif() const;
  Address getAddress() const;
  string getURL() const;
  string getClients() const;
  string getPackets() const;

  // methods SET
  void setName(string name);
  void setNif(string nif);
  void setAddress(Address address);
  void setUrl(string url);
  void setClients(string clients);
  void setPackets(string packets);

  // other methods */
  friend vector<string> openAgency(string fileName);
  
  //friend ostream& operator<<(ostream& out, const Agency & agency);
};
