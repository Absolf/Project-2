#include "Menus.cpp"
#include "Agency.cpp"
#include "Date.cpp"
// #include "utils.h"
int main()
{
  Agency agency(AGENCY_FILE_NAME); // create the agency

  mainMenu(agency); // initial menu inicial with the major options of the application

  return 0;
}