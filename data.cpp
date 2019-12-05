//
// Created by Eva Wu on 12/4/19.
//


#include <string>
#include <iostream>
#include "data.h"

using namespace std;

//default constructor
data::data() {
    Date = "";
    Minute=0;
    BidOpen=0.0;
    BidHigh=0.0;
    BidLow=0.0;
    BidClose=0.0;
}
//alternate constructor
data::data(string d,int min,double open,double high,double low,double close) {
    Date = d;
    Minute = min;
    BidOpen = open;
    BidHigh = high;
    BidLow = low;
    BidClose = close;
}

}

//overloads the outstream operator
ostream& operator<<(ostream& os, const data& ptr) {
    os << ptr.Date << ": " << ptr.Minute << ", " << ptr.BidOpen << "," << ptr.BidHigh << "," << ptr.BidLow << "," << ptr.BidClose;
    return os;
}

//overloads <,>,= operator
bool data::operator<(data &hr) {
    if(this->BidClose < hr.BidClose){
        return true;}
    else{
        return false;
    }
}
bool data::operator>(data &hr) {
    if(this->BidClose>hr.BidClose){
        return true;
    }else{
        return false;
    }
}
bool data::operator >=(data &hr){
    if(this->BidClose>=hr.BidClose){
        return true;
    }else{
        return false;
    }
};
