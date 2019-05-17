#include "Packet.h"
#include "Date.h"
#include "Client.h"

Packet::Packet() {}
Packet::Packet(int id, string local, Date startDate, Date endDate, double pricePerPerson, int maxPlaces, int soldPlaces) : id(id), local(local), startDate(startDate), endDate(endDate), pricePerPerson(pricePerPerson), maxPlaces(maxPlaces), soldPlaces(soldPlaces)
{
}
Packet::Packet(vector<string> pack_vec)
{

    stringstream teste(pack_vec.at(0));
    teste >> this->id;
    //this->id = stoi((pack_vec.at(0)));
    this->local = pack_vec.at(1);
    startDate.setDateString(pack_vec.at(2));
    endDate.setDateString(pack_vec.at(3));
    this->pricePerPerson = stod(pack_vec.at(4));
    this->maxPlaces = stoul(pack_vec.at(5));
    this->soldPlaces = stoul(pack_vec.at(6));
}

//metodos GET
int Packet::getId() const
{
    return id;
}

string Packet::getLocal() const
{
    return local;
}

Date Packet::getBeginDate() const
{
    return startDate;
}

Date Packet::getEndDate() const
{
    return endDate;
}

double Packet::getPricePerPerson() const
{
    return pricePerPerson;
}

int Packet::getMaxPlaces() const
{
    return maxPlaces;
}

int Packet::getSoldPlaces() const
{
    return soldPlaces;
}

//metodos SET
void Packet::setId(int id)
{
    this->id = id;
}

void Packet::setLocal(string local)
{
    this->local = local;
}

void Packet::setBeginDate(Date startDate)
{
    this->startDate = startDate;
}

void Packet::setEndDate(Date endDate)
{
    this->endDate = endDate;
}

void Packet::setPricePerPerson(double pricePerPerson)
{
    this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPlaces(int maxPlaces)
{
    this->maxPlaces = maxPlaces;
}
void Packet::setSoldPlaces(int soldPlaces)
{
    this->soldPlaces = soldPlaces;
}

/*********************************
 * Other functions
 ********************************/

//function that creates a vector containing all the multiple Travel Packages provided by the agency.
vector<Packet> packData(string packFile)
{
    vector<Packet> data_of_pack;
    ifstream data;
    string lines;
    vector<string> pack_temp;
    data.open(packFile);
    getline(data, lines); // Eliminates the first line;
    while (getline(data, lines, '\n'))
    {
        if (lines == "::::::::::")
        {
            Packet newPack(pack_temp);
            data_of_pack.push_back(newPack);
            pack_temp.clear();
        }
        else
        {
            pack_temp.push_back(lines);
        }
    }
    Packet newPack(pack_temp);
    data_of_pack.push_back(newPack);
    data.close();

    return data_of_pack;
}

//get's the ID of the last pack to be added to the packs file
int lastID(vector<Packet> &vec)
{
    int id = vec.back().id;
    if (id < 0)
    {
        id *= -1;
        id++;
    }
    else
    {
        id++;
    }
    return id;
}

//Handle the questions that i have to output to the user when creating a new packet
vector<string> packQuestionHandler(vector<string> vec)
{
    string line;
    vector<string> new_pack;

    cout << "::::::::::::::" << endl;
    cin.ignore();
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (i == 0)
        {
            cout.clear();
            cout << vec.at(i);
            getline(cin, line);
            new_pack.push_back(line);
        }
        if (i == 1)
        {
            string startData;
            cin.clear();
            cout << vec.at(i);
            cin >> startData;
            bool isDate = verifyDate(startData);
            while (isDate == false)
            {
                cin.clear();
                cout << vec.at(i);
                cin >> startData;
                isDate = verifyDate(startData);
            }
            cin.clear();
            new_pack.push_back(startData);
        }
        else if (i == 2)
        {
            string endData;
            cin.clear();
            cout << vec.at(i);
            cin >> endData;
            bool isDate = verifyDate(endData);
            while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him
            {
                cin.clear();
                cout << vec.at(i);
                cin >> endData;
                isDate = verifyDate(endData);
            }
            cout.clear();
            cin.clear();
            new_pack.push_back(endData);
        }
        else if (i == 3) //When the question about price per person be made, it will verify if it's a valid input (of double type)
        {
            double pricePerson = readDouble(vec.at(i));
            new_pack.push_back(to_string(pricePerson));
        }
        else if (i == 4) //When the question about maximum amount of places be made, it will verify if it's a valid input (of int type)
        {
            int maxPlaces = readInteger(vec.at(i));
            new_pack.push_back(to_string(maxPlaces));
        }
        else if (i == 5) //When the question about sold places be made, it will verify if it's a valid input (of int type)
        {
            int soldPlaces = readInteger(vec.at(i));
            new_pack.push_back(to_string(soldPlaces));
        }
        cin.clear();
    }
    cout << ":::::::::::::";
    return new_pack;
}

//Automates the input of information of new packages
vector<string> packs_questions(vector<Packet> &vec)
{
    int id = lastID(vec);
    vector<string> nPacks_questions = {"Location: ", "Start Date: ", "End Date: ", "Price per person: ", "Max places: ", "Sold Places: "};
    vector<string> new_pack;
    new_pack.push_back(to_string(id));
    vector<string> aux = packQuestionHandler(nPacks_questions);
    cout << "i've a new pack" << endl;
    for (size_t i = 0; i < aux.size(); i++)
    {
        new_pack.push_back(aux.at(i));
    }
    return new_pack;
}

//print all the packs i have in my vector of packets
void print_all_packs(vector<Packet> &vec)
{
    int cont = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << "::::::::::::::::::::::::::::::::" << endl;
        cout << vec.at(i) << endl;
        cont++;
        if (cont < vec.size() - 1)
        {
            cout << ":::::::::::::::::::::::::::::::" << endl;
        }
    }
}

//atualize the data inside a packet
void update_packs(vector<Packet> &vec)
{
    vector<Packet>::iterator it;
    it = vec.begin();
    int update_id;
    cout << "What's the ID of the package you would like to update?" << endl;
    cin >> update_id;
    int i = 0;
    int op;

    string line;
    string text;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if (vec.at(i).getId() == update_id)
        {
            cout << "The id[" << vec.at(i).getId() << "] have been found" << endl;
            cout << "proceeding to update into my package " << endl;
            cout << "::::::::::::::::::::" << endl;
            cout << "options: " << endl;
            cout << "1 - Local \n2 - start date \n3 - End date \n4 - Price per person \n5 - Ammount of places \n6 - Sold places" << endl;
            cin >> op;

            if (op == 1)
            {
                cout << "New Local: " << endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).setLocal(line);
            }
            if (op == 2)
            {
                cout << "New start date: " << endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).getBeginDate().setDateString(line);
            }
            if (op == 3)
            {
                cout << "New end date: " << endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).getEndDate().setDateString(line);
            }
            if (op == 4)
            {
                text = "New price per person: ";
                vec.at(i).setPricePerPerson(readDouble(text));
            }
            if (op == 5)
            {
                text = "New max places: ";
                vec.at(i).setMaxPlaces(readInteger(text));
            }
            if (op == 6)
            {
                text = "New sold places: ";
                vec.at(i).setSoldPlaces(readInteger(text));
            }
        }
        i++;
    }
}

//Function to visualize packs data within a specific destiny
void printDestinyPack(vector<Packet> &vec)
{
    string destiny;
    cout << "What's the destiny you would like to access?" << endl;
    cin >> destiny;
    int cont = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        string vec_source = vec.at(i).local;
        vector<string> vec_dest;
        tokenize(vec_source, ' ', vec_dest);
        if (destiny == vec_dest.at(0))
        {
            cout << endl;
            cout << vec.at(i);
            cont++;
            if (cont > 1 && i < (vec.size() - 1))
            {
                cout << "::::::::::";
            }
        }
    }
}

//Visualize information of a pack between dates
void printFromDates(vector<Packet> &vec)
{
    string start_date;
    string end_date;
    cin.clear();
    cin.ignore();
    cout << "What is the start date? \n*Input exemple '2019/05/21'" << endl;
    getline(cin, start_date);
    Date startDate(start_date);
    cout << "What is the end date? \n*Input exemple '2019/05/26'" << endl;
    getline(cin, end_date);
    Date endDate(end_date);
    cout << endl;
    int cont = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (((vec.at(i).startDate.getMonth() >= startDate.getMonth()) && (vec.at(i).endDate.getMonth() <= endDate.getMonth())) && ((vec.at(i).startDate.getDay() >= startDate.getDay()) && (vec.at(i).endDate.getDay() <= endDate.getDay())))
        //if i get here it mean we have any travel trip within the year specified
        {
            cout << endl;
            cout << vec.at(i);
            cont++;
            if (cont > 1 && i < (vec.size() - 1))
            {
                cout << "::::::::::" << endl;
            }
        }
    }
}

//Visualize information of a pack within a destiny and between dates
void printDestinyAndDates(vector<Packet> &vec)
{
    string destiny;
    cout << "What's the destiny you would like to access?\n"
         << endl;
    cin >> destiny;
    int cont = 0;
    string start_date;
    string end_date;
    cin.clear();
    cin.ignore();
    cout << "What is the start date? \n*Input exemple '2019/05/21'" << endl;
    getline(cin, start_date);
    Date startDate(start_date);
    cout << "What is the end date? \n*Input exemple '2019/05/26'" << endl;
    getline(cin, end_date);
    Date endDate(end_date);
    cout << endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        string vec_dest = vec.at(i).local;
        vector<string> dest_vec;
        tokenize(vec_dest, ' ', dest_vec);
        if (destiny == dest_vec.at(0) && (((vec.at(i).startDate.getMonth() >= startDate.getMonth()) && (vec.at(i).endDate.getMonth() <= endDate.getMonth())) && ((vec.at(i).startDate.getDay() >= startDate.getDay()) && (vec.at(i).endDate.getDay() <= endDate.getDay()))))
        {
            cout << endl;
            cout << vec.at(i);
            cont++;
            if (cont > 1 && i < (vec.size() - 1))
            {
                cout << "::::::::::::";
            }
        }
    }
}

//print a certain package sold to a client
void printToClient(vector<Packet> &vec, vector<Client> &client)
{
    string clientNif;
    cin.ignore();
    cout << "What's the nif of the client you want to verify?" << endl;
    getline(cin, clientNif);
    vector<int> clientPacks;
    int cont = 0;
    for (size_t i = 0; i < client.size(); i++)
    {
        if (to_string(client.at(i).getNifNumber()) == clientNif)
        {
            clients_packs(client.at(i).getPacketList(), clientPacks);
            for (size_t j = 0; j < vec.size(); j++)
            {
                if (find(clientPacks.begin(), clientPacks.end(), vec.at(j).getId()) != clientPacks.end())
                {
                    cout << endl;
                    cout << vec.at(j);
                    cont++;
                    if (cont > 1 && i < (vec.size() - 1))
                    {
                        cout << "::::::::::" << endl;
                    }
                }
            }
        }
    }
}

//Manage to sell a package to a certain client
void sellToClient(vector<Packet> &packs, vector<Client> &client)
{
    string clientNif;
    int id;
    vector<int> clientPacks;
    cout << "Type the NIF of the client you would like to sell the package" << endl;
    cin.ignore();
    getline(cin, clientNif);
    cout << "Type the ID of the package you would like to sell to the client" << endl;
    cin >> id;
    for (size_t i = 0; i < client.size(); i++)
    {
        if (to_string(client.at(i).getNifNumber()) == clientNif)
        {
            clients_packs(client.at(i).getPacketList(), clientPacks);
            if (find(clientPacks.begin(), clientPacks.end(), id) != clientPacks.end())
            {
                cout << "Client already have that package! " << endl;
            }
            else
            {
                for (size_t j = 0; j < packs.size(); j++)
                {
                    if (packs.at(j).id == id)
                    {
                        //This chunk of the code, before the next if, adds 1 to the sold places and add to the client vector the new id sold to that client
                        istringstream sold(to_string(packs.at(j).getSoldPlaces()));
                        int addi;
                        sold >> addi;
                        addi += 1;
                        packs.at(j).setSoldPlaces(addi);
                        clientPacks.push_back(id);
                        //This bit transform the ID into a negative number if sold places = to start places
                        if (packs.at(j).getSoldPlaces() == packs.at(j).getMaxPlaces())
                        {
                            packs.at(j).id *= -1;
                        }
                        //this bit of the code will puth the new packs at the client packs parameter
                        stringstream newPacks;
                        copy(clientPacks.begin(), clientPacks.end(), ostream_iterator<int>(newPacks, ";"));
                        string substitute = newPacks.str();
                        substitute = substitute.substr(0, substitute.length() - 1);
                        client.at(i).setPacketList(substitute);
                        client.at(i).setTotalPurchased(client.at(i).getTotalPurchased() + packs.at(j).pricePerPerson);
                        cout << "\nSold!\n";
                    }
                    if (packs.at(j).id == (id * -1) && (packs.at(j).getMaxPlaces() == packs.at(j).getSoldPlaces()))
                    {
                        cout << "\n*Warning!*\n*Sorry! Travel Package not available, reached it's maximum capacity!" << endl;
                    }
                }
            }
        }
    }
}

//print packages sold to all clients
void printPackageAllClients(vector<Packet> &packs, vector<Client> &client)
{

    int cont = 0;

    for (size_t i = 0; i < client.size(); i++)
    {
        vector<int> clientPacks;
        cout << "client name: " << client.at(i).getName() << endl;
        clients_packs(client.at(i).getPacketList(), clientPacks);
        for (size_t j = 0; j < packs.size(); j++)
        {
            if (find(clientPacks.begin(), clientPacks.end(), packs.at(j).getId()) != clientPacks.end())
            {
                cout << "client : " << client.at(i).getName() << " has the package: " << endl;
                cout << endl;
                cout << packs.at(j) << endl;
                cont++;
                if (cont > 1 && i < (packs.size() - 1))
                {
                    cout << "::::::::::" << endl;
                }
            }
        }
    }
}

//Manage to add a new Packet to my current vector of packs
void add_packs(vector<Packet> &vec)
{
    vector<string> new_pack = packs_questions(vec);
    Packet test(new_pack);
    vec.push_back(test);
    //return vec;
}

//Remove a pack from my vector.
void remove_packs(vector<Packet> &vec)
{
    int id;
    cout << "What's the ID of the package you would like to remove?" << endl;
    cin >> id;
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).id == id)
        {
            auto it = vec.begin() + i;
            rotate(it, it + 1, vec.end());
            cout << "The Package of id[" << vec.back().id << "] it's being deleted!" << endl;
            vec.pop_back();
        }
    }
}

/*********************************
 * Show Packet information
 ********************************/

// shows a packet content

void writePacks(string file_name, vector<Packet> &vec)
{
    ofstream file;
    file.open(file_name);
    file << vec.back().getId() << endl;
    if (file.is_open())
    {
        for (size_t i = 0; i < vec.size(); i++)
        {
            file << vec.at(i);
            if (i < vec.size() - 1)
            {
                file << "::::::::::" << endl;
            }
        }
    }
    file.close();
}
ostream &operator<<(ostream &out, const Packet &packet)
{
    out << packet.id << endl;
    out << packet.local << endl;
    out << packet.getBeginDate().getDateString() << endl;
    out << packet.getEndDate().getDateString() << endl;
    out << packet.pricePerPerson << endl;
    out << packet.maxPlaces << endl;
    out << packet.soldPlaces << endl;
    return out;
}