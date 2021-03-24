
#include "Network.h"
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <limits>

Network::Network(){
    // TODO
    // What should be the initial values for head, tail, and count?
    head = NULL;
    tail = NULL;
    count = 0;

}


void Network::push_front(Person* newEntry){
    // TODO
    // Adds a new entry to the front of the LL (where head is pointing)
    newEntry -> next = head;
    newEntry -> prev = NULL;
    if(head != NULL){
      head -> prev = newEntry;
    }
    else{
      tail = newEntry;
    }
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // TODO
    // Adds a new entry to the back of the LL (where tail is pointing)
    newEntry -> next = NULL;
    newEntry -> prev = tail;
    if(tail != NULL){
      tail -> next = newEntry;
    }
    else{
      head = newEntry;
    }
    tail = newEntry;
    count++;
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
    Person* ptr;
    ptr = head;
    while(ptr != NULL){
      ptr = head -> next;
      delete head;
      head = ptr;
      count--;
    }
    delete head;
    delete tail;
}


Person* Network::search(Person* searchEntry){
    // TODO
    // Searches the Network to find an entry which has similar attributes as searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Hint: We already implemented the == operator for two Person objects
    // Note: searchEntry is not a Person, but a Person*
    Person* searchPtr = head;
    if(head != NULL){
      while(searchPtr != NULL){
        if((searchPtr -> f_name == searchEntry -> f_name) && (searchPtr -> l_name == searchEntry -> l_name)){
          return searchPtr;
        }
        searchPtr = searchPtr -> next;
      }
    }
    return NULL;
}


Person* Network::search(string fname, string lname, string bd){
    // TODO
    // Search based on fname, lname, and birthdate
    // if found, returns a pointer to it, else returns NULL
    // Note: two ways to implement this:
    // 1st) making a new Person with fname, lname, bdate and and using search(Person*)
    // 2nd) using fname, lname, and bd directly
    Person a(fname,lname,bd);
    Person* x = &a;
    return search(x);
}



void Network::saveDB(string filename){
    // TODO
    // Saves the netwrok in file <filename>
    // Look at studentDB.db as a template of the format of our database files
    ofstream outFile(filename);
    Person* ptr = head;
    while(ptr != NULL){
        outFile << ptr->l_name <<", " << ptr->f_name << endl;
        outFile << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::loadDB(string filename){
    // TODO
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.db as a template
    // When a new database is being loaded, you need to delete the previous dataset
    Person* ptr = NULL;
    Person* newPerson;
    ptr = head;
    while(ptr != NULL){
      head = ptr;
      delete head;
      ptr = ptr -> next;
    }
    head = NULL;
    tail = NULL;
    count = 0;
    string fname, lname, bdate, sectionBreak, firstLine;
    ifstream inFile(filename);
    if(inFile.is_open()){
      while(getline(inFile, firstLine)){  //Gets contents of first line
        fname = firstLine.substr(firstLine.find(',')+2);
        lname = firstLine.substr(0,firstLine.find(','));
      }
      getline(inFile,bdate);
      getline(inFile,sectionBreak);
      newPerson = new Person(fname,lname,bdate);
      this -> push_back(newPerson);
    }
    inFile.close();
}


Network::Network(string fileName){
    // TODO
    // Hint: just call loadDB
    loadDB(fileName);
}


bool Network::remove(string fname, string lname, string bd){
    // TODO
    // remove the entry with matching fname, lname, bd
    // If it exists, returns true, otherwise, returns false

    Person* x = search(fname,lname,bd);
    if(x!=NULL){
      if (x->next == NULL){
        free(x);
      }else{
        Person* temp = x->next;
        x->f_name = temp->f_name;
        x->l_name = temp->l_name;
        x->birthdate = temp->birthdate;
        x->next = temp->next;
        free(temp);
      }
      return true;
    }
    return false;
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
            cin >> fname >> lname >> bdate;
            Person per(fname, lname, bdate);
            Person* pers = &per;
            if(search(pers)){
              cout << "Entity already exists\n";
            }else{
              push_front(pers);
            }

            // If it already exists:
            // cout << "Entity already exists\n"; -- not required in 2021
        }
        else if (opt == 4){
            // TODO
            cout << "Removing an item \n";
            cout << "First name: ";
            cin >> fname;
            cout << "Last name: ";
            cin >> lname;
            cout << "Birthdate: ";
            cin >> bdate;
            if(remove(fname, lname, bdate)){
              cout << "Remove Successful! \n";
            }else{
              cout << "Person not found! \n";
            }
            // If found and removed successfully: cout << "Remove Successful! \n";
            // else: cout << "Person not found! \n";
        }
        else if (opt==5){
            // TODO
            cout << "Searching: \n";
            cout << "First Name: ";
            cin >> fname;
            cout << "Last Name: ";
            cin >> lname;
            cout << "Birthdate: ";
            cin >> bdate;
            if(search(fname, lname, bdate)!=NULL){
              cout << search(fname, lname, bdate);
            }else{
              cout << "Not found! \n";
            }
            // If not found: cout << "Not found! \n";
            // If found: print person
        }

        else if (opt==6){
            // TODO
            cout << "Network Database: \n";
            // this should be simple ...
            printDB();
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
