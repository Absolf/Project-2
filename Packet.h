#ifndef __PACKET_H_INCLUDED__
#define __PACKET_H_INCLUDED__
#include "utils.h"
#include "Date.h"
#include "Client.h"
using namespace std;
class Client;
class Packet
{
    friend class Address;

private:
    int id;                // packet unique identifier
    string local;          // touristic places to visit
    Date startDate;        // the start date of the travel packet trip
    Date endDate;          // the ending date of the trip
    double pricePerPerson; // the price for each person
    int maxPlaces;         // number of persons still available in the packet (updated whenever the packet is sold to a new client)
    int soldPlaces;        // number of places that have been sold.
public:
    Packet(); // empty constructor
    Packet(vector<string> pack_vec); //constructor that will be used crete the clients objects
    // GET methods
    int getId() const;
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

    // other methods

    friend int lastID(vector<Packet> &vec); //got the ID of the last packet
    friend vector<string> packQuestionHandler(vector<string> vec); // Manage the string vector that contains the questions to create a new packet
    friend vector<string> packs_questions(vector<Packet> &vec); // takes the ID of the last packet inside the vector, and create a new pack with the handler results
    friend void add_packs(vector<Packet> &vec); // create a new vector and put it in the end of the current packet
    friend void print_all_packs(vector<Packet> &vec); // present all the packets that i currently have in my agency
    friend void remove_packs(vector<Packet> &vec); // removes a pack using the id
    friend void update_packs(vector<Packet> &vec); // updates a pack information
    friend void printDestinyPack(vector<Packet> &vec); // Show packages related to a destiny
    friend void printFromDates(vector<Packet> &vec); //Show packages in a range of date
    friend void printDestinyAndDates(vector<Packet> &vec); // a mix of previous functions
    friend void printToClient(vector<Packet> &vec, vector<Client> &client); // Shows the package that a specific client have
    friend void printPackageAllClients(vector<Packet> &packs, vector<Client> &client); // print all packeges that all clients have
    friend void sellToClient(vector<Packet> &packs, vector<Client> &client); // Realize the act of selling a package to a client
    friend void writePacks(string file_name, vector<Packet> &vec); //Writes the content of the vector to the file

    //outputh method
    friend ostream &operator<<(ostream &out, const Packet &packet); //ovearload of "<<" operator that allows to print a Packet object
};

vector<Packet> packData(string packFile); // Creates the first vector of Packet objects from the file of Holiday Packets
#endif
