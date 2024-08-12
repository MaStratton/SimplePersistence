#pragma once
#include "main.h"
#include <fstream>
#include <filesystem>
#include <map>


#ifndef LOCAL_H
#define LOCAL_H



class Local {
private:
    string strLocalMenu = "1) Display \n2) Add File\n3) Delete File by ID\n4) Update by ID\n5) Search by ID(File System Search)\n6) Search by ID (Memory Search)\n7) Search by Last Name(Memory Search)\n8) Search By Last Name (File Search)\n9) Serialize Employees\n10) Search Serialized Files";


public:
    void localMenu();
    void display(string dirPath);
    void addFileLong();
    string readInfo(string fileName);
    void deleteFileByID();
    void updateByID();
    void searchByID();
    bool checkFileExistLong(string checkFile);

    void indexDatabase();
    void serializeLong();
    void deserialize();

    void searchIDIndexbyID();
    void searchByLname();
    void searchByLnameFile();

    map<string, Employee> &getMap();
    string getDirPath(string dir);


};



#endif //LOCAL_H
