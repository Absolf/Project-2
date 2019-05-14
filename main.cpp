#include "Menus.h"
#include "Agency.h"
#include "defs.h"
int main()
{
  vector<string> agency_file = agencyData(AGENCY_FILE_NAME);
  Agency agency(agency_file); // create the agency
  mainMenu(agency); // initial menu inicial with the major options of the application

  return 0;
}