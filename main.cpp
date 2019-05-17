#include "Menus.h"
#include "defs.h"

int main()
{
  Agency myAgency(AGENCY_FILE_NAME); // create the agency
  mainMenu(myAgency);                // initial menu with the major options of the application
  return 0;
}
