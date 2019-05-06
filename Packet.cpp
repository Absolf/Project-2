#include "Packet.h"
#include <sstream>

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

//function responsible to understand wich components of the file is a Travel Package.

//function that creates a vector containing all the multiple Travel Packages provided by the agency.
vector<Packet> packData(string packFile)
{
    vector<Packet> data_of_pack;
    ifstream data;
    string lines;
    vector<string> pack_temp;
    data.open(packFile);
    getline(data, lines); // Eliminates the first line IDK what to do with it yet.
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
    //cout << data_of_pack.at(0).start_date.ano << endl; // test to verify if i'm gettin the right values to my vector of Packets
    data.close();
    cout << "Ive done it sucessfully!" << endl;
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
    for (size_t i = 0; i<aux.size(); i++) {
        new_pack.push_back(aux.at(i));
    }
    return new_pack;
}

/*
void print_all_packs(vector<Packet> &vec)
{
    vector<Packet>::iterator it;
    it = vec.begin();
    int i = 0;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << "::::::::::::::::::" << endl;
        cout << "Unique id: " << vec.at(i).getId() << "\nLocal: " << vec.at(i).getLocal() << "\nDate of start: " << returnDate(vec.at(i).getBeginDate()) << "\nDate of end: " << returnDate(vec.at(i).getEndDate())
             << "\nPrice per person: " << vec.at(i).getPricePerPerson() << "\nAmmount of places: " << vec.at(i).getMaxPlaces() << "\nSold places: " << vec.at(i).getSoldPlaces() << endl;
        cout << ":::::::::::::::::::::::::::::::";
        i++;
    }
}
*/

void add_packs(vector<Packet> &vec)
{
    vector<string> new_pack = packs_questions(vec);
    Packet test(new_pack);
    vec.push_back(test);
    //return vec;
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
            operator<<(file, vec.at(i));
            if (i < vec.size() - 1)
            {
                file << "::::::::::";
            }
        }
    }
    file.close();
}
*/
ostream &operator<<(ostream &out, const Packet &packet)
{
    /*
    file << endl;
    file << packet.id << endl;
    file << packet.local << endl;
    file << return_date(packet.startDate) << endl;
    file << return_date(packet.endDate) << endl;
    file << packet.pricePerPerson << endl;
    file << packet.startPlaces << endl;
    file << packet.soldPlaces << endl;
    */
}