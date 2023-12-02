#include <iostream>
#include <fstream>

int getTotalSum(const std::string& input);

int main() {
    getTotalSum("input.txt");
}

int getTotalSum(const std::string& input){
    std::string line;
    std::ifstream file(input);
    std::string tempstring;
    int values[25];
    char colours[25];
    int n = 0;
    bool possible = true;
    int total = 0;
    int game = 1;

    while (std::getline(file, line)) {
        std::cout << "Game: " << game << std::endl;
        for (char& c : line) {
            if (isdigit(c)) {
                tempstring += c;
            }
            if (!isdigit(c)) {
                if (!tempstring.empty()) {
                    values[n] = stoi(tempstring);
                    //std::cout << values[n] << std::endl;
                    n++;
                }
                if(c == 'r'){
                    //std::cout << "red" << std:: endl;
                    colours[n] = 'r';
                }
                if(c == 'n'){
                    //std::cout << "green" << std:: endl;
                    colours[n] = 'g';
                }
                if(c == 'b'){
                    //std::cout << "blue" << std:: endl;
                    colours[n] = 'b';
                }
                tempstring = "";
            }
        }

        if (!tempstring.empty()) {
            values[n] = stoi(tempstring);
            n++;
        }

        for (int i = 1; i < 24; i++) {
            std::cout << values[i] << ", ";
            std::cout << colours[i + 1] << std::endl;
            if ((values[i] > 12 && colours[i + 1] == 'r') ||
                (values[i] > 13 && colours[i + 1] == 'g') ||
                (values[i] > 14 && colours[i + 1] == 'b')) {
                possible = false;
            }
        }

        if (possible) {
            total += values[0];
            std::cout << "possible, ";
            std::cout << "total: " << total << std::endl;
        } else {
            std::cout << "not possible, ";
            std::cout << "total: " << total << std::endl;
        }

        std::fill_n(values, 25, 0);
        std::fill_n(colours, 25, 'x');
        possible = true;
        n = 0;
        game++;
    }

    std::cout << "total: " << total << std::endl;

    return total;
}
