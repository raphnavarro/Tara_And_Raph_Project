
#include "Network.h"
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <limits>

Network::Network(){
    // TODO
    // What should be the initial values for head, tail, and count? 
}


void Network::push_front(Person* newEntry){
    // TODO
    // Adds a new entry to the front of the LL (where head is pointing)
}


void Network::push_back(Person* newEntry){
    // TODO
    // Adds a new entry to the back of the LL (where tail is pointing)
}


void Network::printDB(){
    // Already done! 
    cout << "Number of items: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

Network::~Network(){
    // TODO 
    // Delete all the dynamically allocated items
}


Person* Network::search(Person* searchEntry){
    // TODO
    // Searches the Network to find an entry which has similar attributes as searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Hint: We already implemented the == operator for two Person objects
    // Note: searchEntry is not a Person, but a Person* 
}


Person* Network::search(string fname, string lname, string bd){
    // TODO
    // Search based on fname, lname, and birthdate
    // if found, returns a pointer to it, else returns NULL
    // Note: two ways to implement this:
    // 1st) making a new Person with fname, lname, bdate and and using search(Person*)
    // 2nd) using fname, lname, and bd directly 
}



void Network::saveDB(string filename){
    // TODO
    // Saves the netwrok in file <filename>
    // Look at studentDB.db as a template of the format of our database files
}


void Network::loadDB(string filename){
    // TODO
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.db as a template
    // When a new database is being loaded, you need to delete the previous dataset
}


Network::Network(string fileName){
    // TODO
    // Hint: just call loadDB 
}


bool Network::remove(string fname, string lname, string bd){
    // TODO
    // remove the entry with matching fname, lname, bd
    // If it exists, returns true, otherwise, returns false
}



void Network::showMenu(){
    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner");
        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Search \n";
        cout << "6. Print database \n";
        cout << "0. Quit \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! Quitting ... " << endl;
            return;
        }

        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){ 
            // Already done! 
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            this->saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){ 
            // Already done! 
            cout << "Loading network database \n";
            // Note: we added a nice feature to show the files in current directory
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir ("./")) != NULL) {
                string str;
                while ((ent = readdir (dir)) != NULL) {
                    str = ent->d_name;
                    if (str.size() > 3){
                        if (str.substr(str.size()-3) == ".db")
                            cout << str << endl; 
                    }
                }
                closedir (dir);
            }
            cout << "Enter the name of the load file: ";
            cin >> fileName;
            ifstream check(fileName.c_str());
            if (! bool(check))
                cout << "Warning! File does not exist! \n";
            else {
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " items \n";
            }
        }
        else if (opt == 3){
            // TODO
            // Prompt and get the information of a new Person
            // You need to make sure this item does not already exists!
            // If it does not exist, push it to the front of the LL
            cout << "Adding a new item (push front)\n";

            // If it already exists: 
            // cout << "Entity already exists\n"; -- not required in 2021
        }
        else if (opt == 4){
            // TODO 
            cout << "Removing an item \n";
            cout << "First name: ";
            cout << "Last name: ";
            cout << "Birthdate: ";
            // If found and removed successfully: cout << "Remove Successful! \n";
            // else: cout << "Person not found! \n";
        }
        else if (opt==5){
            // TODO
            cout << "Searching: \n";
            cout << "First Name: ";
            cout << "Last Name: ";
            cout << "Birthdate: ";
            // If not found: cout << "Not found! \n";
            // If found: print person
        }

        else if (opt==6){
            // TODO 
            cout << "Network Database: \n";
            // this should be simple ... 
        }

        else if (opt==0)
            // QUIT! 
            return;
        else
            cout << "Nothing matched!\n";
       
        // Don't touch the lines below! :)  
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear();
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}



