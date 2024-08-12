#include "mongo.h"


using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

mongocxx::instance instance{};
mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
auto db = client["SimplePersistance"];
auto collection = db["people"];

void Mongo::mongoMenu(){
  int cmd = 1;
  while (cmd != 0){
    cout << "Select MongoDB command" << endl;
    cout << strMongoMenu << endl;
    cin >> cmd;

    switch(cmd){
      case 1:
        dbAddFiles(getMap());
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

void Mongo::dbAddFiles(map<string, Employee>& IDMap){
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

void Mongo::dbAddOne(){
  vector<string> info;
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

void Mongo::dbSearch(){
  vector<string> info;
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

  } else {
    cout << "ID Does Not Exist" << endl;
  }
}


void Mongo::dbUpdate(){
  vector<string> info;
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

void Mongo::dbDelete(){
  string ID = getID("Enter ID to Delete");
  if (dbCheckIfExist(ID)){
    collection.delete_one(make_document(kvp("ID", ID)));
    cout << "Document Deleted" << endl;
  }
}

bool Mongo::dbCheckIfExist(string ID){
  if(collection.find_one(make_document(kvp("ID", ID)))){
    return true;
  }
  return false;
}