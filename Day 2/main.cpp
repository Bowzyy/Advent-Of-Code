
// ----------********** DAY 2 **********----------

#include <iostream>
#include <fstream>

int getTotalSum(const std::string &input);
int getTotalPower(const std::string &input);

int main() {
    getTotalSum("input.txt");
    getTotalPower("input.txt");
}

/*
--- Part One ---
 As you walk, the Elf shows you a small bag and some cubes which are either red, green, or blue.
 Each time you play this game, he will hide a secret number of cubes of each color in the bag,
 and your goal is to figure out information about the number of cubes.

To get information, once a bag has been loaded with cubes, the Elf will reach into the bag,
grab a handful of random cubes, show them to you, and then put them back in the bag.
He'll do this a few times per game.

You play several games and record the information from each game (your puzzle input).
Each game is listed with its ID number (like the 11 in Game 11: ...)
followed by a semicolon-separated list of subsets of cubes that were revealed from the bag
(like 3 red, 5 green, 4 blue).

For example, the record of a few games might look like this:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1, three sets of cubes are revealed from the bag (and then put back again).
The first set is 3 blue cubes and 4 red cubes; the second set is 1 red cube, 2 green cubes,
and 6 blue cubes; the third set is only 2 green cubes.

The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes,
13 green cubes, and 14 blue cubes?

In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration.
However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once;
similarly, game 4 would also have been impossible because the Elf showed you 15 blue cubes at once.
If you add up the IDs of the games that would have been possible, you get 8.

Determine which games would have been possible if the bag had been loaded with only 12 red cubes,
13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?

*/
int getTotalSum(const std::string &input) {
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
        for (char &c: line) {
            if (isdigit(c)) {
                tempstring += c;
            }
            if (!isdigit(c)) {
                if (!tempstring.empty()) {
                    values[n] = stoi(tempstring);       // assign number to array
                    n++;
                }
                if (c == 'r') {
                    colours[n] = 'r';
                }
                if (c == 'n') {
                    colours[n] = 'g';               // assign colour to array
                }
                if (c == 'b') {
                    colours[n] = 'b';
                }
                tempstring = "";
            }
        }

        if (!tempstring.empty()) {
            values[n] = stoi(tempstring);
        }

        // check if cubes are over the limit
        for (int i = 1; i < 24; i++) {
            if ((values[i] > 12 && colours[i + 1] == 'r') ||
                (values[i] > 13 && colours[i + 1] == 'g') ||
                (values[i] > 14 && colours[i + 1] == 'b')) {
                possible = false;
            }
        }

        // sum up value of possible games
        if (possible) {
            total += values[0];
        }

        // reset values
        std::fill_n(values, 25, 0);
        std::fill_n(colours, 25, 'x');
        possible = true;
        n = 0;
        game++;
    }

    std::cout << "total: " << total << std::endl;

    return total;
}

/*
--- Part Two ---
The Elf says they've stopped producing snow because they aren't getting any water!
He isn't sure why the water stopped; however, he can show you how to get to the water source
to check it out for yourself. It's just up ahead!

As you continue your walk, the Elf poses a second question: in each game you played, what is the fewest number
of cubes of each color that could have been in the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes.
If any color had even one fewer cube, the game would have been impossible.
Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
Game 4 required at least 14 red, 3 green, and 15 blue cubes.
Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.

The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together.
The power of the minimum set of cubes in game 1 is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively.
Adding up these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present.
What is the sum of the power of these sets?
*/
int getTotalPower(const std::string &input) {
    std::string line;
    std::ifstream file(input);
    std::string tempstring;
    int values[25];
    char colours[25];
    int n = 0;
    int total = 0;
    int game = 1;

    int current_red = 0;
    int current_green = 0;
    int current_blue = 0;

    while (std::getline(file, line)) {
        for (char &c: line) {
            if (isdigit(c)) {
                tempstring += c;
            }
            if (!isdigit(c)) {
                if (!tempstring.empty()) {
                    values[n] = stoi(tempstring);   // store number in array
                    n++;
                }
                if (c == 'r') {
                    colours[n] = 'r';
                }
                if (c == 'n') {
                    colours[n] = 'g';               // store corresponding colour in array
                }
                if (c == 'b') {
                    colours[n] = 'b';
                }
                tempstring = "";
            }
        }

        if (!tempstring.empty()) {
            values[n] = stoi(tempstring);
        }

        // check highest number
        for (int i = 1; i < 24; i++) {
            if (values[i] > current_red && colours[i + 1] == 'r') {
                current_red = values[i];
            }
            if (values[i] > current_green && colours[i + 1] == 'g') {
                current_green = values[i];
            }
            if (values[i] > current_blue && colours[i + 1] == 'b') {
                current_blue = values[i];
            }
        }

        // calculate total
        total += current_red * current_green * current_blue;

        // reset values
        std::fill_n(values, 25, 0);
        std::fill_n(colours, 25, 'x');
        current_red = 0;
        current_green = 0;
        current_blue = 0;
        n = 0;
        game++;
    }

    std::cout << "total: " << total << std::endl;

    return total;
}
