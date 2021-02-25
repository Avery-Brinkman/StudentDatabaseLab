#include "database.h"

void StudentRec::showRecord() {
    cout << left << setw(20) << this->FirstName + " " + this->LastName << setw(10) << this->ID << setw(5) << this->GPA << endl;
}

void StudentDatabase::sort() {
    unsigned int size = this->size();



    for (unsigned int i = 0; i < size - 1; i++) {

        Node* left = head;
        Node* right = head->Next;

        for (unsigned int n = 0; n < size - 1 - i; n++) {

            if (left->data.ID > right->data.ID) {
                if (left == head) {
                    head = right;
                    left->Next = right->Next;
                    right->Next = left;
                    right = left->Next;
                }
                else {
                    Node* prev = new Node;
                    prev->Next = head;
                    do {
                        prev = prev->Next;
                    } while (prev->Next != left);
                    prev->Next = right;
                    left->Next = right->Next;
                    right->Next = left;

                    right = left->Next;
                }

            }
            else {
                left = left->Next;
                right = right->Next;
            }
        }
    }




}

StudentDatabase::StudentDatabase(string fileName) {

    this->DatabaseFileName = fileName;

    ifstream studentFile;

    studentFile.open(fileName);
    if (!studentFile.is_open()) {
        cout << "Student file failed to open" << endl;
    }

    string first, last, id;
    double gpa;


    Node* tail = nullptr;
    head = nullptr;

    //From: https://www.codesdope.com/blog/article/c-linked-lists-in-c-singly-linked-list/

    while (!studentFile.eof()) {
        studentFile >> first >> last >> id >> gpa;

        Node* temp = new Node;

        temp->data.FirstName = first;
        temp->data.LastName = last;
        temp->data.ID = id;
        temp->data.GPA = gpa;
        temp->Next = nullptr;

        if (head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {
            tail->Next = temp;
            tail = tail->Next;
        }
    }


    studentFile.close();



    //Sort
    this->sort();


    Node* left = head;
    Node* right = head->Next;

    for (unsigned int i = 0; i < this->size() - 1; i++) {
        if (left->data.ID == right->data.ID) {
            cout << "Dupe found." << endl;
            cout << "Deleting: ";
            right->data.showRecord();
            cout << "Keeping: ";
            left->data.showRecord();
            left->Next = right->Next;

            i = 0;
            left = head;
            right = head->Next;
        }
        else {
            left = left->Next;
            right = right->Next;
        }
    }
}

StudentDatabase::~StudentDatabase() {
    cout << "Destructor called" << endl;
    ofstream studentFile;
    studentFile.open(DatabaseFileName);

    Node* temp;
    Node* delNode;

    unsigned int size = this->size();

    temp = head;
    for (unsigned int i = 0; i < size; i++) {
        studentFile << temp->data.FirstName << " " << temp->data.LastName << " " << temp->data.ID << " " << temp->data.GPA;
        if (temp->Next != nullptr) {
            studentFile << endl;
        }
        temp = temp->Next;
    }
    studentFile.close();

    temp = head;
    while (temp->Next != nullptr) {
        delNode = temp;
        temp = temp->Next;
        delete delNode;
    }
}

void StudentDatabase::displayAll() {

    cout << left << setw(5) << "No." << setw(20) << "Name" << setw(10) << "ID" << setw(5) << "GPA" << endl;
    cout << "---------------------------------------" << endl;

    Node* temp = new Node;

    unsigned int i = 1;

    temp = head;
    for (unsigned int n = 0; n < this->size(); n++) {
        cout << left << setw(5) << i << setw(20) << temp->data.FirstName + " " + temp->data.LastName << setw(10) << temp->data.ID << setw(5) << temp->data.GPA << endl;
        temp = temp->Next;
        i++;
    }

}

unsigned int StudentDatabase::size() const {

    Node* temp = new Node;

    temp = head;

    unsigned int size = 0;
    while (temp->Next != nullptr) {
        size++;
        temp = temp->Next;
    }
    return size;
}

void StudentDatabase::addRecord(const StudentRec& r) {

    Node* temp = new Node;

    temp->data = r;
    bool foundDupe = false;

    Node* cmpr = head;
    for (unsigned int i = 0; i < this->size(); i++) {
        if (cmpr->data.ID == temp->data.ID) {
            foundDupe = true;
            break;
        }
        else {
            cmpr = cmpr->Next;
        }
    }
    if (foundDupe) {
        unsigned int input = 0;
        do {
            cout << "This ID already exists." << endl;
            cmpr->data.showRecord();
            cout << "(1) Update existing" << endl;
            cout << "(2) Cancel" << endl;
            cin >> input;
        } while (input != 1 && input != 2);
        if (input == 1) {
            cmpr->data = temp->data;
        }
    }
    else {
        if (temp->data.ID <= head->data.ID) {
            temp->Next = head;
            head = temp;
        }
        else {
            temp->Next = head->Next;
            head->Next = temp;

            this->sort();
        }
    }

}

bool StudentDatabase::removeRecord(string ID) {
    Node* prev = new Node;
    Node* temp = new Node;

    bool isFound = false;

    prev = head;
    temp = head->Next;
    while (temp->Next != nullptr) {
        if (prev->data.ID == ID) {
            head = temp;
            delete prev;
            isFound = true;
            break;
        }
        else if (temp->data.ID == ID) {
            prev->Next = temp->Next;
            delete temp;
            isFound = true;
            break;
        }
        prev = temp;
        temp = temp->Next;
    }
    if (isFound) {
        cout << "Student deleted." << endl;
        return true;
    }
    else {
        cout << "Student not found." << endl;
        return false;
    }
}

vector<StudentRec> StudentDatabase::searchByName(string name) const {

    Node* temp;
    temp = head;

    vector<StudentRec> results;

    for (unsigned int i = 0; i < this->size(); i++) {

        if (temp->data.LastName == name) {
            results.push_back(temp->data);
        }
        temp = temp->Next;
    }
    if (results.size() == 0) {
        cout << "Not found." << endl;
    }
    return results;
}

StudentRec* StudentDatabase::operator[](unsigned int index)const {


    Node* temp;
    temp = head;
    for (unsigned int i = 1; i < index; i++) {
        temp = temp->Next;
    }
    return &temp->data;

}
StudentRec* StudentDatabase::operator[](string ID)const {
    Node* temp;
    temp = head;
    for (unsigned int i = 0; i < this->size(); i++) {
        if (temp->data.ID == ID) {
            return &temp->data;
        }
        else {
            temp = temp->Next;
        }
    }

    cout << "Not found" << endl;
    temp->data.FirstName = "-";
    temp->data.LastName = "-";
    temp->data.ID = "-";
    temp->data.GPA = -1;

    return &temp->data;
}
