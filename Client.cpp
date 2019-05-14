
#include "Client.h"

Client::Client(vector<string> clients)
{
  this->name = clients.at(0);
  stringstream nif(clients.at(1));
  nif >> this->nif;
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

unsigned Client::getTotalPurchased() const
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
unsigned Client::setTotalPurchased(unsigned totalPurchased)
{
  this->totalPurchased = totalPurchased;
}

// outros metodos

//Gerar o vetor de objetos da class a partir do client (FILE -> VECTOR<CLIENT>)
vector<Client> clientData(string clientFile)
{
  vector<Client> client_info;
  ifstream file;
  string lines;
  vector<string> client_temp;
  file.open(clientFile);
  while (getline(file, lines, '\n'))
  {
    if (lines == "::::::::::")
    {
      Client newClient(client_temp);
      client_info.push_back(newClient);
      client_temp.clear();
    }
    else
    {
      client_temp.push_back(lines);
    }
  }
  Client newClient(client_temp);
  client_info.push_back(newClient);
  file.close();
  return client_info;
}

//creates a vector of packets id
void clients_packs(string line, vector<int> &aux)
{
  line = regex_replace(line, regex(";"), " ");
  istringstream test(line);
  int i;
  while (test >> i)
  {
    aux.push_back(i);
  }
}

//Add new client (using QUESTIONS)
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
  vector<string> new_client;
  cout << "::::::::::" << endl;
  cin.ignore();
  for (size_t i = 0; i < vec.size(); i++)
  {
    cout << vec.at(i);
    getline(cin, line);
    new_client.push_back(line);
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

//REMOVE - remove a client (remove all data of that client)
void remove_client(vector<Client> &vec)
{
  unsigned int nif;
  cout << "What's the nif of the client you want to remove?" << endl;
  cin >> nif;
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

//update/change the information of a client; (NOTA: Adicionei como função da class)
void update_client(vector<Client> &vec)
{
  int op;
  string line;
  unsigned int nif;
  cout << "What's the nif of the client you want to update? " << endl;
  cin >> nif;
  cin.ignore();
  vector<string> menu = {"Name", "NIF", "Family Number", "Address", "Package"};
  for (size_t i = 0; i < vec.size(); i++)
  {
    if (vec.at(i).getNifNumber() == nif)
    {
      op = readOptions(menu);
      if (op == 1)
      {
        cout << "New Name: ";
        cin.ignore();
        getline(cin, line);
        vec.at(i).setName(line);
      }
      if (op == 2)
      {
        cout << "New NIF: ";
        cin.ignore();
        getline(cin, line);
        vec.at(i).setNifNumber(stoi(line));
      }
      if (op == 3)
      {
        cout << "New family number: ";
        cin.ignore();
        getline(cin, line);
        //istringstream transform(line);  //-----------
        vec.at(i).setFamilySize(stoi(line));
      }
      if (op == 4)
      {
        cout << "New address: ";
        cin.ignore();
        getline(cin, line);
        Address aux(line);
        vec.at(i).setAddress(aux); //Usa o construtor da class Address com string como parametro
      }
      if (op == 5)
      {
        cout << "New package: ";
        cin.ignore();
        getline(cin, line);
        vec.at(i).setPacketList(line);
      }
    }
  }
}

//print a specific client
void printClient(vector<Client> &vec)
{
  cout << ":::::Please provide us with the client Name or NIF:::::";
  cout << "Wich information suits you?  ";
  vector<string> menu = {"Name", "NIF"};
  int op = readOptions(menu);
  string line;
  int cont = 0;
  if (op == 1)
  {
    cout << "Whats the name of the client?" << endl;
    cin.ignore();
    getline(cin, line);
    for (size_t i = 0; i < vec.size(); i++)
    {
      if (line == vec.at(i).getName())
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
  if (op == 2)
  {
    cin.ignore();
    cout << "Whats the NIF of the client?" << endl;
    getline(cin, line);
    for (size_t i = 0; i < vec.size(); i++)
    {
      if (stoi(line) == vec.at(i).getNifNumber())
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

//Print all my clients.
void print_all_clients(vector<Client> &vec)
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

/*
//Função que verifica a validade do input
void Insert_valid()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '/n');

		cout << "Invalid input!" << endl;
	}
}
*/

void writeClients(string file_name, vector<Client> &vec)
{
  cout << "A copy of the previous file have been made in case of data lost!";
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

//MODIFICADO - Overload of "<<" operator
ostream &operator<<(ostream &out, const Client &client)
{
  out << client.name << endl;
  out << client.nif << endl;
  out << client.familySize << endl;
  out << client.address.getAddressString() << endl;
  out << client.packets << endl;
  out << client.totalPurchased << endl;
}
