#pragma once
#include "../inc/employee.h"
#include <string>
#include <vector>
using namespace std;
void display(string dirPath);
void addFileLong();
void deleteFileByID();
void updateByID();
void searchByID();
void getInfo(vector<string>& data);
string readInfo(string fileName);
string capitalize(string input);
string mkString(const vector<string>& data);
string mkData(const vector<string>& data);
string getID(string output);

bool checkFileExistLong(string checkFile);
bool isNum(string input);

void indexDatabase();
void serializeLong();

void deserialize();

void searchIDIndexbyID();
void searchByLname();
