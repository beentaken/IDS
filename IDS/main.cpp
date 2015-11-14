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

// trim newline character from beginning of event names
static inline string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

void distFunc(double mean, double stdDev){
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean,stdDev); //take this number use it to generate however many emails this number invokes -
    cout << "results: " << endl;
    double genMean=0;
    int loop=1000;
    for(int i=0;i<loop;++i){
        double gen=distribution(generator);
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
    
    cout << "------Events data------" << endl;
    for (std::vector<Stats>::const_iterator i = ss.begin(); i != ss.end(); ++i){
        i->printEvents();
    }

    cout << "\n-------Stats Data-------" << endl;
    for (std::vector<Stats>::const_iterator i = ss.begin(); i != ss.end(); ++i){
        i->printStats();
    }
    cout << "------------------------" << endl;

    //OK, so far I've managed to get all the data inside the program using classes -> into vector arrays.
    //I have two classes, Events and Stats because I first read Events.txt data into Events class (type, min, max, unit, weight)
    //and I save that. And then I read in Stats data from stats.txt and then I copy what I already have from events and then merge
    //it with the stats data and store everything in the stats subclass, which inherits from the events superclass
    //(not sure why I need super/subclasses but I used the examples I had from older assignments and that was that.
    
    

    return 0;
    
}

