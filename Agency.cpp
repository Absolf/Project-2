#pragma once
#include "Agency.h"
#include "Address.cpp"
//construtor da classe
Agency::Agency() {}
Agency::Agency(string fileName)
{
    vector<string> linesInfo;
    ifstream agencyFile;
    agencyFile.open(fileName);
    if (agencyFile.good())
    {
        cout << "                Sucefully opened the file: " << fileName << endl;
    }
    else
    {
        cout << "                Can't open the file: " << fileName << endl;
    }
    string lines;
    while (getline(agencyFile, lines))
    {
        linesInfo.push_back(lines);
    }

    setName(linesInfo.at(0));
    setNif(linesInfo.at(1));
    setUrl(linesInfo.at(2));
    Address address(linesInfo.at(3));
    this->address = address;
    setClients(linesInfo.at(4));
    setPackets(linesInfo.at(5));
}

// metodos GET
string Agency::getName() const
{
    return name;
}
string Agency::getNif() const
{
    return nif;
}
Address Agency::getAddress() const
{
    return address;
}
string Agency::getURL() const
{
    return url;
}
string Agency::getClients() const
{
    return clients;
}
string Agency::getPackets() const
{
    return packets;
}

// metodos SET
void Agency::setName(string name)
{
    this->name = name;
}
void Agency::setNif(string nif)
{
    this->nif = nif;
}
void Agency::setAddress(Address address)
{
    this->address = address;
}
void Agency::setUrl(string url)
{
    this->url = url;
}
void Agency::setClients(string clients)
{
    this->clients = clients;
}
void Agency::setPackets(string packets)
{
    this->packets = packets;
}

/*********************************
 * Mostrar Loja
 ********************************/

// mostra o conteudo de uma agencia
ostream &operator<<(ostream &out, const Agency &agency)
{
    // A IMPLEMENTATION REQUIRED
}
