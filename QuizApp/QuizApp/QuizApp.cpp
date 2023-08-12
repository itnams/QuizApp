#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Question.cpp"
#include <sstream>

std::vector<std::string> stringToVector(const std::string& str) {
    std::vector<std::string> vec;
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
        vec.push_back(word);
    }

    return vec;
}
int main()
{
    std::list<Question> questions;
    std::ifstream file("files/input.txt"); // Đường dẫn đến file txt

    if (file.is_open()) {
        std::string line;
        std::list<std::string> lines; // Danh sách dòng

        while (std::getline(file, line)) {
            lines.push_back(line); // Thêm dòng vào danh sách
        }

        file.close();

        int index = 0;
        for (const auto& line : lines) {
            if (line == "5" && index != 0) {
                auto itQuestion = std::next(lines.begin(), index - 1);
                auto itOptions = std::next(lines.begin(), index + 1);
                auto itAnswer = std::next(lines.begin(), index + 2);
                std::string question = *itQuestion;
                std::vector<std::string> options = stringToVector(*itOptions);
                std::string answer = *itAnswer;
                Question questionItem(question, options, answer);
                questions.push_back(questionItem);
            }
            index++;
        }
    }
    else {
        std::cout << "Không thể mở file." << std::endl;
    }

    std::cout << "Hello World!\n";
}