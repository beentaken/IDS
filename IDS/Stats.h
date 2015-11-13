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
    string mean;
    string stdDev;
public:
    
    Stats(){name="null";mean="";stdDev="";};
    Stats(string name,string type,string min,string max,string unit, string weight,string mean, string stdDev){
        this->name=name;
        this -> type = type;
        this -> min = min;
        this -> max = max;
        this -> unit = unit;
        this -> weight = weight;
        this->mean=mean;
        this->stdDev=stdDev;}
    
    ~Stats(){};
    
    void print() const{cout<<"mean: "<<this->mean<<"\nStandard Deviation: "<<stdDev<<endl;}
    
    
    void printAll() const{
        cout << "Name: " << this->name << endl;
        cout << "Type: " << this->type << endl;
        cout << "Min: " << this->min << endl;
        cout << "Max: " << this->max << endl;
        cout << "Unit: " << this->unit << endl;
        cout << "Weight: " << this->weight << endl;
        cout << "Mean: " << this->mean << endl;
        cout << "Std Dev: " << this->stdDev << endl;

    }
    
    void setMean(string mean){this->mean=mean;}
    void setStdDev(string stdDev){this->stdDev=stdDev;}
    
    string getName() const{return this->name;}
    string getType() const{return this->type;}
    string getMin() const{return this->min;}
    string getMax() const{return this->max;}
    string getUnit() const{return this->unit;}
    string getWeight() const{return this->weight;}
};

#endif /* Stats_h */
