#pragma once
#include "Agency.h"
#include "Packet.h"

int readOptions(const vector<string> &menu);
int agency_operations(Agency &agency);
void packs_operation(Agency &agency, vector<Packet> &packs);
unsigned mainMenu(Agency agency);
