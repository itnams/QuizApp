#pragma once
#include<iostream>
using namespace std;

class Student {
private:
    string fullName;
    string studentCode;

public:
    Student() {
        fullName = "";
        studentCode = "";
    }
public:
    Student(string fullName, string studentCode) {
        this->fullName = fullName;
        this->studentCode = studentCode;
    }

    void getStudent() {
        cout << "Full Name: " << fullName << endl;
        cout << "Student Code: " << studentCode << endl;
    }
};