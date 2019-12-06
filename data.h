//
// Created by Eva Wu on 12/4/19.
//

#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H
#include <string>
#include <iostream>

using namespace std;

class data {
public:

    data ();
    data(string Date,int Minute,double BidOpen,double BidHigh,double BidLow,double BidClose);
    friend ostream& operator<<(ostream& os, const data& pr);
    friend bool operator >= (const data& hr, const data &d);
    friend bool operator <= (const data& hr, const data &d);
    friend bool operator > (const data& hr, const data &d);
    data& operator = (const data &d);


    string Date;
    int Minute;
    double BidOpen;
    double BidHigh;
    double BidLow;
    double BidClose;
};


#endif //PROJECT9_DATA_H
