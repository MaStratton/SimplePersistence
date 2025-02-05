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
void searchByLnameFile();

void mongo();
void dbAddFiles();
void dbAddOne();
void dbSearch();
void dbUpdate();
void dbDelete();
bool dbCheckIfExist(string ID);

void neo4j();
void neoAddPeople();
void neoAddOne();
void neoAddRel();
void neoUpdate();
void neoFindOne();
void neoDelOne();
bool neoCheckID(string ID);

void redis();
void redisAddPeople();
void redisAddOne();
void redisSearch();
void redisUpdate();
void redisDelete();
void redisEmpty();
vector<string> redisMkVector(string person);
bool redisCheckExist(string ID);
