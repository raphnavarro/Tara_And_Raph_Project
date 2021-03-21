
#include "Person.h"


Person::Person(){
    // Already Done! :)
    set_person();
}


Person::Person(string fname, string lname, string bdate){
    // TODO
    this->f_name = fname;
    this->l_name = lname;
    this->birthdate = new Date(bdate);
}


Person::~Person(){
  delete birthdate;
    // TODO
}


void Person::set_person(){
    //TODO
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY", but user can make mistakes
    // OOP: the one who wrote the Date class did take care of handling mistakes

	cout << "First Name: ";
  cin >> f_name;
    // TODO: read the first name
	cout << "Last Name: ";
  cin >> l_name;
    // TODO: read the last name
    cout << "Birthdate (M/D/YYYY): ";
    string s;
    cin >> s;
    birthdate = new Date(s);
    // TODO: get birthdate from user as a string and use it to create a new Date (dynamic allocation)

}


bool Person::operator==(const Person& rhs){
    // TODO
    // Hint: Look at how we overloaded == in Date
    // Two persons are equal only if they have the same first name, last name and date of birth!
    if(this->f_name == rhs.f_name){
      if(this->l_name == rhs.l_name){
        if(this->birthdate == rhs.birthdate)
          return true;
      }
    }
    return false;
}


bool Person::operator!=(const Person& rhs){
    // TODO
    // Hint: two things are either equal or not equal
    if(this->f_name == rhs.f_name){
      if(this->l_name == rhs.l_name){
        if(this->birthdate == rhs.birthdate)
          return false;
      }
    }
    return true;
}


void Person::print_person(){
    // Already done!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
}
