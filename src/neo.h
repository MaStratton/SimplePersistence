#pragma once
#include "main.h"
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <cstdlib>


#ifndef NEO_H
#define NEO_H

using namespace std;

class Neo {
private:
    string strNeo4jMenu = "1) Add all Indexed People\n2) Add Person\n3) Add Relationship\n4) Search By ID\n5) Update by ID\n6) Delete by ID\n0) Top Menu";
    string neo4jExists = "exist\nTRUE\n";

public:
    Neo() = default;

    void neo4jMenu();
    void neoAddPeople(map<string, Employee>& IDMap);
    void neoAddOne();
    void neoAddRel();
    void neoUpdate();
    void neoFindOne();
    void neoDelOne();

    bool neoCheckID(string ID);
};

#endif //NEO_H
