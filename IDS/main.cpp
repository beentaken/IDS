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

void distFunc(double mean, double stdDev){
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean,stdDev);
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
        Stats s (name, ee[i].getType(),ee[i].getMin(),ee[i].getMax(),ee[i].getUnit(),ee[i].getWeight(),mean, stdDev);
        
        ss.push_back(s);
    }
}

int main() {
    
    /*cout << "Menu:\n";
    cout << "1. Activity Engine (Events output)\n";
    cout << "2. Analysis Engine (Stats output)\n";
    cout << "3. Alert Engine (Anomaly report)\n";*/

    //distFunc(5.0,2.0);
    
    readInEventsData();
    readInStatsData();
    
    
    ss.front().printAll();
    
    return 0;
    
}

