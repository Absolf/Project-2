
#include "Address.h"

Address::Address() {}
Address::Address(string line)
{
    vector<string> addres_vec;
    tokenize(line, '/', addres_vec);
    for (int i = 0; (unsigned) i < addres_vec.size(); i++)
    {
        if (i == 0)
        {
            this->street = addres_vec.at(0);
        }
        else if (i == 1)
        {
            istringstream teste(addres_vec.at(1));
            teste >> this->doorNumber;
        }
        else if (i == 2)
        {
            this->floor = addres_vec.at(2);
        }
        else if (i == 3)
        {
            this->zipCode = addres_vec.at(3);
        }
        else if (i == 4)
        {
            this->location = addres_vec.at(4);
        }
    }
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

string Address::getAddressString() const
{
	string street = getStreet();   
	int doorNumber = getDoorNumber(); 
	string floor = getFloor();    
	string zipCode = getZipCode(); 
	string location = getLocation(); 

	string oneLine = street + " / " + to_string(doorNumber) + " / " + floor + " / " + zipCode + " / " + location;

	return oneLine;
}


/*********************************
 * Mostrar Address
 ********************************/
