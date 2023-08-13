#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Question.cpp"
#include <sstream>
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
int main()
{
    list<Question> questions;
    ifstream file("files/input.txt"); // Đường dẫn đến file txt
    list<char> answers;

    if (file.is_open()) {
        string line;
        list<string> lines; // Danh sách dòng

        while (getline(file, line)) {
            lines.push_back(line); // Thêm dòng vào danh sách
        }

        file.close();

        int index = 0;
        for (const auto& line : lines) {
            if (line == "5" && index != 0) {
                auto itQuestion = next(lines.begin(), index - 1);
                auto itOptions = next(lines.begin(), index + 1);
                auto itAnswer = next(lines.begin(), index + 2);
                string question = *itQuestion;
                vector<string> options = stringToVector(*itOptions);
                string answer = *itAnswer;
                Question questionItem(question, options, answer);
                questions.push_back(questionItem);
            }
            index++;
        }
    }
    else {
        cout << "Không thể mở file." << endl;
    }
    for (const auto& question: questions) {
        char answer;
        question.display();
        bool validAnswer = false;
        while (!validAnswer) {
            cout << "Enter answer or enter 0 to skip" << endl;
            cin >> answer;
            if (answer - 'a' < question.getOptions().size()) {
                validAnswer = true;
            }
            else {
                cout << "Cau tra loi khong hop le! Vui long nhap lai." << endl;
            }
        }
        if (answer != '0') {
            answers.push_back(answer);
        }
    }
}