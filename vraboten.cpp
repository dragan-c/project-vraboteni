#include <string.h>
#include <iomanip>

#include "vraboten.h"

using namespace std;

Vraboten::Vraboten(char id[ID_LIMIT], char name[NAME_LIMIT], Position position, int hoursWorked, float wage) {
    strcpy(this->id, id);
    strcpy(this->name, name);
    this->position = position;
    this->hoursWorked = hoursWorked;
    this->wage = wage;
}

bool Vraboten::operator ==(const Vraboten &vraboten) {
    return strcmp(this->id, vraboten.id) == 0 || strcmp(this->name, vraboten.name) == 0;
}

char * Vraboten::getID() {
    return this->id;
}

char * Vraboten::getName() {
    return this->name;
}

Position Vraboten::getPosition() {
    return this->position;
}

int Vraboten::getHoursWorked() {
    return this->hoursWorked;
}

float Vraboten::getWage() {
    return this->wage;
}

float Vraboten::getCalculatedWage() {
    return this->hoursWorked * this->wage;
}

ostream & operator <<(ostream &out, Vraboten &vraboten) {
    cout << "------------------" << endl;
    cout << "#" << vraboten.getID() << " -> " << vraboten.getName() << endl;
    cout << " Total Wage  ->  " << '$' << setprecision(2) << fixed << vraboten.getCalculatedWage() << endl;
    cout << "------------------" << endl;
    return out;
}
