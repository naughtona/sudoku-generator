// Author: Andrew Naughton, 8/8/2020

#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <map>
#include <stdbool.h>
#include <vector>

typedef struct neighbourpair_t {
    int neighbour1, neighbour2;

    neighbourpair_t(int neighbour1, int neighbour2) {
        this->neighbour1 = neighbour1;
        this->neighbour2 = neighbour2;
    }

} neighbourpair_t;


class Sudoku;

class Generator {
    private:
        Sudoku *puzzle;
        Sudoku *solution;

        bool ac3();
        bool remove_inconsistent_values(neighbourpair_t np);
        bool different_assignments(std::map<int, int> assignments);
        bool backtracking();
        bool backtracking(std::map<int, int> assignments);
        bool reducible();

        int multiple_solutions();


    public:
        Generator();

        void generate_complete();
        void display_puzzle();
        void display_solution();
        void generate_puzzle(unsigned requisite_coverage);
};

#endif