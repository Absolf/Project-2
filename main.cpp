
#include "Menus.cpp"
// #include "utils.h"
#include "Agency.cpp"


int main(){
  Agency agency(AGENCY_FILE_NAME);   // create the agency

  mainMenu(agency); // initial menu inicial with the major options of the application
  
  return 0;
}