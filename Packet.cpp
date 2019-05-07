#pragma once
#include "Packet.h"
#include "Address.h"

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
unsigned int Packet::getId() const
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
    cout << "data pack working" << endl;

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

//Other functions
vector<string> packQuestionHandler(vector<string> vec)
{
    string line;
    vector<string> new_pack;
    cout << "::::::::::::::" << endl;
    cin.ignore();
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i);
        getline(cin, line);
        new_pack.push_back(line);
    }
    cout << ":::::::::::::";
    return new_pack;
}

//Automates the input of information of new packages
vector<string> packs_questions(vector<Packet> &vec)
{
    int id = lastID(vec);
    vector<string> nPacks_questions = {"Location: ", "Start Date: ", "End Date: ", "Price per person: ", "Max places: ", "Sold Places: "};
    cout << endl;
    vector<string> new_pack;
    new_pack.push_back(to_string(id));
    vector<string> aux = packQuestionHandler(nPacks_questions);
    for (size_t i = 0; i < aux.size(); i++)
    {
        new_pack.push_back(aux.at(i));
    }
    return new_pack;
}

void print_all_packs(vector<Packet> &vec)
{
    vector<Packet>::iterator it;
    it = vec.begin();
    int i = 0;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << "::::::::::::::::::::::::::::::::" << endl;
        cout << vec.at(i) << endl;
        cout << ":::::::::::::::::::::::::::::::" << endl;
    }
}

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
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if (vec.at(i).id == update_id)
        {
            cout << "The id[" << vec.at(i).id << "] have been found" << endl;
            cout << "proceeding to update into my package " << endl;
            cout << "::::::::::::::::::::" << endl;
            cout << "options: " << endl;
            cout << "1 - Local \n2 - start date \n3 - End date \n4 - Price per person \n5 - Ammount of places \n6 - Sold places" << endl;
            cin >> op;

            if (op == 1)
            {
                cout << "New data?: " << endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).local = line;
            }
            if (op == 2)
            {
                cout << "New data?: " << endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).startDate.setDateString(line);
            }
            if (op == 3)
            {
                cout << "New data?: " << endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).endDate.setDateString(line);
            }
            if (op == 4)
            {
                cout << "New data?: " << endl;
                cin.ignore();
                getline(cin, line);
                istringstream price_converter(line);
                price_converter >> vec.at(i).pricePerPerson;
            }
            if (op == 5)
            {
                cout << "New data?: " << endl;
                cin.ignore();
                getline(cin, line);
                istringstream start_place_converter(line);
                start_place_converter >> vec.at(i).maxPlaces;
            }
            if (op == 6)
            {
                cout << "New data?: " << endl;
                cin.ignore();
                getline(cin, line);
                istringstream sold_places_converter(line);
                sold_places_converter >> vec.at(i).soldPlaces;
            }
        }
        i++;
    }
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

//Function to visualize packs data within a specific destiny
void printDestinyPack(vector<Packet> &vec)
{
    string destiny;
    cout << "What's the destiny you would like to access?" << endl;
    cin >> destiny;
    int cont;
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
                cout << ":::::::::::::::::::::::::::::::";
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
/*
void writePacks(string file_name, vector<Packet> &vec)
{
    //makeCopy(file_name);
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
                file << "::::::::::"<<endl;
            }
        }
    }
    file.close();
}
*/
ostream &operator<<(ostream &out, const Packet &packet)
{
    out << packet.id << endl;
    out << packet.local << endl;
    out << packet.getBeginDate().getDateString() << endl;
    out << packet.getEndDate().getDateString() << endl;
    out << packet.pricePerPerson << endl;
    out << packet.maxPlaces << endl;
    out << packet.soldPlaces << endl;
}
