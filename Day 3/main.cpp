#include <iostream>
#include <fstream>
#include <string>

int getAdjacent(std::string input);
int getTwoPart(std::string input);

int main() {
    getAdjacent("input.txt");
}

int getAdjacent(std::string input){
    char symbols[140][140];
    std::string tempstring;
    int total = 0;
    bool number_added;

    std::string line;
    std::ifstream file(input);


    // Read input from file
    for (int i = 0; i < 140; i++) {
        if (!std::getline(file, line)) {
            std::cerr << "Error reading line from file." << std::endl;
        }

        for (int j = 0; j < 140 && j < line.length(); j++) {
            char c = line[j];
            symbols[i][j] = c;
        }
    }

    // Check surrounding tiles
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            if (isdigit(symbols[i][j])) {
                if(!number_added){
                    tempstring += symbols[i][j];
                }
            }
            if(symbols[i][j] == '.'){
                tempstring = "";
                number_added = false;
            }

            bool is_adjacent = false;
            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x >= 0 && x < 140 && y >= 0 && y < 140 && !(x == i && y == j)) {
                        if (symbols[x][y] == '@') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '$') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '*') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '=') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '&') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '/') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '-') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '#') {
                            is_adjacent = true;
                        }
                        if (symbols[x][y] == '%') {
                            is_adjacent = true;
                        }
                    }
                }
            }

            if (is_adjacent && !tempstring.empty()) {
                int temp_j = j + 1;
                while (temp_j < 140 && isdigit(symbols[i][temp_j])) {
                    tempstring += symbols[i][temp_j];
                    temp_j++;
                }
                number_added = true;
                total += std::stoi(tempstring);
                tempstring = "";
            }
        }
    }

    std::cout << "total: " << total << std::endl;
    return total;
}