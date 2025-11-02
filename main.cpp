#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*
Additional functions: 
check avg age of goats - accumulate()
remove old goats - find + erase, use any_of to check for more values
sell herd - clear
paint goats - fill
walk goats - for_each
sort goats - sort
shuffle herd - shuffle
find goats of certain color - find
*/
 
const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void avg_age(list<Goat> trip);
void remove_old_goats(list<Goat> &trip);
void sell_herd(list<Goat> &trip);
void paint_goats(list<Goat> &trip);
void walk_goats(list<Goat> &trip);
void sort_goats(list<Goat> &trip);
void shuffle_goats(list<Goat> &trip);
void find_color(list<Goat> &trip);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Finding average age.\n";
                avg_age(trip);
                break;
            case 5:
                cout << "Removing old goats.\n";
                remove_old_goats(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] check avg age of goats\n";
    cout << "[5] remove old goats\n";
    cout << "[6] sell herd\n";
    cout << "[7] paint goats\n";
    cout << "[8] walk goats\n";
    cout << "[9] sort goats\n";
    cout << "[10] shuffle herd\n";
    cout << "[11] find goats of certain color\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

// function uses accumulate to find total goat age and prints average
void avg_age(list<Goat> trip) {
    cout << "Entered func";
    vector<int> ages;
    for(auto goat: trip) {
        ages.push_back(goat.get_age());
    }
    int totalScore = accumulate(ages.begin(), ages.end(), 0);
    cout << "Average goat age: " << totalScore/ages.size() << endl;
}

void remove_old_goats(list<Goat> &trip) {
    while(any_of(trip.begin(), trip.end(), [](Goat& g) { return g.get_age() > 15; })) {
        auto it = find_if(trip.begin(), trip.end(), [](Goat& g){ return g.get_age() > 15; });
        if (it != trip.end())
            trip.erase(it);
    }
}
/*
void sell_herd(list<Goat> &trip);
void paint_goats(list<Goat> &trip);
void walk_goats(list<Goat> &trip);
void sort_goats(list<Goat> &trip);
void shuffle_goats(list<Goat> &trip);
void find_color(list<Goat> &trip);*/