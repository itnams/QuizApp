#include <iostream>
#include <vector>

class Question {
private:
    std::string question;
    std::vector<std::string> options;
    std::string answer;

public:
    // Constructor
    Question(const std::string& q, const std::vector<std::string>& o, std::string a)
        : question(q), options(o), answer(a) {
    }

    // Getter methods
    std::string getQuestion() const {
        return question;
    }

    std::vector<std::string> getOptions() const {
        return options;
    }

    std::string getAnswer() const {
        return answer;
    }

    // Display question and options
    void display() const {
        std::cout << "Question: " << question << std::endl;
        std::cout << "Options:" << std::endl;
        for (const auto& option : options) {
            std::cout << option << std::endl;
        }
    }
};