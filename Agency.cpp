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

//Calculates and visualize the number and the total value of sold packages
void totalPackageSold(vector<Packet> &packs, vector<Client> &client)
{
    int cont = 0, value = 0;
    for (size_t i = 0; i < client.size(); i++)
    {
        for (size_t j = 0; j < packs.size(); j++)
        {
            vector<int> clientPacks;
            clients_packs(client.at(i).getPacketList(), clientPacks);                                   //creates a int vector with the elements of the packet list of client object
            if (find(clientPacks.begin(), clientPacks.end(), packs.at(j).getId()) != clientPacks.end()) // if find inside that int vector the any ID present in the packet object it will go for it
            {
                cout << "Package ID: " << packs.at(j).getId() << endl;
                cout << "Client owner:" << client.at(i).getName() << endl;
                cont++;
                istringstream prices(to_string(packs.at(j).getPricePerPerson()));
                int price;
                prices >> price;
                value += price;
            }
            clientPacks.clear();
        }
    }
    cout << "\nThe ammount of sold packages is: " << cont << endl;
    cout << "The total value of those packages is: " << value << endl;
}

//makes me a vector with all the places to visit a holiday package can offer
void createPlacesVector(vector<Packet> &packs, vector<string> &aux)
{
    vector<string> secondary;
    for (size_t i = 0; i < packs.size(); i++)
    {

        string source = packs.at(i).getLocal(); //Takes the entire line of the places to visit of that holiday package
        vector<string> dest_vec;                // aux vector
        tokenize(source, '-', dest_vec);        // remove the main place from the secondary ones
        string mainDest = dest_vec.at(0);
        size_t found = mainDest.find_last_of(" "); // encontra prosição do primeiro espaço vazio
        mainDest = mainDest.substr(0, found);      // remove o último espaço vazio
        aux.push_back(mainDest);
        if (dest_vec.size() > 1)
        {
            source = dest_vec.at(1);
            dest_vec.clear();
            tokenize(source, ',', dest_vec);
            for (size_t j = 0; j < dest_vec.size(); j++)
            {
                aux.push_back(dest_vec.at(j));
            }
        }
        //cout << "this is a 2nd test " << source <<endl;
    }
}

//Makes me a string vector with only the elements of the package destiny
void PackagePlaces(string line, vector<string> &aux)
{
    vector<string> dest_vec;       // aux vector
    tokenize(line, '-', dest_vec); // remove the main place from the secondary ones
    string mainDest = dest_vec.at(0);
    mainDest = regex_replace(mainDest, regex(" +$"), "");
    aux.push_back(mainDest);
    if (dest_vec.size() > 1)
    {
        line = dest_vec.at(1);
        dest_vec.clear();
        tokenize(line, ',', dest_vec);
        for (size_t j = 0; j < dest_vec.size(); j++)
        {
            dest_vec.at(j) = regex_replace(dest_vec.at(j), regex("^ +"), "");
            aux.push_back(dest_vec.at(j));
        }
    }
}

//makes me the map<string,int> i'll need to use
void createVisitMap(vector<Packet> &packs, vector<string> &aux, map<string, int> &map)
{
    vector<string> packagePlaces;
    createPlacesVector(packs, aux);
    for (size_t i = 0; i < packs.size(); i++)
    {
        PackagePlaces(packs.at(i).getLocal(), packagePlaces);

        for (size_t j = 0; j < packagePlaces.size(); j++)
        {

            if (find(aux.begin(), aux.end(), packagePlaces.at(j)) != aux.end())
            {

                map[packagePlaces.at(j)] += packs.at(i).getSoldPlaces(); //add to the value of te key the sold places
            }
            else
            {
                map.insert(pair<string, int>(packagePlaces.at(j), packs.at(i).getSoldPlaces())); // if dont, create that new<key, value>
            }
        }
        packagePlaces.clear();
    }
}

//create the most visited places of the Holiday Package in a decreasing order
void createMostVisitedLocals(vector<Packet> &packs, vector<pair<string, int>> &pares)
{
    vector<string> aux;
    map<string, int> map;
    createPlacesVector(packs, aux);
    createVisitMap(packs, aux, map);
    pares = vector<pair<string, int>>(map.begin(), map.end());
    sort(pares.begin(), pares.end(), [](auto &left, auto &right) { // Give me the pair sorted from the 2nd element in decreasing order
        return left.second > right.second;
    });
}

//prints out the N most visited places of the Holiday Package
void printMostVisitedLocals(vector<Packet> &packs)
{
    int n;
    cout << "How many Holiday Destinations would you like to see ?" << endl;
    cin >> n;
    vector<pair<string, int>> pares;
    createMostVisitedLocals(packs, pares);
    auto it = pares.begin();
    for (size_t i = 0; i < n; i++)
    {
        cout << it->first << "-" << it->second << endl;
        ++it;
        assert(it != pares.end());
    }
}
//creates a list with the visited places by the client
void createClientsVisitations(vector<Client> &clients, vector<Packet> &packs, vector<vector<string>> &vectorOfClientsPlaces)
{
    vector<string> aux;
    vector<string> clientsVisitedPlaces; // aux vector that will hold all possible Places a clients could visit
    for (size_t i = 0; i < clients.size(); i++)
    {
        vector<int> clientPacksId;                                   // aux vector that wil hold the id of all packages that a client have
        clients_packs(clients.at(i).getPacketList(), clientPacksId); // filling that vector with the ids
        cout <<"i've created a vector with the id of the packages that a client have" << endl;
        for (size_t j = 0; j < packs.size(); j++)
        {
            cout << "searching if our packages have any simmilar id" << endl;
            if (find(clientPacksId.begin(), clientPacksId.end(), packs.at(j).getId()) != clientPacksId.end())
            {           
                cout << "I've found an id correpondent" << endl;
                cout <<"NEW: function PackagePlaces test" << endl;                                          // if the client have one id that is present in the holiday packages enters here
                PackagePlaces(packs.at(j).getLocal(), aux); // creates an auxiliar vector that will hold all possible visited places of that holiday package
                cout <<" it passed!  at package [" << j << "] position of my package vector" << endl;
                for (size_t k = 0; k < aux.size(); k++)
                {   

                    cout << "Using the Visited place: "<< aux.at(k) << endl;
                    cout <<" trying to puth previous data into the string vector clientsVisitedPlaces" << endl;
                    clientsVisitedPlaces.push_back(aux.at(k));
                    cout<<"It passed" << k << " times" << endl;
                }
                aux.clear();
            }
            else
            {
                cout <<" i did'nt find the package apply 'Not aplicable' " << endl; 
                clientsVisitedPlaces.push_back("Not aplicable");
                cout << "it  added a 'Not aplicable' at: " << j << " position of my vector / client" << endl;
            }
        }
        vectorOfClientsPlaces.push_back(clientsVisitedPlaces);
        clientsVisitedPlaces.clear();
    }
}

void createClientVisitSugestionList(vector<Packet> &packs, vector<Client> &clients, vector<vector<string>> &vectorSugestion)
{
    vector<pair<string, int>> pares;
    cout << "Client visited Sugestion List test" << endl;
    cout <<"NEW: createMostVisitedLocals test: " << endl;
    createMostVisitedLocals(packs, pares);
    cout << " createMostVisitedLocals passed! :)" << endl;
    vector<vector<string>> vectorOfClientsPlaces;                    // This will hold in each position visited places by each client (when aplicable)                         // This will hold the sugestion for each client (when aplicable).
    vector<string> sugestion;  
    cout << "NEW : createClientsVisitations test" << endl;                                      // this will be filled with sugestion for one client ( when aplicable)
    createClientsVisitations(clients, packs, vectorOfClientsPlaces); // fill my vector containing  in each position the places that each client has visited
     cout << " createClientsVisitations  passed! :)" << endl;  
    for (size_t i = 0; i < pares.max_size(); i++)                    // look each of the most visited places
    {
        for (size_t j = 0; j < vectorOfClientsPlaces.max_size(); j++) // look up the vector that contains a vector with the visited places by each client (when aplicable)
        {
            for (size_t k = 0; k < vectorOfClientsPlaces.at(j).max_size(); k++) //look up now for the visited places by the client at postion j
            {
                if (find(vectorOfClientsPlaces.at(j).begin(), vectorOfClientsPlaces.at(j).end(), pares.at(i).first) != vectorOfClientsPlaces.at(j).end()) // if one of the most visited places, has already been visited by the client
                {
                    sugestion.push_back("visited!");
                }
                else if (find(vectorOfClientsPlaces.at(j).begin(), vectorOfClientsPlaces.at(j).end(), "Not aplicable") != vectorOfClientsPlaces.at(j).end())
                {
                    sugestion.push_back("Not aplicable"); //if it have not aplicable it means 1 the client has no package 2 the client has visited all places
                }
                else
                {
                    sugestion.push_back(pares.at(i).first); // add in the single vector sugestion the name of a place that client hasn't visited yet;
                }
            }
            vectorSugestion.push_back(sugestion);
            sugestion.clear();
        }
    }
}

void printClientSugestion(vector<Client> &clients, vector<Packet> &packs)
{
    
    vector<vector<string>> vectorSugestion;
    /*
    int n;
    cout << "How many holiday destination sugestions is aplicable? " << endl;
    cin >> n;
    */
    createClientVisitSugestionList(packs, clients, vectorSugestion);
    for (size_t i = 0; i < clients.size(); i++)
    {
        cout << "For client: " << clients.at(i).getName() << endl;
        for (size_t j = 0; j < vectorSugestion.at(i).max_size(); j++)
        {
            vector<string>::iterator it;
            it = find_if_not(vectorSugestion.at(i).begin(), vectorSugestion.at(i).end(), [](string word) {return (word == "visited!" || word == "Not aplicable"); });
            //int sugs = vectorSugestion.at(i).at(j).find(*it) + n; // from the first item that is aplicable + N more items
            if (vectorSugestion.at(i).at(j).find(*it) != vectorSugestion.at(i).at(j).back())
            {
                for (it; it != vectorSugestion.at(i).end(); it++)
                {
                    if ((vectorSugestion.at(i).at(j) != "visited!") || (vectorSugestion.at(i).at(j) != "Not aplicable"))
                    {
                        cout << *it << endl;
                    }
                    else if (vectorSugestion.at(i).at(j) == "Not aplicable")
                    {
                        cout << "No Sugestion! That client has none of our packages" << endl;
                    }
                }
            }
        }
    }
}
// mostra o conteudo de uma agencia
ostream &operator<<(ostream &out, const Agency &agency)
{
    // A IMPLEMENTATION REQUIRED
}
