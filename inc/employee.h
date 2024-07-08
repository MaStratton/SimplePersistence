#pragma once
#include "../inc/main.h"
#include <string>

class Employee{
  private:
    string ID;
    string fName;
    string lName;
    string hireYear;

  public:
    Employee() = default;

    Employee(string ID, string fName, string lName, string hireYear){
      this->ID = ID;
      this->fName = fName;
      this-> lName = lName;
      this->hireYear = hireYear;
    }



    string getID();
    string getfName();
    string getlName();
    string getHireYear();

    void setfName(string fName);
    void setlName(string lName);
    void setHireYear(string hireYear);

    void update(string fName, string lName, string hireYear);

    string toString();
};

