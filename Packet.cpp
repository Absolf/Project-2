#include "Packet.h"
#include "Date.h"
#include "Client.h"

//Constructors of the Packet class
Packet::Packet() {}
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

//GET methods
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

//SET methods
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

vector<Packet> packData(string packFile) //function that creates a vector containing all the multiple Travel Packages provided by the agency.
{
    vector<Packet> data_of_pack;
    ifstream data;
    string lines;
    vector<string> pack_temp;
    data.open(packFile);
    getline(data, lines); // Eliminates the first line;
    while (getline(data, lines, '\n'))
    {
        if (lines == "::::::::::") // when find's it will create a new Packet object to be insert into the vector of Packets
        {
            Packet newPack(pack_temp);
            data_of_pack.push_back(newPack);
            pack_temp.clear();
        }
        else
        {
            pack_temp.push_back(lines); // while "::::::::::" not found, will keep adding each line to the string vector (each position of the string vector is releted to a Packet data)
        }
    }
    Packet newPack(pack_temp); // creates the last Packet object
    data_of_pack.push_back(newPack);
    data.close(); // closes the file

    return data_of_pack;
}

//get's the ID of the last pack to be added to the packs file
int lastID(vector<Packet> &vec)
{
    int id = vec.back().id;
    if (id < 0) // if the last ID is negative, it will still get it, but the new one will be positive (as long as is has places)
    {
        id *= -1;
        id++;
    }
    else
    {
        id++; // add +1 to the id of the last packet of the agency
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
        if (i == 0) //For the local
        {
            line = vec.at(i);
            getline(cin, line);
            new_pack.push_back(line);
        }
        if (i == 1) // for the start date
        {
            string startData;
            cin.clear();
            cout << vec.at(i);
            cin >> startData;
            bool isDate = verifyDate(startData); // verify if the input is actualy a date
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
        else if (i == 2) // for the end date
        {
            string endData = readString(vec.at(i));
            bool isDate = verifyDate(endData);
            while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
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

vector<string> packs_questions(vector<Packet> &vec) //Automates the input of information of new packages
{
    int id = lastID(vec);
    vector<string> nPacks_questions = {"Location: ", "Start Date: ", "End Date: ", "Price per person: ", "Max places: ", "Sold Places: "}; //string vector containing my strings
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

void print_all_packs(vector<Packet> &vec) //print all the packs i have in my vector of packets
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

void update_packs(vector<Packet> &vec) //actualize the data inside a packet
{
    vector<Packet>::iterator it;
    it = vec.begin();
    int update_id = readInteger("What's the ID of the package you would like to update?");
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
            op = readInteger("1 - Local \n2 - start date \n3 - End date \n4 - Price per person \n5 - Ammount of places \n6 - Sold places \n");
            if (op == 1)
            {
                line = readString("New local: ");
                vec.at(i).setLocal(line);
            }
            if (op == 2)
            {
                string startDate = readString("New start date: ");
                bool isDate = verifyDate(startDate);
                while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
                {
                    startDate = readString("New start date: ");
                    isDate = verifyDate(startDate);
                }
                Date start_date(startDate);
                vec.at(i).setBeginDate(start_date);
            }
            if (op == 3)
            {
                string endDate = readString("New end date: ");
                cout << endDate;
                bool isDate = verifyDate(endDate);
                while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
                {
                    endDate = readString("New end date: ");
                    isDate = verifyDate(endDate);
                }
                cout << endDate;
                Date end_date(endDate);
                vec.at(i).setEndDate(end_date);
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
    string destiny = readString("What's the destiny you would like to access?");
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
    string start_date = readString("What is the start date? \n*Input example '2019/05/21'");
    bool isDate = verifyDate(start_date);
    while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
    {
        start_date = readString("New start date: ");
        isDate = verifyDate(start_date);
    }
    Date startDate(start_date);
    string end_date = readString("What is the end date? \n*Input example '2019/05/26'");
    isDate = verifyDate(end_date);
    while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
    {
        end_date = readString("New end date: ");
        isDate = verifyDate(end_date);
    }
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
    int cont = 0;
    string start_date = readString("What is the start date? \n*Input example '2019/05/21'");
    bool isDate = verifyDate(start_date);
    while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
    {
        start_date = readString("New start date: ");
        isDate = verifyDate(start_date);
    }
    Date startDate(start_date);
    string end_date = readString("What is the end date? \n*Input example '2019/05/26'");
    isDate = verifyDate(end_date);
    while (isDate == false)// while the manager doesn't put a valid input for date, it will keep asking him for it
    {
        end_date = readString("New end date: ");
        isDate = verifyDate(end_date);
    }
    Date endDate(end_date);
    string destiny = readString("What's the destiny you would like to access?");
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
    string clientNif = readString("What's the nif of the client you want to verify?");
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
    string clientNif = readString("What's the nif of the client you want to verify?");
    int id = readInteger("Type the ID of the package you would like to sell to the client");
    vector<int> clientPacks;
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
                        //this bit of the code will put the new packs at the client packs parameter
                        stringstream newPacks;
                        copy(clientPacks.begin(), clientPacks.end(), ostream_iterator<int>(newPacks, ";"));
                        string substitute = newPacks.str();
                        substitute = substitute.substr(0, substitute.length() - 1);
                        client.at(i).setPacketList(substitute);
                        client.at(i).setTotalPurchased(client.at(i).getTotalPurchased() + packs.at(j).pricePerPerson);
                        cout << "\nSold!\n"; //just to check if ti was sold on screen
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


void printPackageAllClients(vector<Packet> &packs, vector<Client> &client) //print packages sold to all clients
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


void add_packs(vector<Packet> &vec) //Manage to add a new Packet to my current vector of packs
{
    vector<string> new_pack = packs_questions(vec);
    Packet test(new_pack);
    vec.push_back(test);
}


void remove_packs(vector<Packet> &vec) //Remove a pack from my vector.
{
    int id = readInteger("What's the ID of the package you would like to remove?");
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).id == id)
        {
            auto it = vec.begin() + i;
            rotate(it, it + 1, vec.end());
            cout << "The Package of id[" << vec.back().id << "] it's being deleted!" << endl; // Shows on screen the packet id just for verification
            vec.pop_back();
        }
    }
}

/*********************************
 * Show Packet information
 ********************************/

void writePacks(string file_name, vector<Packet> &vec) // writes the content of the vector packet to a file
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

ostream &operator<<(ostream &out, const Packet &packet) // this is where the magic happens and allows << operator receive an object ( of packet)
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