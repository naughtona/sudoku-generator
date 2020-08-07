// Author: Andrew Naughton, 8/8/2020

#include "main.h"
#include "generator.h"

using std::cout;
using std::cin;
using std::endl;

void start_menu(std::string &preference) {
    cout << endl << "Start Menu:" << endl;
    cout << "[1] Easy" << endl
         << "[2] Medium" << endl 
         << "[3] Hard" << endl 
         << "[4] Quit" << endl << endl;
            
    cout << "Which option would you like to take? ";
    cin >> preference;
}


void solution_menu(bool &reveal) {
    bool valid_response = false;
    std::string verdict;

    while (!valid_response) {
        cout << "Show solution? [Y/N]: ";
        cin >> verdict;

        if (verdict == YES) {
            reveal = true;
            valid_response = true;
        } else if (verdict == NO) {
            reveal = false;
            valid_response = true;
            cout << endl;
        } else {
            cout << endl 
                 << "Incorrect input. Enter 'Y' or 'N' corresponding to your desired action."
                 << endl << endl;
        }
    }
}


void end_menu(bool &game_on, bool &continuous) {
    bool valid_response = false;
    std::string verdict;

    while (!valid_response) {
        cout << "[1] Give me another (same difficulty)" << endl
             << "[2] Back to start menu" << endl
             << "[3] Quit" << endl << endl;

        cout << "Which option would you like to take? ";
        cin >> verdict;

        if (verdict == ANOTHER) {
            continuous = true;
            valid_response = true;
        } else if (verdict == BACK) {
            continuous = false;
            valid_response = true;
        } else if (verdict == QUIT_2) {
            valid_response = true;
            game_on = false;
        } else {
            cout << endl 
                 << "Incorrect input. Enter the number corresponding to your desired action."
                 << endl << endl;
        }
    }
}


// Program begins here
int main() {
    std::string preference;
    bool game_on = true, continuous = false, reveal = false;

    while (game_on) {
        Generator generator;

        if (!continuous) start_menu(preference);

        if (preference == EASY)
            generator.generate_puzzle(EASY_COVERAGE);
        else if (preference == MEDIUM) 
            generator.generate_puzzle(MEDIUM_COVERAGE);
        else if (preference == HARD) 
            generator.generate_puzzle(HARD_COVERAGE);
        else if (preference == QUIT_1) {
            game_on = false;
            continue;
        } else {
            cout << endl 
                 << "Incorrect input. Enter the number corresponding to your desired action." 
                 << endl << endl;
            continue;
        }
        generator.display_puzzle();

        solution_menu(reveal);
        if (reveal) generator.display_solution();

        end_menu(game_on, continuous);
    }
    cout << endl << endl << "Bye!" << endl << endl;

    return 0;
}