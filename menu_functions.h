#ifndef MENU_FUNCTIONS_H_INCLUDED
#define MENU_FUNCTIONS_H_INCLUDED

#include "vraboten.h"

using namespace std;

bool wageComparator(Vraboten &first, Vraboten &second);

void initMenu();

void addVraboten();
void findVraboten();
void printVraboten(Vraboten &);
void printVraboteniList();

#endif // MENU_FUNCTIONS_H_INCLUDED
