// Author: Andrew Naughton, 8/8/2020

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <ctime>
#include <map>
#include <stdbool.h>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>

#define N 9
#define N_2 81
#define N_ROOT 3
#define DOMAIN {1,2,3,4,5,6,7,8,9}
#define NBRS 20
#define PADDING 3
#define BORDER "|"
#define SPACE " "
#define ROW_SEPARATOR "+---------+---------+---------+"


typedef struct removal_t {
    int var, assignment;

    removal_t(int var, int assignment) {
        this->var = var;
        this->assignment = assignment;
    }

} removal_t;



class Sudoku {
    private:
        std::vector<std::unordered_set<int>> neighbours{N_2, {std::unordered_set<int>(NBRS)}};
        std::vector<std::unordered_set<int>> curr_domains{N_2, {std::unordered_set<int>(N)}};
        std::map<int, int> assignments;

        void add_neighbours_and_domains();

    public:
        Sudoku();
        Sudoku(const Sudoku &original);

        void clear_sudoku();
        void copy_sudoku(const Sudoku &original);
        void assign(int var, int val) { assignments[var] = val; };
        void unassign(int var) { assignments.erase(var); };
        void restore(std::vector<removal_t> removals);
        void infer_assignment();
        void prune(int var, int val);
        void clear_assignments() { assignments.clear(); };
        void clear_curr_domain(int var) { curr_domains[var].clear(); };
        void insert_curr_domain(int var, int val) { curr_domains[var].insert(val); };
        void insert_curr_domain(int var, std::vector<int> vals) { curr_domains[var].insert(vals.begin(), vals.end()); };
        void randomize_grid();
        void print_grid();

        int get_assignment(int var);
        int n_conflicts(int var1, int val1);
        int select_random_assigned_cell();
        int select_unassigned_cell();

        unsigned get_n_assignments() { return assignments.size(); };

        bool satisfies_constraints(int val1, int val2) { return val1 != val2; };
        bool goal_test() { return assignments.size() == N_2; };
        bool curr_domain_empty(int var) { return curr_domains[var].empty(); };

        std::vector<removal_t> suppose(int var, int val);
        
        std::unordered_set<int> get_neighbours(int var);
        std::unordered_set<int> get_curr_domain(int var);

        std::map<int, int> get_assignments();
};

#endif