#ifndef VRABOTEN_H_INCLUDED
#define VRABOTEN_H_INCLUDED

#include <iostream>

#define ID_LIMIT 100
#define NAME_LIMIT 255

using namespace std;

enum Position {
    WORKER,
    MANAGER,
    OWNER
};

class Vraboten {

private:
    char id[ID_LIMIT];
    char name[NAME_LIMIT];
    Position position;
    int hoursWorked;
    float wage;

public:
    Vraboten(char[ID_LIMIT], char[NAME_LIMIT], Position, int, float);

    bool operator ==(const Vraboten &);

    char * getID();

    char * getName();

    Position getPosition();

    int getHoursWorked();

    float getWage();

    float getCalculatedWage();

    friend ostream & operator <<(ostream &, Vraboten &);

    ~Vraboten() {
        //cout << endl << "Destroyed '" << name << '\'' << endl;
    }
};

#endif // VRABOTEN_H_INCLUDED
