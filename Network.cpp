
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
    count = 0; //no one in the db

}


void Network::push_front(Person* newEntry){
    // TODO
    // Adds a new entry to the front of the LL (where head is pointing)
    newEntry -> next = head;
    newEntry -> prev = NULL; //nothing before head
    if(head != NULL){ //if there is already other entries
      head -> prev = newEntry;
    }
    else{
      tail = newEntry;
    }
    head = newEntry;
    count++; //increment for new person
}


void Network::push_back(Person* newEntry){
    // TODO
    // Adds a new entry to the back of the LL (where tail is pointing)
    newEntry -> next = NULL; //nothing after tail
    newEntry -> prev = tail;
    if(tail != NULL){ //if there is already other entries
      tail -> next = newEntry;
    }
    else{
      head = newEntry;
    }
    tail = newEntry;
    count++; //increment for new person
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
    while(ptr != NULL){ //go through and delete all entries
      ptr = head -> next; //the node after head
      delete head; //delete current head
      head = ptr; //make ptr the new head
      count--; //decrement
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
    if(head != NULL){ //make sure there are people in the network
      while(searchPtr != NULL){//as long as we havent reached the end of the list
        if(searchPtr -> f_name == searchEntry -> f_name){
          if(searchPtr -> l_name == searchEntry -> l_name){
            if(searchPtr -> birthdate -> get_date() == searchEntry -> birthdate -> get_date()){
              return searchPtr; //return searchPtr if first name, last name, and birthdate are the same
            }
          }
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
    Person a(fname,lname,bd); //create a new person
    Person* x = &a; //create a pointer to point to that person
    return search(x); //call other search function
}



void Network::saveDB(string filename){
    // TODO
    // Saves the netwrok in file <filename>
    // Look at studentDB.db as a template of the format of our database files
    ofstream outFile(filename);
    Person* ptr = head; //start at head
    while(ptr != NULL){ //as long as we havent reached the end, keep outputting
        outFile << ptr->l_name <<", " << ptr->f_name << endl;
        outFile << ptr -> birthdate -> get_date() << endl;
        outFile << "------------------------------" << endl;
        ptr = ptr->next; // go to next entry
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
    while(ptr != NULL){ //delete old database
      head = ptr;
      delete head;
      ptr = ptr -> next;
    }
    head = NULL;
    tail = NULL;
    count = 0;
    int index = 0;
    string fname, lname, bdate, sectionBreak, firstLine;
    ifstream inFile(filename);
    while(getline(inFile, firstLine)){ //take in the name (last, first)
      index = firstLine.find(","); //find comma
      fname = firstLine.substr(index+2); //first name starts after the comma and space and goes to the end of the string
      lname = firstLine.substr(0,index); // last name goes from the beginning to the comma
      getline(inFile,bdate);
      getline(inFile,sectionBreak);
      newPerson = new Person(fname,lname,bdate);
      this -> push_back(newPerson); //add person to end of database
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

    Person* x = search(fname,lname,bd); //make sure person exists
    if(x!=NULL){
      if (x->next == NULL){//if it is the tail
        free(x); //delete

      }else{
        Person* temp = x->next; //make temp point to the next entry
        x->next = temp->next->next;
        x = temp;
        free(temp); //delete
      }
      count--; //decrement
      return true;
    }
    return false; //return false if person doesnt exist
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
            // cout << "Adding a new item (push front)\n";
            // cout << "Input first name: ";
            // cin >> fname;
            // cout << "Input last name: ";
            // cin >> lname;
            // cout << "Input birthdate: ";
            // cin >> bdate;
            // Person per(fname, lname, bdate);
            // Person* pers = &per;
            Person* newItem = new Person(); //make a new person
            string lname, fname, bdate;
            //take in attributes
            lname = newItem -> l_name;
            fname = newItem -> f_name;
            bdate = newItem -> birthdate -> get_date();
            if(search(lname,fname,bdate) != NULL){ //make sure not getting a repeat
              cout << "Entity already exists\n";
            }else{
              push_front(newItem);
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
            if(remove(fname, lname, bdate)){ //call remove function, if true then output success
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
            if(search(fname, lname, bdate)!=NULL){ //if person found, print the person
              search(fname,lname,bdate) -> print_person();
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
