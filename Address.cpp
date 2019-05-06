#include "Address.h"

Address::Address()
{
}

Address::Address(string street, int doorNumber, string floor, string zipCode, string location) : street(street), doorNumber(doorNumber), floor(floor), zipCode(zipCode), location(location)
{
}

// metodos GET

string Address::getStreet() const
{
    return street;
}

int Address::getDoorNumber() const
{

    return doorNumber;
}

string Address::getFloor() const
{

    return floor;
}

string Address::getZipCode() const
{

    return zipCode;
}

string Address::getLocation() const
{

    return location;
}

// metodos SET

void Address::setStreet(string street)
{

    this->street = street;
}

void Address::setDoorNumber(int doorNumber)
{

    this->doorNumber = doorNumber;
}

void Address::setFloor(string floor)
{

    this->floor = floor;
}

void Address::setZipCode(string postalCode)
{

    this->zipCode = zipCode;
}

void Address::setLocation(string location)
{

    this->location = location;
}

//other functions
//function that process my addresses removing the '/', making a plan line with spaces, so i can use it with my stringstream
Address address_handler(string line)
{   
    Address address;
    vector<string> addres_vec;
    tokenize(line, '/', addres_vec);
    for (int i = 0; i < addres_vec.size(); i++)
    {
        if (i == 0)
        {
           address.setStreet(addres_vec.at(0));
        }
        else if (i == 1)
        {   
            int number;
            istringstream teste(addres_vec.at(1));
            teste >>  number;
            address.setDoorNumber(number);
        }
        else if (i == 2)
        {   
            address.setFloor(addres_vec.at(2));
        }
        else if (i == 3)
        {
            address.setZipCode(addres_vec.at(3));
        }
        else if (i == 4)
        {
             address.setLocation(addres_vec.at(4));
        }
    }
    return address;
}

//fill a string vector with informations separated by a certain delimiter
void tokenize(string const &str, const char delim, vector<string> &out)
{
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim))
    {
        out.push_back(s);
    }
}

/*********************************
 * Mostrar Address
 ********************************/

// displayes an address in a nice format
ostream &operator<<(ostream &out, const Address &address)
{

    // REQUIRES IMPLEMENTATION
}
