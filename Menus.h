#ifndef __MENUS_H_INCLUDED__
#define __MENUS_H_INCLUDED__

#include "Agency.h"
#include "Packet.h"
#include "Client.h"
#include "Address.h"
#include "Date.h"
#include "utils.h"

int agency_operations(Agency &agency); // Presents the agency
void packs_operation(Agency &agency, vector<Packet> &packs, vector<Client> &clients); // for the packets management
void clients_operations(Agency &agency, vector<Client> &clients); // for the client management
void makeCopy(string filename);
void mainMenu(Agency agency); // for the proper usage of the agency options and management the other management functions

#endif