#include "../inc/employee.h"
#include <fstream>

using namespace std;

string Employee::getID(){
  return ID;
}

string Employee::getfName(){
  return fName;
}

string Employee::getlName(){
  return lName;
}

string Employee::getHireYear(){
  return hireYear;
}

void Employee::setfName(string fName){
  this->fName = fName;
}

void Employee::setlName(string lName){
  this->lName = lName;
}

void Employee::setHireYear(string hireYear){
  this->hireYear = hireYear;
}

void Employee::update(string fName, string lName, string hireYear){
  this->fName = fName;
  this-> lName = lName;
  this->hireYear = hireYear;
}

string Employee::toString(){
  return ("ID: " + ID+ "\nFirst Name: " + fName + "\nLast Name: " + lName + "\nHire Year: " + hireYear);
}