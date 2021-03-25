
#include "Date.h"

Date::Date(){
    // Already done!
    // cout << "Default constructor called! " << endl;
    day = 1;
    month = 1;
    year = 1970;
}


Date::Date(int day, int month, int year){
    // Already done!
    // cout << "Constructor with integer arguments is called!" << endl;
    set_date(day, month, year);
}


Date::Date(string str){
    // Already done!
    // input format is M/D/YYYY
    // cout << "Constructor wtih string argument is called" << endl;
    set_date(str);
}


bool Date::operator==(const Date& rhs){
    // TODO
    if(this->month == rhs.month){ //if the month is the same
      if(this->day == rhs.day){ // if the day is the same
        if(this->year == rhs.year)//if the year is the same
          return true;
      }
    }
    return false;
}


bool Date::operator!=(const Date& rhs){
    // TODO
    //same logic as the == operator, but returns false if month, day, and year are the same
    if(this->month == rhs.month){
      if(this->day == rhs.day){
        if(this->year == rhs.year)
          return false;
      }
    }
    return true;
}

bool Date::operator < (const Date& rhs){
    // TODO
    if(this->year < rhs.year) // if the year is earlier
      return true;
    else if(this->year == rhs.year){
      if(this->month < rhs.year) //if the year is the same but the month is earlier
        return true;
    }else if(this->month == rhs.month){
      if(this->day < rhs.day) //if the month and year are the same but the day is earlier
        return true;
    }
    return false;
}

bool Date::operator > (const Date& rhs){
    // TODO
    //same logic as the < operator, but using > instead
    if(this->year > rhs.year)
      return true;
    else if(this->year == rhs.year){
      if(this->month > rhs.year)
        return true;
    }else if(this->month == rhs.month){
      if(this->day > rhs.day)
        return true;
    }
    return false;
}

bool Date::check_date(int _day, int _month, int _year){
    // TODO -- you did this in Lab3
    // Leap years are those years divisible by 4, except for century years which are not divisible by 400.
    //copied from lab 3
    int y = year%4;
    int x = year%400;
    int z = year%100;

    if (_day<1 || _day > 31){
      return false;
    }
    if(_month<1 || _month>12){
      return false;
    }
    if(_month == 2 && _day > 28 && (!(y==0) || (z==0 && !(x==0)))){
      return false;
    }
    else if(_month == 2 && _day > 29 && y==0){
      return false;
    }

    if((_month == 4 || _month == 6 || _month == 9 || _month == 11) && _day>30){
      return false;
    }

    if(_year<0){
      return false;
    }

    return true;
}

bool Date::set_date(string str){
    // TODO
    // input format should be M/D/YYYY

    // You may use these prompts
    // cout << "Error! Invalid date!" << endl;
    // cout << "Date set to default!" << endl;
    string month = "";
    string day = "";
    string year = "";
    int index1 = str.find("/"); // the index of the first "/"

    month = str.substr(0,index1); // the month will be from the beginning of the string to index1
    index1++; //iterate over the slash since we don't want it in our day
    str = str.substr(index1,str.length()-index1); //get rid of the month and the first slash since we already inputted month. We only need to look at day and year now
    int index2 = str.find("/"); // finding the slash between day and year
    day = str.substr(0, index2); // the day will be from the beginning of the string to index2
    index2++; // iterate over the slash since we dont want it in our year
    year = str.substr(index2, str.length()); //year is the rest of the string
    return set_date(stoi(day), stoi(month), stoi(year));
}


bool Date::set_date(int day, int month, int year){
    // Already done!
    // returns a true if operation successful, or false if unsuccessful
    // understand why we used "this" statement in this method
    if (check_date(day, month, year)){
        this->day = day;
        this->month = month;
        this->year = year;
        return true;
    }
    else {
        cout << "Error! Invalid date!" << endl;
        cout << "Date set to default!" << endl;
        this->day = 1;
        this->month = 1;
        this->year = 1970;
        return false;
    }
}


void Date::print_date(string type){
    // TODO
    // Different types for print, are:
    // "M/D/YYYY"
    // "Month D, YYYY"
    // "D-Month-YYYY"
    // otherwise, cout << "Wrong print type!" << endl;
    if(type=="M/D/YYYY"){
      cout << month << "/" << day << "/" << year << endl;
    }else if(type == "Month D, YYYY"){//taken from lab3
      enum monthnum{Jan = 1, Feb=2, Mar=3, Apr=4, May=5, Jun=6, Jul=7, Aug=8, Sep=9, Oct=10, Nov=11, Dec=12};
      switch(month){
        case Jan:
        cout << "January " << day << ", " << year << endl;
        break;
        case Feb:
        cout << "February " << day << ", " << year << endl;
        break;
        case Mar:
        cout << "March " << day << ", " << year << endl;
        break;
        case Apr:
        cout << "April " << day << ", " << year << endl;
        break;
        case May:
        cout << "May " << day << ", " << year << endl;
        break;
        case Jun:
        cout << "June " << day << ", " << year << endl;
        break;
        case Jul:
        cout << "July " << day << ", " << year << endl;
        break;
        case Aug:
        cout << "August " << day << ", " << year << endl;
        break;
        case Sep:
        cout << "September " << day << ", " << year << endl;
        break;
        case Oct:
        cout << "October " << day << ", " << year << endl;
        break;
        case Nov:
        cout << "November " << day << ", " << year << endl;
        break;
        case Dec:
        cout << "December " << day << ", " << year << endl;
        break;
      }
    }else if(type == "D-Month-YYYY"){
      cout << day << "-" << month << "-" << year << endl;
    }else{
      cout << "Wrong print type!" << endl;
    }
}

string Date::get_date(){
    // Already done!
    ostringstream ss;
    ss << month << "/" << day << "/" << year;
    string str = ss.str();
    return str;
}
