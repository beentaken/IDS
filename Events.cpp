#include "Events.h"

Events::Events(){
    name="";
    type="";
    min="0";
    max="0";
    unit="";
    weight="0";
}

Events::Events(string name, string type, string min, string max, string unit, string weight)
{
    this -> name = name;
    this -> type = type;
    this -> min = min;
    this -> max = max;
    this -> unit = unit;
    this -> weight = weight;
}

Events::~Events(){}

string Events::getName() const{return this->name;}
string Events::getType() const{return this->type;}
string Events::getMin() const{return this->min;}
string Events::getMax() const{return this->max;}
string Events::getUnit() const{return this->unit;}
string Events::getWeight() const{return this->weight;}
void Events::setName(string name){this->name = name;}
void Events::setType(string type){this->type = type;}
void Events::setMin(string min){this->min = min;}
void Events::setMax(string max){this->max = max;}
void Events::setUnit(string unit){this->unit = unit;}
void Events::setWeight(string weight){this->weight = weight;}

void Events::printEvents() const{
    cout << "Name: " << this->name << endl;
    cout << "Type: " << this->type << endl;
    cout << "Min: " << this->min << endl;
    cout << "Max: " << this->max << endl;
    cout << "Unit: " << this->unit << endl;
    cout << "Weight: " << this->weight << endl;
    
}

