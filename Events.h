#ifndef Events_h
#define Events_h

#include <iostream>
using namespace std;

//this class stores the baseline events from the files
class Events
{
protected:
    string name;
    string type;
    string min;
    string max;
    string unit;
    string weight;
public:
    //constructors and destructors
    Events();
    Events(string,string,string,string,string,string);
    ~Events();
    
    //assessors and mutator functions
    void setName(string);
    void setType(string);
    void setMin(string);
    void setMax(string);
    void setUnit(string);
    void setWeight(string);
    
    void printEvents() const;
    string getName() const;
    string getType() const;
    string getMin() const;
    string getMax() const;
    string getUnit() const;
    string getWeight() const;

    virtual istream& read(istream &is){
        getline(is, name, ':');
        getline(is, type, ':');
        getline(is, min, ':');
        getline(is, max, ':');
        getline(is, unit, ':');
        getline(is, weight, ':');
        return is;
    }
    friend istream& operator>> (istream& is, Events& e){
        return e.read(is);
    }
    
    
    
};

#endif /* Events_h */
