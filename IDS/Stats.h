//
//  Stats.h
//  IDS
//
//  Created by Admin on 11/12/15.
//  Copyright © 2015 Personal. All rights reserved.
//

#ifndef Stats_h
#define Stats_h

#include "Events.h"


class Stats:public Events{
protected:
    string mean; //we will have mean and stdDev as string datatypes as it is easier to read in from the file that way
    string stdDev; //we can cast string to int or double later on when we need it.
    double value;
    int hour;
public:
    
    Stats(){name="";mean="";stdDev="";};
    Stats(string name,string type,string min,string max,string unit, string weight,string mean, string stdDev){
        this->name=name;
        this -> type = type;
        this -> min = min;
        this -> max = max;
        this -> unit = unit;
        this -> weight = weight;
        this->mean=mean;
        this->stdDev=stdDev;
        this->value=0.0;
        this->hour=0;
    }
    Stats(int hour, string name, string type, double value ){ //this will be the constructor for our randomly generated events
        this->hour=hour;
        this->name=name;
        this->type=type;
        this->value=value;
        this -> min = "";
        this -> max = "";
        this -> unit = "";
        this -> weight = "";
        this->mean="";
        this->stdDev="";
    }
    
    ~Stats(){};
    
    void print() const{cout<<"mean: "<<this->mean<<"\nStandard Deviation: "<<stdDev<<endl;}
    
    
    void printStats() const{
        cout << "Name: " << this->name << endl;
        cout << "Mean: " << this->mean << endl;
        cout << "Std Dev: " << this->stdDev << endl <<endl;
    }
    
    void setMean(string mean){this->mean=mean;}
    void setStdDev(string stdDev){this->stdDev=stdDev;}
    void setValue(double value){this->value=value;}
    void setTime(int hour){this->hour=hour;}
    
    string getName() const{return this->name;}
    string getType() const{return this->type;}
    string getMin() const{return this->min;}
    string getMax() const{return this->max;}
    string getUnit() const{return this->unit;}
    string getWeight() const{return this->weight;}
};

#endif /* Stats_h */
