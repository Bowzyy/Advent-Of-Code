
// ------------********** DAY 1 **********----------

#include <iostream>
#include <fstream>

int getNumberValue(const std::string& input);
int getStringValue(const std::string& input);


int main() {
    getNumberValue("input.txt");
    getStringValue("input.txt");
    return 0;
}

/*
--- Part One ---
The newly-improved calibration document consists of lines of text;
each line originally contained a specific calibration value that the Elves now need to recover.
On each line, the calibration value can be found by combining the first digit and the last digit (in that order)
to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet

In this example, the calibration values of these four lines are 12, 38, 15, and 77.
Adding these together produces 142.
*/

int getNumberValue(const std::string& input){
    std::string line;
    std::ifstream file(input);
    std::string tempstring;
    std::string twodigitnum;

    int total = 0;

    // extract the numbers from the strings
    while(std::getline(file, line)){
        for(char& c : line) {
            if(isdigit(c)){         // check if number in string
                tempstring += c;    // append the number to the temporary string
            }
        }
        twodigitnum = tempstring.front();               // add the first number
        twodigitnum.push_back( tempstring.back());  // add the last number
        total += stoi(twodigitnum);     // convert to int
        tempstring = "";
    }

    std::cout << total << std::endl;
    return total;
}


/*
--- Part Two ---
Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters:
    one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen
 
In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.
*/

int getStringValue(const std::string& input){
    std::string wordsToSearch[] = {"one", "1", "two", "2", "three", "3",
                                   "four", "4","five","5", "six", "6",
                                   "seven", "7","eight", "8","nine", "9"};

    std::ifstream file(input);

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string tempstring;
    std::string twodigitnum;

    int total = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::pair<size_t, std::string > > foundWords;

        for (const auto &word : wordsToSearch) {
            size_t found = line.find(word);

            while (found != std::string::npos) {
                foundWords.push_back(std::make_pair(found, word));
                found = line.find(word, found + 1);
            }
        }

        // sort based on position in line
        std::sort(foundWords.begin(), foundWords.end());

        for (const auto &pair : foundWords) {
            const auto &word = pair.second;

            if (word == "one") {
                tempstring += "1";
            } else if (word == "two") {
                tempstring += "2";
            } else if (word == "three") {
                tempstring += "3";
            } else if (word == "four") {
                tempstring += "4";
            } else if (word == "five") {
                tempstring += "5";
            } else if (word == "six") {
                tempstring += "6";
            } else if (word == "seven") {
                tempstring += "7";
            } else if (word == "eight") {
                tempstring += "8";
            } else if (word == "nine") {
                tempstring += "9";
            } else if(word == "1"){
                tempstring += "1";
            } else if(word == "2"){
                tempstring += "2";
            } else if(word == "3"){
                tempstring += "3";
            } else if(word == "4"){
                tempstring += "4";
            } else if(word == "5"){
                tempstring += "5";
            } else if(word == "6"){
                tempstring += "6";
            } else if(word == "7"){
                tempstring += "7";
            } else if(word == "8"){
                tempstring += "8";
            } else if(word == "9"){
                tempstring += "9";
            }
        }

        twodigitnum = tempstring.front();               // add the first number
        twodigitnum.push_back( tempstring.back());  // add the last number
        total += stoi(twodigitnum);     // convert to int and add to total

        tempstring = "";
    }

    std::cout << total << std::endl;
    return total;
}
