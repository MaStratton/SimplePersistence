#include "local.h"

map<string, Employee> IDMap;;
map<string, Employee> lNameMap;

string dirPathShort = "./people/simple/";
string dirPathLong = "./people/long/";
string dirPathLongSer = "./people/longSerialized/";



void Local::localMenu() {
    int cmd = -1;
    while (cmd != 0) {
        cout << "select Command" << endl;
        cout << strLocalMenu << endl;
        cin >> cmd;
        switch (cmd){
            case 1:
                display(getDirPath("long"));
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
            case 0:
                break;
            default:
                cout << "Invalid Command" << endl;
            break;
        }
    }
}

void Local::display(string dirPath) {
    auto start = chrono::high_resolution_clock::now();
    for (auto& entry: filesystem::directory_iterator(dirPath)){
        const auto fileName = dirPath + entry.path().filename().string();
        cout << readInfo(fileName) << endl;
    }
    auto finish = chrono::high_resolution_clock::now();
    auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);

    cout << (double)microseconds.count() / 1000000 << "Seconds"<< endl;
}

void Local::searchByLname() {
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

void Local::addFileLong(){
    bool succsess = false;
    while (!succsess){
        string id;
        id = getID("Enter ID for new File");
        if (id == "EXIT") {
            return;
        }

        if (!checkFileExistLong(id)) {
            vector<string> info;
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

void Local::deleteFileByID(){
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

void Local::updateByID(){
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

void Local::searchByID(){
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

bool Local::checkFileExistLong(string checkFile){
  for (auto& entry : filesystem::directory_iterator(dirPathLong)){
    const auto fileName = entry.path().filename().string();
    if (fileName == checkFile + ".txt") {
      return true;

    }
  }
  return false;
}

string Local::readInfo(string fileName) {
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



void Local::indexDatabase(){
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

void Local::searchIDIndexbyID() {
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

map<string, Employee> &getMap() {
  return IDMap;
}

string Local::getDirPath(string dir) {
  if (dir == "long"){
      return dirPathLong;
  } else if (dir == "longser"){
      return dirPathLongSer;
  }else {
      return dirPathShort;
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