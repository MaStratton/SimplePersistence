#include "../inc/employee.h"
#include <fstream>

using namespace std;

string Employee::getID(){
  return to_string(ID);
}

string Employee::getfName(){
  return fName;
}

string Employee::getlName(){
  return lName;
}

string Employee::getHireYear(){
  return to_string(hireYear);
}

void Employee::setfName(string fName){
  for (int i = 0; i <= fName.length(); i++){
		this->fName[i] = fName[i];
	}
}

void Employee::setlName(string lName){
  for (int i = 0; i <= lName.length(); i++){
		this->lName[i] = lName[i];
	}
}

void Employee::setHireYear(string hireYear){
  this->hireYear = stoi(hireYear);
}

void Employee::update(string fName, string lName, string hireYear){
  setfName(fName);
  setlName(lName);
  this->hireYear = stoi(hireYear);
}

string Employee::toString(){
  return ("ID: " + to_string(ID) + "\nFirst Name: " + fName + "\nLast Name: " + lName + "\nHire Year: " + to_string(hireYear));
}