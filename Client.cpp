#include "Client.h"

//Construtors of the class objects Client
Client::Client()
{
}
Client::Client(vector<string> clients)
{
    this->name = clients.at(0);
    this->nif = stoi(clients.at(1));
    stringstream famSize(clients.at(2));
    famSize >> this->familySize;
    Address address(clients.at(3));
    this->address = address;
    this->packets = clients.at(4);
    stringstream totPurch(clients.at(5));
    totPurch >> this->totalPurchased;
}

// GET methods

string Client::getName() const
{
    return name;
}

unsigned Client::getNifNumber() const
{

    return nif;
}

unsigned short Client::getFamilySize() const
{

    return familySize;
}

Address Client::getAddress() const
{

    return address;
}

string Client::getPacketList() const
{

    return packets;
}

double Client::getTotalPurchased() const
{

    return totalPurchased;
}

// metodos SET

void Client::setName(string name)
{

    this->name = name;
    ;
}

void Client::setNifNumber(unsigned nif)
{

    this->nif = nif;
}

void Client::setFamilySize(unsigned short familySize)
{

    this->familySize = familySize;
}
void Client::setAddress(Address address)
{
    this->address = address;
}
void Client::setPacketList(string packets)
{
    this->packets = packets;
}
void Client::setTotalPurchased(double totalPurchased)
{
    this->totalPurchased = totalPurchased;
}

// outros metodos

//Creates a vector with all of the Objects of the Class Clients contained in the clients file
vector<Client> clientData(string clientFile)
{
    vector<Client> client_info;
    ifstream file;
    string lines;
    vector<string> client_temp;
    file.open(clientFile);
    while (getline(file, lines, '\n')) //Cicles through the client lines in the clients file
    {
        if (lines == "::::::::::")
        {
            Client newClient(client_temp); //Creats a temporary client
            client_info.push_back(newClient); //Adds the temporary client to the clients vector
            client_temp.clear();
        }
        else
        {
            client_temp.push_back(lines); //adds client info to the temporary client
        }
    }
    Client newClient(client_temp);
    client_info.push_back(newClient);
    file.close();
    return client_info;
}

//creates a vector of packets id (for a client)
void clients_packs(string line, vector<int> &aux)
{
    line = regex_replace(line, regex(";"), " "); //Returns the clients packs as a string
    istringstream test(line);
    int i;
    while (test >> i)
    {
        aux.push_back(i);
    }
}

//Add new client (using the function client_questions)
vector<Client> add_client(vector<Client> &vec)
{
    vector<string> new_client = clients_questions();
    Client aux(new_client);
    vec.push_back(aux);
    return vec;
}

//it will automate de clients_question job
vector<string> clientQuestionHandler(vector<string> vec)
{
    string line;
    string text;
    vector<string> new_client;
    cout << "::::::::::" << endl;
    cin.clear();
    for (size_t i = 0; i < vec.size(); i++)
    {
        if((i == 0) || (i == 3) || (i == 4)){ // for all my "string" inputs "can be empty"
            line = readString(vec.at(i));
            new_client.push_back(line);
            cout.clear();
        }
        else if(i == 1){
            int nif = readInteger(vec.at(i)); //verify the nif
            new_client.push_back(to_string(nif));
        }
        else if(i == 2)
        {
            int famSize = readInteger(vec.at(i)); //verify the family size
            new_client.push_back(to_string(famSize));
        }
        else if(i == 5){
            int totlPurch = readInteger(vec.at(i)); // verify the total purchased (can be 0)
            new_client.push_back(to_string(totlPurch));
        }
    }
    cout << "::::::::::" << endl;
    return new_client;
}

//creates a new vector<string> with the data needed to create my new client
vector<string> clients_questions()
{
    string line;
    vector<string> nClient_questions = {"Client name: ", "NIF number: ", "Nº family members: ", "Address: ", "Package list: ", "Spent ammount: "};
    cout << endl;
    vector<string> new_client = clientQuestionHandler(nClient_questions);
    return new_client;
}

//Remove a client from the clients vector (remove all data of that client)
void remove_client(vector<Client> &vec)
{
    unsigned int nif = readInteger("What's the nif of the client you want to remove?");
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).getNifNumber() == nif)
        {
            auto it = vec.begin() + i;
            rotate(it, it + 1, vec.end()); //puth the wished client at the end
            cout << "The client with the NIF: " << vec.back().getNifNumber() << " it's being deleted! " << endl;
            vec.pop_back();
        }
    }
}

//Update/change the information of a client;
void update_client(vector<Client> &vec)
{
    int op;
    string line, text;
    unsigned int nif = readInteger("What's the nif of the client you want to remove?");
    vector<string> menu = {"Name", "NIF", "Family Number", "Address", "Package"};
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).getNifNumber() == nif) //Cycle that asks which client info to change (select the client through its nif)
        {
            op = readOptions(menu);
            if (op == 1)
            {
                line = readString("New Name: ");
                vec.at(i).setName(line);
            }
            if (op == 2)
            {
                text = "New NIF: ";
                vec.at(i).setNifNumber(readInteger(text));
            }
            if (op == 3)
            {
                text = "New family number: ";
                vec.at(i).setFamilySize(readInteger(text));
            }
            if (op == 4)
            {
                line = readString("New address: ");
                Address aux(line);
                vec.at(i).setAddress(aux); //Uses the constructor of the class with a string
            }
            if (op == 5)
            {
                line = readString("New package: ");
                vec.at(i).setPacketList(line);
            }
        }
    }
}

//Displays a specific client in the screen
void printClient(vector<Client> &vec)
{
    cout << ":::::Please provide us with the client Name or NIF:::::";
    cout << "Wich information suits you?  ";
    vector<string> menu = {"Name", "NIF"}; //Select how to search the client (Name or Nif)
    int op = readOptions(menu);
    string line;
    int cont = 0;
    if (op == 1) //Name option
    {
        line = readString("Whats the name of the client?");
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (line == vec.at(i).getName()) //Cycle through the client's attributes displaying them
            {
                cout << endl;
                cout << vec.at(i) << endl;
                cont++;
                if (cont > 1 && i < (vec.size() - 1))
                {
                    cout << "::::::::::" << endl;
                }
            }
        }
    }
    if (op == 2) //Nif option
    {
        line = readString("Whats the NIF of the client?");
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (stoi(line) == vec.at(i).getNifNumber()) //Cycle through the client's attributes displaying them
            {
                cout << endl;
                cout << vec.at(i) << endl;
                cont++;
                cont++;
                if (cont > 1 && i < (vec.size() - 1))
                {
                    cout << "::::::::::" << endl;
                }
            }
        }
    }
}


void print_all_clients(vector<Client> &vec) //Displays all clients in the screen
{
    cout << ":::::The current clients in our database are:::::";
    int cont = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << endl;
        cout << vec.at(i) << endl;
        cont++;
        if (cont > 1 && i < (vec.size() - 1))
        {
            cout << "::::::::::" << endl;
        }
    }
}

//Saves the clients vector in the client file
void writeClients(string file_name, vector<Client> &vec)
{
    ofstream file;
    file.open(file_name);
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

//Overload of "<<" operator to display all client's info
ostream &operator<<(ostream &out, const Client &client)
{
    out << client.name << endl;
    out << client.nif << endl;
    out << client.familySize << endl;
    out << client.address.getAddressString() << endl;
    out << client.packets << endl;
    out << client.totalPurchased << endl;
}