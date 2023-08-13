#include <iostream>
#include <vector>
using namespace std;

class Question {
private:
    string question;
    vector<string> options;
    string answer;

public:
    Question(const string& q, const vector<string>& o, string a)
        : question(q), options(o), answer(a) {
    }

    string getQuestion() const {
        return question;
    }

    vector<string> getOptions() const {
        return options;
    }

    string getAnswer() const {
        return answer;
    }

    void display() const {
        char marker = 'a';
        cout << "Question: " << question << endl;
        for (const auto& option : options) {
            cout << marker << ". " << option << endl;
            marker++;
        }
    }
};