#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <algorithm>


using namespace std;


struct StudentRec{

    string FirstName;
    string LastName;
    string ID;
    double GPA;

    void showRecord();

};

class StudentDatabase{
private:
    struct Node{
        StudentRec data;
        Node* Next;
    };

    //Number of records
    unsigned int recordCount;

    //Pointer to head of linked list
    Node* head;

    string DatabaseFileName;

public:

    //Constructor (read file, copy to list, close file, sort list)
    StudentDatabase(string fileName);

    //Destructor (save list to file and close file, destroy list)
    ~StudentDatabase();

    //sort
    void sort();

    //Return num valid records
    unsigned int size() const;

    //Add record (detect duplicate ID, make sure still sorted after adding, update if existing ID)
    void addRecord(const StudentRec &r);

    //Remove record and return t/f for success
    bool removeRecord(string ID);

    //Search by index
    StudentRec* operator[](unsigned int index)const;

    //Search by ID
    StudentRec* operator[](string ID) const;

    //Srch by name
    vector<StudentRec> searchByName(string name) const;

    void displayAll();
};

#endif // DATABASE_H
