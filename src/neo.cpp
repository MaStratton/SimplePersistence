//
// Created by matthew on 8/7/24.
//

#include "neo.h"

using namespace std;

void Neo::neo4jMenu(){
int cmd = 1;
  while (cmd != 0){
    cout << "Select Neo4j command" << endl;
    cout << strNeo4jMenu << endl;
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

void Neo::neoAddPeople(map<string, Employee>& IDMap){
  for (auto record : IDMap){
    string cmdString = "./cypherScript/add.sh " + record.second.getID()+ " " + record.second.getfName()+ " " + record.second.getlName()+ " " + record.second.getHireYear();
    const char* cmdStringC = cmdString.c_str();
    system(cmdStringC);
  }
}

void Neo::neoAddOne(){
  vector<string> info;
  string ID = getID("Enter ID");
  if (neoCheckID(ID)){
    cout << "ID Exists" << endl;
  } else {
    info.push_back(ID);
    getInfo(info);

    auto start = chrono::high_resolution_clock::now();
    string cmd = "./cypherScript/add.sh " + info[0] + " " + info[1] + " " + info[2] + " " + info[3];
    system(cmd.c_str());
    info.clear();

    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);
    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
  }
}

void Neo::neoAddRel(){
  cout << "The Relationship added will go both ways" << endl;
  string IDpOne = getID("Enter ID for Person One");
  string IDpTwo = getID("Enter ID for Person Two");
  if (neoCheckID(IDpOne) && neoCheckID(IDpTwo)){
    cout << "Enter Relationship" << endl;
    string rel = "";
    cin >> rel;

    auto start = chrono::high_resolution_clock::now();
    string cmdString = "./cypherScript/addRel.sh " + IDpOne + " " + IDpTwo + " " + rel;
    system(cmdString.c_str());

    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);
    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

  } else {
    cout << "One or both IDs do not exist or error has occured" << endl;
  }
}

void Neo::neoUpdate(){
  vector<string> info;
  string ID = getID("Enter ID to Update");
  if (neoCheckID(ID)){
    info.push_back(ID);
    cout << "Due to limitations of neo4J, Please enter all info for the person under this ID repeating what needs to be unchanged and changing what needs to be changed" << endl;
    getInfo(info);

    auto start = chrono::high_resolution_clock::now();
    string cmd = "./cypherScript/updateOne.sh " + info[0] + " " + info[1] + " " + info[2] + " " + info[3];
    system(cmd.c_str());
    info.clear();
    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);
    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

  }
}

void Neo::neoFindOne(){
  string ID = getID("Enter ID to Search");

  auto start = chrono::high_resolution_clock::now();
  string sysCmd = "./cypherScript/findOne.sh " + ID;
  system(sysCmd.c_str());

  auto finish = chrono::high_resolution_clock::now();
  auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);
  cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

}

void Neo::neoDelOne(){
  string ID = getID("Enter ID to Delete");
  if (neoCheckID(ID)){

    auto start = chrono::high_resolution_clock::now();
    string cmd = "./cypherScript/deleteOne.sh " + ID;
    system(cmd.c_str());

    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);
    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;

  }
}

bool Neo::neoCheckID(string ID){
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