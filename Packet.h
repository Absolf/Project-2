#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "defs.h"
#include "Date.h"
#include "Address.h"
#include "Client.h"

using namespace std;
class Client;

class Packet
{
    friend class Address;
private:
    int id;                // packet unique identifier
    string local;          // touristic places to visit
    Date startDate;        // the start of the travel packet trip
    Date endDate;          // the ending date of the trip
    double pricePerPerson; // price per person
    int maxPlaces;         // number of persons still available in the packet (updated whenever the packet is sold to a new client)
    int soldPlaces;        //number of places that have been sold.
public:
    Packet();
    Packet(int id, string local, Date startDate, Date endDate, double pricePerPerson, int startPlaces, int SoldPlaces);
    Packet(vector<string> pack_vec);
    // GET methods
    unsigned getId() const;
    string getLocal() const;
    Date getBeginDate() const;
    Date getEndDate() const;
    double getPricePerPerson() const;
    int getMaxPlaces() const;
    int getSoldPlaces() const;

    // SET methods
    void setId(int id); // to set negatve if "deprecated"
    void setLocal(string local);
    void setSites(string local);
    void setBeginDate(Date startDate);
    void setEndDate(Date endDate);
    void setPricePerPerson(double pricePerPerson);
    void setMaxPlaces(int maxPlaces);
    void setSoldPlaces(int soldPlaces);
    //void setPackage(vector<string> &pack_vec);

    // other methods
    friend vector<Packet> packData(string packFile);
    friend int lastID(vector<Packet> &vec);
    friend vector<string> packQuestionHandler(vector<string> vec);
    friend vector<string> packs_questions(vector<Packet> &vec);
    friend void add_packs(vector<Packet> &vec);
    friend void print_all_packs(vector<Packet> &vec);
    friend void remove_packs(vector<Packet> &vec);
    friend void update_packs(vector<Packet> &vec);
    friend void Address::tokenize(string const &str, const char delim, vector<string> &out);
    friend void printDestinyPack(vector<Packet> &vec);
    friend void printFromDates(vector<Packet> &vec);
    friend void printDestinyAndDates(vector<Packet> &vec);
    friend void printToClient(vector<Packet> &vec, vector<Client> &client);
    friend void printPackageAllClients(vector<Packet> &packs, vector<Client> &client);
    friend void sellToClient(vector<Packet> &packs, vector<Client> &client);
    friend void totalPackageSold(vector<Packet> &packs, vector<Client> &client);
    //friend void clients_packs(string line, vector<int> &aux);
    //outputh method
    friend ostream &operator<<(ostream &out, const Packet &packet);
};

