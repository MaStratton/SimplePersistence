#include "../inc/main.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;


string dirPathShort = "./people/simple/";
string dirPathLong = "./people/long/";


string menu = "1) Display \n2) Add File\n3) Delete File by ID\n4) Update by ID\n5) Search by ID\n0) EXIT"; 


vector<string> info;

int main(void) {
  int cmd = -1;
  while (cmd != 0){
    cout << "select Command" << endl;
    cout << menu << endl;
    cin >> cmd;

    switch (cmd){
      case 1:
        display(dirPathLong);
        break;
      case 2:
        addFileLong();
        break;
      case 3:
        deleteFileByID();
        break;
      case 4:
        updateByID();
        break;
      case 5:
        searchByID();
      default:
        break;
    }
  }
}

void display(string dirPath) {
  for (auto& entry: filesystem::directory_iterator(dirPath)){
    const auto fileName = dirPath + entry.path().filename().string();
    cout << readInfo(fileName) << endl;
  }
}

void addFileLong(){
  bool succsess = false;
  while (!succsess){
    string id;
    id = getID("Enter ID for new File");
    if (id == "EXIT") {
        return;
    }

    if (!checkFileExistLong(id)){
      info.push_back(id);
      getInfo(info);
      string fileName = "people/long/" + id + ".txt";
      ofstream output(fileName);
      output<< mkData(info);
      succsess = true;
      info.clear();
    } else {
      cout << "ID exists. To make changes use update function or type EXIT to cancle" << endl;
    }
  }
}

void deleteFileByID(){
  string id;
  bool exit = false;
  while (!exit){
    id = getID("enter ID");
    if (id == "EXIT"){
      return;
    }

    if (!checkFileExistLong(id)){
      cout << "ID Does not exists Try again or enter EXIT to cancle" << endl;

    } else {
      string filePath = dirPathLong + id + ".txt";
      remove(filePath.c_str());
      exit = true;
    }
  }
}

void updateByID(){
  string id;
  bool exit = false;
  while (!exit){
    id = getID("Enter ID to Update");

    if (id == "EXIT"){
      return;
    }

    if (!checkFileExistLong(id)){
      cout << "ID Does not exits. Try agian or enter EXIT to cancle" << endl;
    } else {
      string fullPath = "people/long/" + id + ".txt";
      readInfo(fullPath);
    }

    cout << mkString(info) << endl;

    bool updating = false;
    int cmd;
    string input;
    while (!updating){
      cout << "What Data to re-write:\n1) First Name\n2) Last name\n3) Hire Year\n4) Write Changes" << endl;
      cin >> cmd;
      switch (cmd){
        case 1:
          cout << "Enter new First Name" << endl;
          cin >> input;
          input = capitalize(input);
          info[1] = input;
          break;
        case 2:
          cout << "Enter new Last Name" << endl;
          cin >> input;
          input = capitalize(input);
          info[2] = input;
          break;
        case 3:
          cout << "Enter new Hire Year" << endl;
          cin >> input;
          capitalize(input);
          info[3] = input;
          break;
        case 4:{
          cout << "Confirm Data(1/0)\n" + mkString(info) << endl;
          cin >> input;
          if (input == "1"){
            string fullPath = "people/long/" + id;
            ofstream output(fullPath);
            output << mkData(info);
            return;
          }
        }
        case 5:
          updating = true;
          exit = true;
          break;
      }
    }
  }
}

void searchByID(){
  string id = getID("Enter ID to search for");
  if (!checkFileExistLong(id)) {
      cout << "ID does not exist" << endl;
  } else {
    id = dirPathLong + id + ".txt";
    cout << readInfo(id) << endl;
  }
}

string capitalize(string input) {
  for (int i = 0; i < (int)input.length(); i++) {
    input[i] = toupper(input[i]);
  }
  return input;
}

bool checkFileExistLong(string checkFile){
  for (auto& entry : filesystem::directory_iterator(dirPathLong)){
    const auto fileName = entry.path().filename().string();
    if (fileName == checkFile + ".txt") {
      return true;

    }
  }
  return false;
}

string readInfo(string fileName) {
  ifstream file(fileName);
  if (file.is_open()){
    string tempStr;
    while (!file.eof()){
      getline(file, tempStr, ',');
      info.push_back(tempStr);
    }
  }
  file.close();
  string strReturn = mkString(info);
  info.clear();
  return strReturn;
}

string getID(string output) {
  cout << output << endl;
  string strReturn;
  cin >> strReturn;
  return strReturn;
}

string mkString(const vector<string>& chkInfo){
  return ("ID: " + chkInfo[0] + "\nFirst Name: " + chkInfo[1] + "\nLast Name: " + chkInfo[2] + "\nHire Year: " + chkInfo[3]);
}

string mkData(const vector<string>& chkInfo){
  return ("" + chkInfo[0] + ", " + chkInfo[1] + ", " + chkInfo[2] + ", " + chkInfo[3]);
}


void getInfo(vector<string>& info){
  bool confirm = 0;
  string input;
  while (!confirm){
    int hireYear;
    cout << "Enter First Name" << endl;
    cin >> input;
    input = capitalize(input);
    info.push_back(input);
    cout << "Enter Last Name" << endl;
    cin >> input;
    input = capitalize(input);
    info.push_back(input);
    cout << "Enter Hire Year" << endl;
    cin >> hireYear;
    input = to_string(hireYear);
    info.push_back(input);  
    cout << "Confirm (1/0):\n" + mkString(info) << endl;
    cin >> confirm;
  }
}
