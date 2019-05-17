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
  friend void createPlacesVector(vector<Packet> &packs, vector<string> &aux); //Makes a vector with all the places to visit a holiday package can offer
  friend void createVisitMap(vector<Packet> &packs, vector<string> &aux, map<string, int> &map); //Makes the map<string,int> i'll need to use
  friend void createMostVisitedLocals(vector<Packet> &packs, vector<pair<string, int>> &pares); //Create the most visited places of the Holiday Package in a decreasing order
  friend void createClientsVisitations(vector<Client> &clients, vector<Packet> &packs, vector<vector<string>> &vectorOfClientsPlaces); //Creates a list with the visited places by the client
  friend void createClientVisitSugestionList(vector<Packet> &packs, vector<Client> &clients, vector<vector<string>> &vectorSugestion); //Creates a 2D vector with the client pack sgestions
  friend void createClientSugestion(vector<Packet> &packs, vector<Client> &clients, map<int, int> &myMap); //Creates a map with Packet sugestion for a certain client
  //friend void printClientSugestion(vector<Client> &clients, vector<Packet> &packs);  //Displays the client pack sugestions

  friend ostream &operator<<(ostream &out, const Agency &agency); //Shows an agency content
};
void showAgency(Agency agency); //Use the operator '<<' overload to show agency
void totalPackageSold(vector<Packet> &packs, vector<Client> &client); //Calculates and visualize the number and the total value of sold packages
void PackagePlaces(string line, vector<string> &aux); //Makes a string vector with only the elements of the package destiny
void printMostVisitedLocals(vector<Packet> &packs); //Prints out the N most visited places of the Holiday Package
void printClientSugestion(vector<Client> &clients, vector<Packet> &packs); //Displays the client pack sugestions
#endif
