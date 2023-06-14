#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <exception>
#include <algorithm>
#include <iomanip>

#include <sstream>

#include "menu_functions.h"
#include "io_functions.h"

using namespace std;

const string DATA_PATH = "./data.dat";

vector<Vraboten> vraboteni;

bool wageComparator(Vraboten &first, Vraboten &second) {
    return first.getCalculatedWage() > second.getCalculatedWage();
}

Position getPositionFromStr(string positionStr) {
    if (positionStr == "owner") {
        return Position::OWNER;
    } else if (positionStr == "manager") {
        return Position::MANAGER;
    } else {
        return Position::WORKER;
    }
}

string getFriendlyPositionName(Position position) {
    switch (position) {
        case 2:
            return "owner";
            break;
        case 1:
            return "manager";
            break;
        case 0:
            return "worker";
            break;
    }
    return "empty";
}

void readVraboteniData() {
    ifstream in(DATA_PATH);

    if (in.fail()) {
        cout << "Failed to read vraboteni!" << endl;
        exit(1);
    }
    cout << "Vraboteni loaded and read from file!" << endl;

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        char id[ID_LIMIT];
        char name[ID_LIMIT];
        Position position;
        int hoursWorked;
        float wage;

        ss.getline(id, ID_LIMIT, ' ');
        ss.getline(name, NAME_LIMIT, ' ');
        string positionStr;
        getline(ss, positionStr, '@');
        position = getPositionFromStr(positionStr);
        ss >> hoursWorked;
        ss.ignore();
        ss >> wage;

        vraboteni.push_back(*new Vraboten(id, name, position, hoursWorked, wage));
    }

    in.close();
}

void writeVraboteniData() {
    ofstream out(DATA_PATH);

    if (out.fail()) {
        cerr << "Failed to write vraboteni!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Vraboteni sent and written to file!" << endl;

    vector<Vraboten> :: iterator itr;
    sort(vraboteni.begin(), vraboteni.end(), &wageComparator);
    for (itr = vraboteni.begin(); itr != vraboteni.end(); itr++) {
        Vraboten vraboten = (*itr);

        out << vraboten.getID()
            << ' ' << vraboten.getName()
            << ' ' << getFriendlyPositionName(vraboten.getPosition())
            << "@ " << vraboten.getHoursWorked()
            << ' ' << vraboten.getWage()
            << " $" << vraboten.getCalculatedWage() << '\n';
    }

    out.close();
}

void initMenu() {
    char option;

    do {
        system("CLS");

        cout << "Pick an option!" << endl;
        cout << "------------------" << endl;
        cout << " A  ->  add vraboten" << endl;
        cout << " B  ->  find vraboten" << endl;
        cout << " C  ->  list of vraboteni" << endl;
        cout << " D  ->  exit" << endl;
        cout << "------------------" << endl;

        cin >> option;

        switch (toupper(option)) {
            case 'A':
                addVraboten();
                system("PAUSE");
                break;
            case 'B':
                findVraboten();
                system("PAUSE");
                break;
            case 'C':
                printVraboteniList();
                system("PAUSE");
                break;
            case 'D':
                cout << "The End" << endl;
                writeVraboteniData();
                exit(EXIT_SUCCESS);
                break;
            default:
                cerr << "Invalid option!" << endl;
                system("PAUSE");
                break;
        }
        initMenu();

    } while (toupper(option) != 'D');
}

void addVraboten() {
    char id[ID_LIMIT];
    char name[NAME_LIMIT];
    Position position;
    int hoursWorked;
    float wage;

    cin.ignore();

    cout << " Enter #ID ->" << endl;
    cin.getline(id, ID_LIMIT);

    if (strlen(id) > 6) {
        system("CLS");
        cerr << "ID length can't be >6" << endl << endl;
        return;
    }

    cout << " Enter Name ->" << endl;
    cin.getline(name, NAME_LIMIT);

    cout << " Enter Position ('owner'/'manager'/'worker') ->" << endl;
    string positionStr;
    cin >> positionStr;
    position = getPositionFromStr(positionStr);

    cin.ignore();

    cout << " Enter Hours Worked ->" << endl;
    cin >> hoursWorked;

    cout << " Enter Wage ->" << endl;
    cin >> wage;

    Vraboten *vraboten = new Vraboten(id, name, position, hoursWorked, wage);

    cout << endl;
    cout << "------" << endl;
    cout << "Added!" << endl;
    cout << "------" << endl;

    printVraboten(*vraboten);

    vraboteni.push_back(*vraboten);

    delete vraboten;
}

void findVraboten() {
    char entryToFind[NAME_LIMIT];

    cin.ignore();

    cout << " Enter #ID/Name to Find ->" << endl;
    cin.getline(entryToFind, ID_LIMIT);

    vector<Vraboten> :: iterator itr;
    itr = find(vraboteni.begin(), vraboteni.end(), *new Vraboten(entryToFind, entryToFind, Position::WORKER, 0, 0));

    if (itr != vraboteni.end()) {
        printVraboten(*itr);
        cout << (*itr);
    } else {
        cerr << "Vraboten not found!" << endl << endl;
    }
}

void printVraboten(Vraboten &vraboten) {
    cout << "#" << vraboten.getID()
        << setw(8) << vraboten.getName()
        << setw(8) << getFriendlyPositionName(vraboten.getPosition())
        << setw(8) << vraboten.getHoursWorked() << 'h'
        << setw(8) << '$' << vraboten.getWage() << "/h"
        << setw(8) << '$' << setprecision(2) << fixed << vraboten.getCalculatedWage() << endl;
}

/*
void printVraboten(Vraboten &vraboten) {
    cout << endl;
    cout << "Info" << endl;
    cout << "------------------" << endl;
    cout << " ID  ->  #" << vraboten.getID() << endl;
    cout << " Name  ->  " << vraboten.getName() << endl;
    cout << " Position  ->  " << getFriendlyPositionName(vraboten.getPosition()) << endl;
    cout << " Hours Worked  ->  " << vraboten.getHoursWorked() << endl;
    cout << " Hourly Wage  ->  " << vraboten.getWage() << endl;
    cout << "------------------" << endl;
    cout << vraboten;
}
*/

void printVraboteniList() {
    vector<Vraboten> :: iterator itr;

    sort(vraboteni.begin(), vraboteni.end(), &wageComparator);

    if (vraboteni.empty()) {
        cout << "Empty list!" << endl << endl;
    }

    for (itr = vraboteni.begin(); itr != vraboteni.end(); itr++) {
        //cout << (*itr) << endl;
        printVraboten(*itr);
    }
}
