#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "Date.h"

using namespace std;

class Packet
{
private:
    int id;                  // packet unique identifier
    string local;            // touristic places to visit
    Date startDate;          // the start of the travel packet trip
    Date endDate;            // the ending date of the trip
    double pricePerPerson;   // price per person
    int maxPlaces;  // number of persons still available in the packet (updated whenever the packet is sold to a new client)
    int soldPlaces; //number of places that have been sold.
    Date begin;              // begin date
    Date end;                // end date
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

    //outputh method
    friend ostream &operator<<(ostream &out, const Packet &packet);
};