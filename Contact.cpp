
#include "Contact.h"
#include <algorithm>


Email::Email(string type, string email_addr){
    // Already done
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // Already done!
    // We don't need to validate the entered email address.
	cout << "Enter the type of email address: ";
	cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}


string Email::get_contact(){
    // TODO
    // return example: "(Personal) username@gmail.com"
    set_contact();
    string str = "(" + type + ") " + email_addr;
    return str;
}


void Email::print(){
    // TODO
    // Hint: use get_contact
    string str = get_contact();
    cout << str << endl;
}


Phone::Phone(string type, string num){
    // TODO
    // It is possible that the phone number is given with (292-431-9876) or without (2924319876) dashes.
    // We are sure that all phone numbers have 10 digits.
    this->type = type;
    this->num = num;
}


void Phone::set_contact(){
    // TODO

    // Use these prompts:
    cout <<"Enter the type of phone number: ";
    cin >> type;
    cout << "Enter the phone number: ";
    cin >> num;
    //
}


string Phone::get_contact(){
    // TODO
    // return example "(Cell) 213-876-0023"
    set_contact();
    if(num.length()==10){
      num.insert(3,"-");
      num.insert(7,"-");
    }
    string str = "(" + type + ") " + num;
    return str;
}


void Phone::print(){
    // TODO
    // Hint: use get_contact
    string str = get_contact();
    cout << str << endl;
}
