#pragma once
#include "main.h"

#include <fstream>
#include <iostream>

using namespace std;

class Employee{
  private:
    int ID;
    char fName[32];
    char lName[32];
    int hireYear;

  public:
    Employee() = default;

    Employee(string ID, string fName, string lName, string hireYear){
      this->ID = stoi(ID);
      setfName(fName);
      setlName(lName);
      this->hireYear = stoi(hireYear);

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

    void serialize(){
      string fileName = "./people/longSerialized/" + getID() + ".bin";
      ofstream file(fileName, ios::binary);
      if (file.is_open()){
        file.write(reinterpret_cast<const char*>(this), sizeof(*this));
        file.close();
      }
    }

    static Employee deserialize(string id){
      string fileName = "./people/longSerialized/" + id + ".bin";
      ifstream fin(fileName, ios::binary);
      if (!fin.is_open()) {
        std::cout << "ERROR" << std::endl;
        Employee e;
        return e;
      }
      Employee temp;
      fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
      fin.close();
      std::cout << temp.getfName();
      return temp;
    }
};

