# PROGRAMMING - PROG - Project 2

[![N|Solid](https://sigarra.up.pt/feup/pt/WEB_GESSI_DOCS.download_file?p_name=F-370784536/logo_cores_oficiais.jpg)](https://nodesource.com/products/nsolid)

[![Build Status](https://github.com/Absolf/Project-1)](https://travis-ci.org/joemccann/dillinger)

This is the first project of the Programming subject taught in FEUP in the academic year 2018/2019
# Features:

1. Read and store agency, client and travel package information stored in files.
2. Manage client and package tours: create, change and remove a client or package tour.
3. Generate and display formatted information of a specific client.
4. Generate and display formatted information for all agency customers.
5. Generate and display formatted available tour packages (all, a specific destination, all between two dates, all relating to a specific destination and between two dates).
6. Generate and display formatted tour packages sold (to a specific customer, to
all customers).
7. Make the purchase of a tour package by a customer.
8. Calculate and display the number and total value of packages sold.



### Tech


* c++ first contact with the language

### Guide
first type the name of the file without ".txt" extension
```sh
 agency
```
A 'loading' screen will appear
Then choose what you want to manage

```sh
1 - Clients
2 - Package
0 - Quit
```
Type your choice:
```sh
1 - Create new Client
2 - Remove existing Client
3 - Update Client Information
4 - Print a specific client
5 - Print agency clients
0 - Quit
```
* Example of creating a new client
#
```sh
Client name: User test
NIF number: 2122232425
Nº family members: 4
Address: Rua qualquer/94/1ºDireita/4000-220/ Paranhos
Package list: 2 ; 1 ; 5
```
* Here, only the nº of the house/building after the street name has to be an integer. The rest of the data are of c++ string data type and will be managed to their proper position inside of the vector of clients by proper functions
* After each interaction with the program you will be asked if you want to repeat the action or not, usually 1 means yes and 0 means no
#
```sh
Do you want to add another client? 
1 - Yes 
0 - No 
```
* To remove, update and print a specific client the NIF will be asked and it is a single function. It will ask if you want to repeat the action with another client.
* As proof that a client has been added you can print a specific client using the previous NIF provided or just print all clients. Here I've printed all clients.

```sh
Name: Rui Manuel
NIF: 234987156
Family members: 4
----Address--- 
Rua: Rua Sem Fim 
Nº porta/prédio: 200
Andar:  5Esq 
Código postal: 1200‐001 
Localidade:  Lisboa
Packages: 10 ; 36 ; 2
::::::::::
Name: Belmiro Miguel
NIF: 111987666
Family members: 2
----Address--- 
Rua: Avenida dos Grilos 
Nº porta/prédio: 100
Andar:  ‐ 
Código postal: 2300‐101 
Localidade:  Coimbra
Packages: 100 ; 136 ; 20
::::::::::
Name: User test
NIF: 2122232425
Family members: 4
----Address--- 
Rua: Rua qualquer
Nº porta/prédio: 94
Andar: 1º Direita
Código postal:  Paranhos
Localidade: 
Packages: 2 ; 1 ; 5
```
* The proper input of the address is by using '/' after each piece of information.
* As for the packages use ';' to separate them.
#### Managing the Travel Packages

```sh
:::::::::::::::::::::::::::::::::::
             options             
:::::::::::::::::::::::::::::::::::
1 - Create new Package
2 - Remove existing Package
3 - Update Package Information
4 - Visualise Travel Packages
5 - Sell a package to a client
6 - Nº of sold Packages and total value
0 - Quit
Answer: 1 
```
* Here, to remove and update an existing package the ID of the package is used, a list of packages is printed just before this menu, so the user can check which package they want to select.
* Here's an example of a proper input for creating a new package. Unfortunately the months are not limited to 12 and the days are not limited to a maximum of 28,30 or 31 corresponding its month. The line for dates is a c++ string, that functionality will be implemented further in the project 2.
```sh
Local: Bahia - Salvador, Camaçari, Arembepe
Start date: 2020/06/05 
End date: 2020/09/20
Price per person: 1200
Max places: 30
Sold places: 0
```
#### Displaying Travel Packages Data:

```sh
How would you like to search for Travel Packs?
:::::::::::::::::::::::::::::::::::
             options             
:::::::::::::::::::::::::::::::::::
1 - All Travel Packs
2 - Related to a destination
3 - Between dates
4 - Related to a destination and between dates
5 - Sold to a client
6 - Sold to all clients
0 - Quit
Answer: 
```
* After choosing your option the way of a proper input follows the previous idea.
* To confirm that the recent Travel Package have been created, a list with all travel packages will be displayed on the screen
### Selling a package to a client:
```sh
Type the NIF of the client you would like to sell the package
111987666
Type the ID of the package you would like to sell to the client
1

Sold  <-- This means it has been sold, otherwise an error message would be displayed, for example if the client already has a package with the id '1'.
```
* As we can see now if we print that specific client the package will be added at the end of the package list.
#
```sh
:::::Please provide us with the client Name or NIF:::::
Which information suits you?  
:::::::::::::::::::::::::::::::::::
             options             
:::::::::::::::::::::::::::::::::::
1 - Name
2 - NIF
0 - Quit
Answer: 2
Whats the NIF of the client?
111987666
::::::::::
Name: Belmiro Miguel
NIF: 111987666
Family members: 2
----Address--- 
Rua: Avenida dos Grilos 
Nº porta/prédio: 100
Andar:  ‐ 
Código postal: 2300‐101 
Localidade:  Coimbra
Packages: 100;136;20;1 <- Here
```
* As the last function of managing packages is used to calculate and display the number and the total value of the sold packages, it only takes data from the vectors, there's no input needed.

#### Writing the content to a file
* At the end of the program if the user wants to quit, all the content of the vectors will be written to the file of same name. It will also create a copy of the previous file with the same name + "_copy.txt" and a copy will be made, which can be used to restore main files if any mistake has occurred.
* The problem here is if we try to use the program again, an 'out_of_range' error message is displayed, therefore I always had to restore original files to run code checks.


```sh 
                                clients.txt
Rui Manuel
234987156
4
Rua Sem Fim  / 200 /  5Esq  / 1200‐001  /  Lisboa
::::::::::
Belmiro Miguel
111987666
2
Avenida dos Grilos  / 100 /  ‐  / 2300‐101  /  Coimbra
::::::::::
User test
2122232425
4
Rua qualquer / 94 / 1ºDireita / 4000-220 /  Paranhos
```
* This is the main file of the packages created at the end of the program 'packs.txt'. For some reason in this case my negative id is not read and it became the id 0.
```sh 
                                packs.txt
4
1
Madeira – Funchal, Porto Santo
2019/08/01
2019/08/05
300
30
11
::::::::::
0
Veneza
2019/03/02
2019/03/05
300
24
24
::::::::::
3
Douro vinhateiro ‐ Porto, Régua, Pinhão, Vila Real
2019/09/21
2019/09/22
100
62
12
::::::::::
4
Bahia - Salvador, Camaçari, Arembepe
2020/06/05
2020/09/20
1200
30
0
```
# END
This was a short summary of how the program is working so far, all 8 topics of the features were implemented. improvements will be made in Project 2.

# Project-2
