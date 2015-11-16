//
//  main.cpp
//  IDS
//
//  Created by Admin on 11/10/15.
//  Copyright © 2015 Personal. All rights reserved.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include "Events.h"
#include "Stats.h"

using namespace std;

vector<Events> ee;
vector<Stats> ss;
vector<Stats> randEvents; //stores the randomly generated events.
static int tempHr=510; //510MINS is 0830HRS from 0000HRS

// trim newline character from beginning of event names
static inline string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

void transformTime(int x, int& hours, int& mins) //turns minutes into hours and minutes
{
    hours=x/60;
    mins=x%60;
}

int timeIncrement(double mean=12, double stdDev=7)
{
    int increment;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean,stdDev);
    increment=int(distribution(generator));
    return increment;
}

void distFuncC(double mean, double stdDev, int loop, string name){
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean,stdDev); //take this number use it to generate however many emails this number invokes -
    //cout << "results: " << endl;
    double genMean=0;
    for(int i=0;i<loop;i++){
        //++tempHr;
        double gen=distribution(generator);
        gen = (round(gen*100)) / 100.0; //rounds random value to 0.00
        Stats r(tempHr, name, "C", gen); //no floor, we want 2 decimal places
        randEvents.push_back(r);
        genMean=gen+genMean;
        cout << gen << endl;
    }
    cout << "mean is: " << genMean/loop << endl;
}

void distFuncD(int loop, string name){
    
    for(int i=0;i<loop;i++){
        //++tempHr;
        Stats r(tempHr, name, "D", 1); //floor esentially takes floor of double value eg. 10.12 and turns it into 10 to cut off the decimal place trails
        randEvents.push_back(r);
    }
}

void distFuncE(double mean, double stdDev, int loop, string name){
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean,stdDev); //take this number use it to generate however many emails this number invokes -
    //cout << "results: " << endl;
    double genMean=0;
    for(int i=0;i<loop;i++){
        //++tempHr;
        double gen=distribution(generator);
        Stats r(tempHr, name, "E", floor(gen)); //floor esentially takes floor of double value eg. 10.12 and turns it into 10 to cut off the decimal place trails
        randEvents.push_back(r);
        genMean=gen+genMean;
        cout << gen << endl;
    }
    cout << "mean is: " << genMean/loop << endl;
}

void readInEventsData(){
    Events e;
    string t, numOfEvents;
    ifstream infile("Events.txt");
    getline(infile, numOfEvents);
    for (int i=0;i<stoi(numOfEvents);i++) //while(infile) loops the first line too.
    {
        infile >> e;
        //e.print();
        ee.push_back(e);
    }
}

/*This function will allow what we've read from the events file
(type,min,max,unit,weight) to be stored in stats as well as reading in
the (mean,std dev) data from the stats file and
having it all together in the Stats data class which inherits from the Events superclass*/
void readInStatsData(){
    
    string t, numOfEvents;
    ifstream infile("Stats.txt");
    getline(infile, numOfEvents);
    for (int i=0;i<stoi(numOfEvents);i++)
    {
        string name,mean,stdDev;
        getline(infile, name, ':');
        getline(infile, mean, ':');
        getline(infile, stdDev, ':');
        Stats s (ltrim(name), ee[i].getType(),ee[i].getMin(),ee[i].getMax(),ee[i].getUnit(),ee[i].getWeight(),mean, stdDev);
        
        ss.push_back(s);
    }
    ee.clear(); //clear event vector to free memory since all data is consolidated in Stats vector
}

int main() {
    
   
    /*cout << "Menu:\n";
    cout << "1. Activity Engine (Events output)\n";
    cout << "2. Analysis Engine (Stats output)\n";
    cout << "3. Alert Engine (Anomaly report)\n";*/

    //distFunc(5.0,2.0);
    
    readInEventsData();
    readInStatsData();
    
    cout << "------Events settings------" << endl;
    for (std::vector<Stats>::const_iterator i = ss.begin(); i != ss.end(); ++i){
        i->printEvents();
    }

    //this will iterate through the stats vector which has the class object object for stats, as well as the data for events since we
    //copied it into stats from events earlier during the read in loop. but we don't output the events data here, only in the iterator above.
    cout << "-------Stats settings-------" << endl;
    for (std::vector<Stats>::const_iterator i = ss.begin(); i != ss.end(); ++i){
        i->printStats();
    }
    //OK, so far I've managed to get all the data inside the program using classes -> into vector arrays.
    //I have two classes, Events and Stats because I first read Events.txt data into Events class (type, min, max, unit, weight)
    //and I save that. And then I read in Stats data from stats.txt and then I copy what I already have from events and then merge
    //it with the stats data and store everything in the stats subclass, which inherits from the events superclass
    //(not sure why I need super/subclasses but I used the examples I had from older assignments and that was that.
    
    //Now we start randomly generating events based on the events that we have.
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    for (std::vector<Stats>::const_iterator i = ss.begin(); i != ss.end(); ++i){
        if(i->getType()=="C") //C Events
        {
            normal_distribution<double> distribution(5,3); //mean=10 std deviation=3 so 7 to 13 login events each lasting about 70minutes to 130 minutes each time
            distFuncC(stod(i->getMean()), stod(i->getStdDev()), distribution(generator),i->getName());
            //loop count randomizer using the mean,stdDev settings above
            //note: we use stod (string to double) cast method here to convert strings to double so distFunc can process it.
        }
        if(i->getType()=="D") //D Events
        {
            normal_distribution<double> distribution(stod(i->getMean()),stod(i->getStdDev())); //for discrete events, we dont need to output values, only single based events based on it's mean and std deviation of its chances occuring in a day. for eg: mean=5 equals 5 email events on average a day.
            distFuncD(distribution(generator), i->getName());
            //loop count randomizer using the mean,stdDev settings above
            //note: we use stod (string to double) cast method here to convert strings to double so distFunc can process it.
        }
        if(i->getType()=="E") //E Events
        {
            normal_distribution<double> distribution(5,3); //anywhere from 2-8 E type events generated.
            distFuncE(stod(i->getMean()), stod(i->getStdDev()), distribution(generator),i->getName());
            //loop count randomizer using the mean,stdDev settings above
            //note: we use stod (string to double) cast method here to convert strings to double so distFunc can process it.
        }
        
    }
    random_shuffle(randEvents.begin(), randEvents.end()); //shuffles the vector so the events are randomized and not in sequence.
    for (int i = 0; i < randEvents.size(); i++){ //loops through the randomized vector and sets the time
        tempHr=tempHr+timeIncrement();
        int tempHrs, tempMins;
        transformTime(tempHr, tempHrs, tempMins);
        tempHrs=(tempHrs*100)+(tempMins);
        randEvents[i].setTime(tempHrs);
    }
    

    cout << "-------Generated Data-------" << endl; //outputs the randomized events in ascending order of hour
    for (std::vector<Stats>::const_iterator i = randEvents.begin(); i != randEvents.end(); ++i){
        i->printRandEvents();
    }
    
    return 0;
}

