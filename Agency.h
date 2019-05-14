#ifndef __AGENCY_H_INCLUDED__
#define __AGENCY_H_INCLUDED__

#include "Address.h"
#include "Date.h"
#include "Client.h"
#include "Packet.h"
#include "utils.h"
#include "defs.h"

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
  Agency(string filename);

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
  friend void createPlacesVector(vector<Packet> &packs, vector<string> &aux);
  friend void createVisitMap(vector<Packet> &packs, vector<string> &aux, map<string, int> &map);
  friend void createMostVisitedLocals(vector<Packet> &packs, vector<pair<string, int>> &pares);
  friend void createClientsVisitations(vector<Client> &clients, vector<Packet> &packs, vector<vector<string>> &vectorOfClientsPlaces);
  friend void createClientVisitSugestionList(vector<Packet> &packs, vector<Client> &clients, vector<vector<string>> &vectorSugestion);
  friend void createClientSugestion(vector<Packet> &packs, vector<Client> &clients, map<int, int> &myMap);
  friend void printClientSugestion(vector<Client> &clients, vector<Packet> &packs);

  //friend ostream& operator<<(ostream& out, const Agency & agency);
};

void totalPackageSold(vector<Packet> &packs, vector<Client> &client);
void printMostVisitedLocals(vector<Packet> &packs);
void printClientSugestion(vector<Client> &clients, vector<Packet> &packs);
vector<string> agencyData(vector<string> &linesInfo);
#endif
