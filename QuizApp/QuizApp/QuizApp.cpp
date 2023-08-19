#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cctype>
#include <sstream>
#include <iterator>
#include "Question.cpp"
#include "Student.cpp"
#include <algorithm>
using namespace std;

vector<string> stringToVector(const string& str) {
    vector<string> vec;
    istringstream iss(str);
    string word;

    while (iss >> word) {
        vec.push_back(word);
    }

    return vec;
}

list<Question> loadingFile() {
    list<Question> questions;
    ifstream file("files/input.txt");

    if (file.is_open()) {
        string line;
        list<string> lines;

        while (getline(file, line)) {
            lines.push_back(line);
        }

        file.close();

        int index = 0;
        for (const auto& line : lines) {
            if (line == "5" && index != 0) {
                if(index + 1 < lines.size() && index + 2 < lines.size()) {
                    auto itQuestion = next(lines.begin(), index - 1);
                    auto itOptions = next(lines.begin(), index + 1);
                    auto itAnswer = next(lines.begin(), index + 2);
                    string question = *itQuestion;
                    vector<string> options = stringToVector(*itOptions);
                    string answer = *itAnswer;
                    Question questionItem(question, options, answer);
                    questions.push_back(questionItem);
                }
            }
            index++;
        }
    }
    else {
        cout << "Unable to open file." << endl;
    }
    return questions;
}

Student inputStudent() {
    string fullName;
    string studentCode;
    bool validFullName = false;
    bool validStudentCode = false;
    while (!validFullName) {
        cout << "Full Name:" << endl;
        getline(cin, fullName);
        if (fullName.size() > 0) {
            validFullName = true;
        } else {
            cout << "Please join again." << endl;
        }
    }
    while (!validStudentCode) {
        cout << "Student Code:" << endl;
        cin >> studentCode;
        if (studentCode.size() > 7) {
            validStudentCode = true;
        }
        else {
            cout << "Please join again." << endl;
        }
    }
    Student student(fullName, studentCode);
    return student;
}

list<char> showQuestion(list<Question> questions) {
    list<char> answers;
    cout << "Total questions: " << questions.size() << endl;
    cout << "Time: " << questions.size() << " minutes" << endl;
    for (const auto& question : questions) {
        char answer;
        question.display();
        bool validAnswer = false;
        while (!validAnswer) {
            cout << "Enter answer or enter 0 to skip" << endl;
            cin >> answer;
            if (tolower(answer) - 'a' < question.getOptions().size()) {
                validAnswer = true;
            }
            else if (answer == '0') {
                validAnswer = true;
                answers.push_back(' ');
            }
            else {
                cout << "Please join again." << endl;
            }
        }
        if (answer != '0') {
            answers.push_back(tolower(answer));
        }
    }
    return answers;
}

void previewSnswer(list<char> answers) {
    int i = 0;
    cout << "Preview" << endl;
    for (const auto& answer : answers) {
        i++;
        cout << i << ". " << answer << endl;
    }
}

void editAnswers(Student student, list<Question> questions, list<char> answers) {
    string selected;
    bool validSelected = false;
    list<char> answersEdited = answers;
    while (!validSelected) {
        cout << "Please select a question to edit, or enter OK to submit." << endl;
        cin >> selected;
        transform(selected.begin(), selected.end(), selected.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        if (selected == "ok") {
            int i = 0;
            int rightAnswer = 0;
            for (const auto& question : questions) {
                auto itAnswers = answers.begin();
                advance(itAnswers, i);
                char answer = *itAnswers;
                if (question.getAnswer().front() == (answer)) {
                    rightAnswer++;
                }
                i++;
            }
            student.getStudent();
            cout << "Result:" << rightAnswer << "/" << questions.size() << endl;
            cout << "Scores:" << 10/questions.size()*rightAnswer << endl;
            validSelected = true;
        }
        else {
            int num;
            try {
                num = stoi(selected) - 1;
                if (num >= questions.size()) {
                    cout << "Please join again." << std::endl;
                }
                else {
                    if (num >= 0 && num < questions.size()) {
                        list<Question>::iterator it = questions.begin();
                        advance(it, num);
                        Question element = *it;
                        element.display();
                        bool validAnswer = false;
                        while (!validAnswer) {
                            char answer;
                            cout << "Please selected aswe" << endl;
                            cin >> answer;
                            if (tolower(answer) - 'a' < element.getOptions().size()) {
                                auto it = answersEdited.begin();
                                std::advance(it, num);
                                *it = tolower(answer);
                                validAnswer = true;
                            } else {
                                cout << "Please join again." << endl;
                            }
                        }
                    }
                    previewSnswer(answersEdited);
                    editAnswers(student, questions, answersEdited);
                    validSelected = true;
                }
            }
            catch (const std::exception& e) {
                cout << "Please join again." << std::endl;
                validSelected = false;
            }
        }
    }
}

int main()
{
    list<Question> questions;
    list<char> answers;
    Student student;
    student = inputStudent();
    questions = loadingFile();
    answers = showQuestion(questions);
    previewSnswer(answers);
    editAnswers(student, questions, answers);
}