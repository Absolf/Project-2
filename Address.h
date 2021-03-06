#ifndef __ADDRESS_H_INCLUDED__
#define __ADDRESS_H_INCLUDED__
#include "utils.h"

using namespace std;

class Address
{
private:
  string street;   // street name
  int doorNumber;  // dor number
  string floor;    // floor number ("-" is not applicable)
  string zipCode;  // postal code
  string location; // site

public:
  Address();
  Address(string line);
  //Address(string street, int doorNumber, string floor, string postalCode, string location);

  // metodos GET
  string getStreet() const;
  int getDoorNumber() const;
  string getFloor() const;
  string getZipCode() const;
  string getLocation() const;
  string getAddressString() const;

  // metodos SET
  void setStreet(string street);
  void setDoorNumber(int doorNumber);
  void setFloor(string floor);
  void setZipCode(string postalCode);
  void setLocation(string location);
  void setAddress(string address);

  // outros
  friend ostream &operator<<(ostream &out, const Address &address); //Returns the Address in the form of a string
}; 

#endif