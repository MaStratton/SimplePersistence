#pragma once
#include "employee.h"
#include "local.h"
#include "mongo.h"
#include "neo.h"
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>


using namespace std;



void getInfo(vector<string>& data);

string capitalize(string input);
string mkString(const vector<string>& data);
string mkData(const vector<string>& data);
string getID(string output);


map<string, Employee>& getMap();


bool isNum(string input);






