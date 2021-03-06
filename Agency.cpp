
#include "Agency.h"

//Construtors of the class objects Agency
Agency::Agency(string filename)
{
    vector<string> linesInfo;
    ifstream agencyFile;
	agencyFile.clear();
    agencyFile.open(filename);
    //ifs.is_open()
    if (agencyFile.is_open())
    {
        cout << "Successfully opened the file: " << filename << endl;
    }
    else
    {
        cout << "Can't open the file: " << filename << endl;
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
    agencyFile.close();
}

Agency::Agency() {}

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

//other functions

/*********************************
 * Mostrar Loja
 ********************************/

//Calculates and visualize the number and the total value of sold packages
void totalPackageSold(vector<Packet> &packs, vector<Client> &client)
{
    int total = 0;
    double revenue = 0;
    for (size_t i = 0; i < packs.size(); i++)
    {

        revenue += packs.at(i).getSoldPlaces() * packs.at(i).getPricePerPerson();
        total += packs.at(i).getSoldPlaces();
    }
    cout << "\nThe ammount of sold packages is: " << total << endl;
    cout << "The agency revenue is: " << revenue << endl;
}

//Makes a vector with all the places to visit a holiday package can offer
void createPlacesVector(vector<Packet> &packs, vector<string> &aux)
{
    vector<string> secondary;
    for (size_t i = 0; i < packs.size(); i++)
    {
        if (packs.at(i).getId() > 0)
        {

            string source = packs.at(i).getLocal(); //Takes the entire line of the places to visit of that holiday package
            vector<string> dest_vec;                // aux vector
            tokenize(source, '-', dest_vec);        // remove the main place from the secondary ones
            string mainDest = dest_vec.at(0);
            size_t found = mainDest.find_last_of(" "); // finds the position of the first space
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
        }
    }
}

//Makes a string vector with only the elements of the package destiny
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

//Makes the map<string,int> i'll need to use
void createVisitMap(vector<Packet> &packs, vector<string> &aux, map<string, int> &map)
{
    vector<string> packagePlaces;
    createPlacesVector(packs, aux); // make's a vector with the possible visiting places of a vector
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

//Create the most visited places of the Holiday Package in a decreasing order
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

//Prints out the N most visited places of the Holiday Package
void printMostVisitedLocals(vector<Packet> &packs)
{

    vector<pair<string, int>> pares;

    createMostVisitedLocals(packs, pares);
    cout << "We have a total of " << pares.size() << " destinations " << endl;
    int n = 0;
    auto it = pares.begin();

    cout << "How many Holiday Destinations would you like to see ?" << endl;
    cin >> n;
    while ((unsigned) n > pares.size() || n <= 0)
    {
        cout << "Please do not exceed " << pares.size() << " destinations provided or type null or negative numbers\n Type again: \n";
        cin >> n;
    }
    cout << "Destinations: " << endl;
    for (size_t i = 0; i < (unsigned) n; i++) //Cicle that displays the most visited locals
    {
        cout << "[" << it->first << "] had a total of " << it->second << " visits " << endl;
        ++it;
        //assert(it != pares.end());
    }
}
//Creates a list with the visited places by the client
void createClientsVisitations(vector<Client> &clients, vector<Packet> &packs, vector<vector<string>> &vectorOfClientsPlaces)
{
    vector<string> aux;
    vector<string> clientsVisitedPlaces; // aux vector that will hold all possible Places a clients could visit
    for(size_t i = 0; i < clients.size(); i++)
    {
        vector<int> clientPacksId;                                   // aux vector that wil hold the id of all packages that a client have
        clients_packs(clients.at(i).getPacketList(), clientPacksId); // filling that vector with the ids
        for (size_t j = 0; j < packs.size(); j++)
        {
            if (find(clientPacksId.begin(), clientPacksId.end(), packs.at(j).getId()) != clientPacksId.end()) // searching if our packages have any simmilar id
            {
                PackagePlaces(packs.at(j).getLocal(), aux); // if the client have one id that is present in the holiday packages enters here
                for (size_t k = 0; k < aux.size(); k++)
                {
                    clientsVisitedPlaces.push_back(aux.at(k)); // creates an auxiliar vector that will hold all possible visited places of that holiday package
                }
                aux.clear();
            }
        }
        vectorOfClientsPlaces.push_back(clientsVisitedPlaces);
        clientsVisitedPlaces.clear();
    }
}

//Creates a 2D vector with the client pack sgestions
void createClientVisitSugestionList(vector<Packet> &packs, vector<Client> &clients, vector<vector<string>> &vectorSugestion)
{
    vector<pair<string, int>> pares;
    //cout << "Client visited Sugestion List test" << endl;
    //cout << "NEW: createMostVisitedLocals test: " << endl;
    createMostVisitedLocals(packs, pares);
    // cout << " createMostVisitedLocals passed! :)" << endl;
    vector<vector<string>> vectorOfClientsPlaces; // This will hold in each position visited places by each client (when aplicable)                         // This will hold the sugestion for each client (when aplicable).
    vector<string> sugestion;
    //cout << "NEW : createClientsVisitations test" << endl;           // this will be filled with sugestion for one client ( when aplicable)
    createClientsVisitations(clients, packs, vectorOfClientsPlaces); // fill my vector containing  in each position the places that each client has visited
                                                                     // cout << " createClientsVisitations  passed! :)" << endl;
    for (size_t i = 0; i < vectorOfClientsPlaces.size(); i++)        // look up the vector that contains a vector with the visited places by each client (when aplicable)
    {
        //cout << "client [" << i << "] " << clients.at(i).getName() << endl;
        for (size_t k = 0; k < pares.size(); k++) // look each of the most visited places
        {
            if (find(vectorOfClientsPlaces.at(i).begin(), vectorOfClientsPlaces.at(i).end(), pares.at(k).first) != vectorOfClientsPlaces.at(i).end()) // if one of the most visited places, has already been visited by the client
            {
                //cout << "[" << i << "]if i find the place add visited! he has been there place: " << endl;
                //cout << pares.at(k).first << " like here " << endl;
                //sugestion.push_back("visited!");
                continue;
            }
            else if (find(vectorOfClientsPlaces.at(i).begin(), vectorOfClientsPlaces.at(i).end(), "Not aplicable") != vectorOfClientsPlaces.at(i).end())
            {
                //cout << "[" << i << "]if i find  not Aplicable i'll add the same shit to it " << endl;
                //sugestion.push_back("Not aplicable"); //if it have not aplicable it means 1 the client has no package 2 the client has visited all places
                continue;
            }
            else
            {
                //cout << "[" << i << "] After many searches the sugestion : " << pares.at(k).first << " will be added " << endl;
                sugestion.push_back(pares.at(k).first); // add in the single vector sugestion the name of a place that client hasn't visited yet;
            }
        }
        // cout << "finally add a fucking vector with fully sugestions (or not) to my vector of sugestiosn" << endl;
        vectorSugestion.push_back(sugestion);
        sugestion.clear();
    }
}

//Creates a map with Packet sugestion for a certain client
void createClientSugestion(vector<Packet> &packs, vector<Client> &clients, map<int, int> &myMap)
{
    vector<string> packPlaces;
    vector<vector<string>> vectorSugestion;
    createClientVisitSugestionList(packs, clients, vectorSugestion);

    for (size_t i = 0; i < packs.size(); i++)
    {
        for (size_t j = 0; j < vectorSugestion.size(); j++)
        {
            for (size_t k = 0; k < vectorSugestion.at(j).size(); k++)
            {
                //cout << vectorSugestion.at(j).at(k) << endl;
                if (packs.at(i).getId() > 0)
                {
                    PackagePlaces(packs.at(i).getLocal(), packPlaces);
                    if (!(find(packPlaces.begin(), packPlaces.end(), vectorSugestion.at(j).at(k)) != packPlaces.end()))
                    {
                        //cout << "client: " << clients.at(j).getName() << " sugestion: holiday pack id [" << packs.at(i).getId() << "]" << endl;
                        myMap[packs.at(i).getId()] += 1; //Add the sugested pack to the map
                    }
                }
            }
        }
    }
}

//Displays the client pack sugestions 
void printClientSugestion(vector<Client> &clients, vector<Packet> &packs)
{
    map<int, int> myMap;
    createClientSugestion(packs, clients, myMap);
    auto it = myMap.begin();
    vector<int> lastChance;
    for (it; it != myMap.end(); it++)
    {
        lastChance.push_back(it->first);
    }
    for (size_t i = 0; i < clients.size(); i++)
    {
        for (size_t j = 0; j < packs.size(); j++)
        {
            if (packs.at(j).getId() > 0)
            {
                vector<int> clientPacks;
                clients_packs(clients.at(i).getPacketList(), clientPacks);                                  //creates a int vector with the elements of the packet list of client object
                if (!(find(clientPacks.begin(), clientPacks.end(), lastChance.at(i)) != clientPacks.end())) // if find inside that int vector any ID present in the sugestion
                {
                    if (packs.at(j).getId() == lastChance.at(i))
                    {
                        cout << "client: " << clients.at(i).getName() << " Pack sugestion: " << packs.at(j) << endl;
                    }
                }
                else
                {
                    cout << "client:  " << clients.at(i).getName() << " No sugestion";
                }
            }
        }
    }
}
//Use the operator '<<' overload to show agency
void showAgency(Agency agency){
    //simple user interface
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << "                          Welcome to the agency " << endl;
    cout << agency;
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << endl;
}
//Shows an agency content
ostream &operator<<(ostream &out, const Agency &agency) {
    out << agency.getName() << endl;
    out << agency.getNif() << endl;
    out << agency.getURL() << endl;
    out << agency.getAddress().getAddressString() <<endl;
    out << agency.getClients()<<endl;
    out << agency.getPackets()<<endl;
    return out;
}
