#include "main.h"
#include <fstream>
#include <filesystem>

Neo neo;
Mongo mongo;
Local local;

using namespace std;


string menu = "1)Flat Files And Indexed\n2) MongoDB Stuff\n3) Neo4j\n0) EXIT";
Employee employeeSize;

int main() {
  local.indexDatabase();
  int cmd = -1;
  while (cmd != 0){
    cout << "select Command" << endl;
    cout << menu << endl;
    cin >> cmd;

    switch (cmd){
      case 1:
        local.localMenu();
      case 2:
        mongo.mongoMenu();
        break;
      case 3:
        neo.neo4jMenu();
        break;
      default:
        break;
    }
  }
  return 0;
}

map<string, Employee> &getMap() {
  return local.getMap();
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

string getID(string output) {
  cout << output << endl;
  string strReturn;
  cin >> strReturn;
  return strReturn;
}

string capitalize(string input) {
  for (int i = 0; i < (int)input.length(); i++) {
    input[i] = toupper(input[i]);
  }
  return input;
}



string mkString(const vector<string>& chkInfo){
  return ("ID: " + chkInfo[0] + "\nFirst Name: " + chkInfo[1] + "\nLast Name: " + chkInfo[2] + "\nHire Year: " + chkInfo[3]);
}

string mkData(const vector<string>& chkInfo){
  return ("" + chkInfo[0] + ", " + chkInfo[1] + ", " + chkInfo[2] + ", " + chkInfo[3]);
}

