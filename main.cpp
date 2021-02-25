#include <iostream>
#include <database.h>

using namespace std;


//Prints the Menu
void PrintMenu(){
    cout << "\nLab 10 | Justin Panchula and Avery Brinkman\n";
    cout << "Please choose:\n";
    cout << "(1) Add a student record\n";
    cout << "(2) Delete a student record\n";
    cout << "(3) Find a student's information by last name\n";
    cout << "(4) Find a student's information by ID\n";
    cout << "(5) Display all information in the database\n";
    cout << "(6) Display the number of students in the database\n";
    cout << "(7) Find a student's information by index\n";
    cout << "(8) Save and exit program\n";
    cout << "User Selection: ";
}




int main(){

    StudentDatabase Database("C:/Users/avery/OneDrive - University of Cincinnati/C++/lab10new/students.txt");

    int userInput = 0;
    while(userInput != 8){

        PrintMenu();

        cin >> userInput;

        switch(userInput){
        case 1:{
            StudentRec newStudent;

            cout << "Enter first name, last name, ID, and GPA (Separate w/ spaces): " << endl;
            cin >> newStudent.FirstName >> newStudent.LastName >> newStudent.ID >> newStudent.GPA;

            Database.addRecord(newStudent);

            break;

        }
        case 2:{
            string id;

            cout << "Enter ID of student to delete: " << endl;
            cin >> id;


            Database.removeRecord(id);
            break;
        }
        case 3:{
            string srchName;
            vector<StudentRec> results;
            cout << "Enter last name of student to search: " << endl;
            cin >> srchName;
            results=Database.searchByName(srchName);
            for(unsigned int i = 0; i < results.size(); i++){
                results.at(i).showRecord();
            }
            break;

        }

        case 4:{
            string id;
            cout << "Enter student ID: " << endl;
            cin >> id;
            Database[id]->showRecord();
            break;
        }

        case 5:{
            Database.displayAll();
            break;
        }
        case 6:{
            cout << "Number of students in record: " << Database.size() << endl;
            break;
        }
        case 7:{
            unsigned int index;
            do{
            cout << "Enter index of student: " << endl;
            cin >> index;
            }while(index>Database.size());
            Database[index]->showRecord();
            break;
        }
        case 8:{
           break;
        }
        default:{
            cout << "Invalid input." << endl;
            break;
        }
        }
    }
}
