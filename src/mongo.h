#pragma once
#include "main.h"
#include <string>
#include <vector>
#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>


#ifndef MONGO_H
#define MONGO_H

using namespace std;

class Mongo {
private:
    string strMongoMenu = "1) Add Files to Collection\n2)Add One Person\n3) Search By ID\n4) Update Document\n5) Delete by ID\n0) Top Menu";

public:
    void mongoMenu();
    void dbAddFiles(map<string, Employee>& IDMap);
    void dbAddOne();
    void dbSearch();
    void dbUpdate();
    void dbDelete();
    bool dbCheckIfExist(string ID);

};



#endif //MONGO_H
