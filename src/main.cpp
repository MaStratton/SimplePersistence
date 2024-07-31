#include "../inc/main.h"
#include "../inc/employee.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <map>
#include <chrono>

using namespace std;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

mongocxx::instance instance{};
mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
auto db = client["SimplePersistance"];
auto collection = db["people"];

string dirPathShort = "./people/simple/";
string dirPathLong = "./people/long/";
string dirPathLongSer = "./people/longSerialized/";

string menu = "1) Display \n2) Add File\n3) Delete File by ID\n4) Update by ID\n5) Search by ID(File System Search)\n6) Search by ID (Memory Search)\n7) Search by Last Name(Memory Search)\n8) Search By Last Name (File Search)\n9) Serialize Employees\n10) Search Serialized Files\n11) MongoDB Stuff\n12) Neo4j\n0) EXIT";

string mongoMenu = "1) Add Files to Collection\n2)Add One Person\n3) Search By ID\n4) Update Document\n5) Delete by ID\n0) Top Menu";
string neo4jMenu = "1) Add all Indexed People\n2) Add Person\n3) Add Relationship\n4) Search By ID\n5) Update by ID\n6) Delete by ID\n0) Top Menu";

string neo4jExists = "exist\nTRUE\n";

map<string, Employee> IDMap;;
map<string, Employee> lNameMap;

vector<string> info;
Employee employeeSize;

int main() {
  indexDatabase();
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
        break;
      case 6:
        searchIDIndexbyID();
        break;
      case 7:
        searchByLname();
        break;
      case 8:
        searchByLnameFile();
        break;
      case 9:
        serializeLong();
        break;
      case 10:
        deserialize();
        break;
      case 11:
        mongo();
        break;
      case 12:
        neo4j();
        break;
      default:
        break;
    }
  }
  return 0;
}

void mongo(){
  int cmd = 1;
  while (cmd != 0){
    cout << "Select MongoDB command" << endl;
    cout << mongoMenu << endl;
    cin >> cmd;

    switch(cmd){
      case 1:
        dbAddFiles();
        break;
      case 2:
        dbAddOne();
        break;
      case 3:
        dbSearch();
        break;
      case 4:
        dbUpdate();
        break;
      case 5:
        dbDelete();
        break;
      case 0:
        break;
      default:
        cout << "Invalid Command" << endl;
        break;
    }

  }

}

void dbAddFiles(){
  for (auto record: IDMap){
    string ID = record.second.getID();
    string fName = record.second.getfName();
    string lName = record.second.getlName();
    string hireYear = record.second.getHireYear();
    collection.insert_one(make_document(
        kvp("ID", ID),
        kvp("First Name", fName),
        kvp("Last Name", lName),
        kvp("Hire Year", hireYear)
        )
    );
  }
}

void dbAddOne(){
  string ID = getID("Enter New ID");
  if (!dbCheckIfExist(ID)){
    info.push_back(ID);
    getInfo(info);
    collection.insert_one(
        make_document(
          kvp("ID", ID),
          kvp("First Name", info[1]),
          kvp("Last Name", info[2]),
          kvp("Hire Year", info[3])
        )
      );
  } else {
    cout << "ID Exists" << endl;
  }
}

void dbSearch(){
  string ID = getID("Enter ID to Find");
  if (dbCheckIfExist(ID)){
    auto person = collection.find_one(make_document(kvp("ID", ID)));
    auto personJsonStr = bsoncxx::to_json(person->view());
    Json::Value personJson;
    Json::Reader reader;
    reader.parse(personJsonStr, personJson);
    info.push_back((personJson["ID"].toStyledString().substr(1,personJson["ID"].toStyledString().size()-3)));
    info.push_back((personJson["First Name"].toStyledString().substr(1,personJson["First Name"].toStyledString().size()-3)));
    info.push_back((personJson["Last Name"].toStyledString().substr(1,personJson["Last Name"].toStyledString().size()-3)));
    info.push_back((personJson["Hire Year"].toStyledString().substr(1,personJson["Hire Year"].toStyledString().size()-3)));
    
    cout << mkString(info) << endl;
    info.clear();

  } else {
    cout << "ID Does Not Exist" << endl;
  }
}


void dbUpdate(){
  string ID = getID("Enter ID to Find");
  if(dbCheckIfExist(ID)){
    int cmd = -1;
    auto person = collection.find_one(make_document(kvp("ID", ID)));
    auto personJsonStr = bsoncxx::to_json(person->view());
    Json::Value personJson;
    Json::Reader reader;
    reader.parse(personJsonStr, personJson);
    info.push_back((personJson["ID"].toStyledString().substr(1,personJson["ID"].toStyledString().size()-3)));
    info.push_back((personJson["First Name"].toStyledString().substr(1,personJson["First Name"].toStyledString().size()-3)));
    info.push_back((personJson["Last Name"].toStyledString().substr(1,personJson["Last Name"].toStyledString().size()-3)));
    info.push_back((personJson["Hire Year"].toStyledString().substr(1,personJson["Hire Year"].toStyledString().size()-3)));
    
    cout << mkString(info) << endl;
    string input = "";
    while (cmd != 0){
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
            collection.update_one(make_document(kvp("ID", info[0])), make_document(kvp("$set", make_document(kvp("First Name", info[1])))));
            collection.update_one(make_document(kvp("ID", info[0])), make_document(kvp("$set", make_document(kvp("Last Name", info[2])))));
            collection.update_one(make_document(kvp("ID", info[0])), make_document(kvp("$set", make_document(kvp("Hire Year", info[3])))));
            info.clear();
            return;
          }
        }
      }
    }
  }
}

void dbDelete(){
  string ID = getID("Enter ID to Delete");
  if (dbCheckIfExist(ID)){
    collection.delete_one(make_document(kvp("ID", ID)));
    cout << "Document Deleted" << endl;
  }
}

bool dbCheckIfExist(string ID){
  if(collection.find_one(make_document(kvp("ID", ID)))){
    return true;
  }
  return false;
}

void neo4j(){
int cmd = 1;
  while (cmd != 0){
    cout << "Select Neo4j command" << endl;
    cout << neo4jMenu << endl;
    cin >> cmd;
    switch (cmd){
      case 1:
        //neoAddPeople();
        cout << "I'M NOT DOING THIS FOR ANOTHER TWO HOURS" << endl;
        break;
      case 2:
        neoAddOne();
        break;
      case 3:
        neoAddRel();
        break;
      case 4:
        neoFindOne();
        break;
      case 5:
        neoUpdate();
        break;
      case 6:
        neoDelOne();
        break;
      case 0:
        break;
    }
  }
}

void neoAddPeople(){
  for (auto record : IDMap){
    string cmdString = "./cypherScript/cypherAdd.sh " + record.second.getID()+ " " + record.second.getfName()+ " " + record.second.getlName()+ " " + record.second.getHireYear();
    const char* cmdStringC = cmdString.c_str();
    system(cmdStringC);
  }
}

void neoAddOne(){
  string ID = getID("Enter ID");
  if (neoCheckID(ID)){
    cout << "ID Exists" << endl;
  } else {
    info.push_back(ID);
    getInfo(info);
    string cmd = "./cypherScript/cypherAdd.sh " + info[0] + " " + info[1] + " " + info[2] + " " + info[3];
    system(cmd.c_str());
    info.clear();
  }
}

void neoAddRel(){
  cout << "The Relationship added will go both ways" << endl;
  string IDpOne = getID("Enter ID for Person One");
  string IDpTwo = getID("Enter ID for Person Two");
  if (neoCheckID(IDpOne) && neoCheckID(IDpTwo)){
    cout << "Enter Relationship" << endl;
    string rel = "";
    cin >> rel;
    string cmdString = "./cypherScript/addRel.sh " + IDpOne + " " + IDpTwo + " " + rel;
    system(cmdString.c_str());
  } else {
    cout << "One or both IDs do not exist or error has occured" << endl;
  }
}

void neoUpdate(){

}

void neoFindOne(){
  string ID = getID("Enter ID to Search");
  string cmd = "./cypherScript/findOne.sh " + ID;
  system(cmd.c_str());
}

void neoDelOne(){

}

bool neoCheckID(string ID){
  char buffer[128];
  string result = "";
  string cmd = "./cypherScript/checkID.sh " + ID;
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe) {
    cout << "Failed" << endl;
    return false;
  }

  while (!feof(pipe)){
    if (fgets(buffer, 128, pipe) != NULL){
         result += buffer;
   }
  }
  pclose(pipe);
  if (result == neo4jExists){
    return true;
  }
  return false;
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

string capitalize(string input) {
  for (int i = 0; i < (int)input.length(); i++) {
    input[i] = toupper(input[i]);
  }
  return input;
}

void display(string dirPath) {
  auto start = chrono::high_resolution_clock::now();
  for (auto& entry: filesystem::directory_iterator(dirPath)){
    const auto fileName = dirPath + entry.path().filename().string();
    cout << readInfo(fileName) << endl;
  }
  auto finish = chrono::high_resolution_clock::now();
  auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

  cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
}

string mkString(const vector<string>& chkInfo){
  return ("ID: " + chkInfo[0] + "\nFirst Name: " + chkInfo[1] + "\nLast Name: " + chkInfo[2] + "\nHire Year: " + chkInfo[3]);
}

string mkData(const vector<string>& chkInfo){
  return ("" + chkInfo[0] + ", " + chkInfo[1] + ", " + chkInfo[2] + ", " + chkInfo[3]);
}

void addFileLong(){
  bool succsess = false;
  while (!succsess){
    string id;
    id = getID("Enter ID for new File");
    if (id == "EXIT") {
        return;
    }

    if (!checkFileExistLong(id)) {
      auto start = chrono::high_resolution_clock::now();
      info.push_back(id);
      getInfo(info);
      string fileName = "people/long/" + id + ".txt";
      ofstream output(fileName);
      output<< mkData(info);
      succsess = true;
      info.clear();
      Employee employee(info[0], info[1], info[2], info[3]);
      IDMap.insert({employee.getID(), employee});
      lNameMap.insert({employee.getlName(), employee});
      auto finish = chrono::high_resolution_clock::now();
      auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

  cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

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
      auto start = chrono::high_resolution_clock::now();
      string filePath = dirPathLong + id + ".txt";
      remove(filePath.c_str());
      exit = true;
      lNameMap.erase( IDMap.at(id).getID());
      IDMap.erase(id);
      auto finish = chrono::high_resolution_clock::now();
      auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

      cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
      return;
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
            auto start = chrono::high_resolution_clock::now();
            string fullPath = "people/long/" + id;
            ofstream output(fullPath);
            output << mkData(info);
            IDMap.at(id).update(info[1], info[2], info[3]);
            lNameMap.erase(info[2]);
            lNameMap.insert({info[2], IDMap.at(id)});
            auto finish = chrono::high_resolution_clock::now();
            auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

            cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
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
    auto start = chrono::high_resolution_clock::now();
    id = dirPathLong + id + ".txt";
    cout << readInfo(id) << endl;
    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

  }
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

void indexDatabase(){
  for (auto& entry: filesystem::directory_iterator(dirPathLong)){
    const auto fileName = dirPathLong + entry.path().filename().string();
    ifstream file(fileName);

    vector<string> tempInfo;

    if (file.is_open()){
      string tempStr;
      while (!file.eof()){
        getline(file, tempStr, ',');
        tempInfo.push_back(tempStr);
      }
    }
    file.close();
    tempInfo[1] = tempInfo[1].substr(1);
    tempInfo[2] = tempInfo[2].substr(1);
    tempInfo[3] = tempInfo[3].substr(1);

    Employee employee(tempInfo[0], tempInfo[1], tempInfo[2], tempInfo[3]);
    string tempID = employee.getID();
    IDMap.insert({tempInfo[0], employee});
    lNameMap.insert({tempInfo[2], employee});
  }
}

void searchIDIndexbyID() {
  string id = getID("Enter ID to Find");
  try {
    auto start = chrono::high_resolution_clock::now();
    cout << IDMap.at(id).toString() << endl;
    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

  } catch (const std::out_of_range& e) {
    cout << "Entry Does Not Exits\n" << endl;;
  }

}

void searchByLname() {
  string lName;
  cout << "Enter Last Name to Find" << endl;
  cin >> lName;
  lName = capitalize(lName);
  try {
    cout << lNameMap.at(lName).toString() << endl;
  } catch (const std::out_of_range& e) {
    cout << "Entry Does Not Exist\n" << endl;
  }
}

void searchByLnameFile(){
  string lName;
  cout << "Enter Last Name to Find" << endl;
  cin >> lName;
  lName = capitalize(lName);
  auto start = chrono::high_resolution_clock::now();
  for (auto& entry: filesystem::directory_iterator(dirPathLong)){
    const auto fileName = dirPathLong + entry.path().filename().string();
    ifstream file(fileName);
    if (file.is_open()){
      string tempStr;
      vector<string> tempInfo;
      while (!file.eof()){
        getline(file, tempStr, ',');
        tempInfo.push_back(tempStr);
      }

      string templName = tempInfo[2].substr(1);

      if (lName == templName){
        cout << mkString(tempInfo) << endl;
      } 
    }
  file.close();
  }
  auto finish = chrono::high_resolution_clock::now();
  auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

  cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

}

void serializeLong() {
  auto start = chrono::high_resolution_clock::now();
  for (auto record : IDMap) {
    record.second.serialize();
  }
  auto finish = chrono::high_resolution_clock::now();
  auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

  cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
}

void deserialize(){
    string id = getID("Enter ID to find");
    auto start = chrono::high_resolution_clock::now();
    Employee employee = Employee::deserialize(id);
    cout << employee.toString() << endl;
    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

  cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
}


