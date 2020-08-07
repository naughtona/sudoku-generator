// Author: Andrew Naughton, 8/8/2020

#include "generator.h"
#include "sudoku.h"

using std::cout;
using std::cin;
using std::endl;


// Default Constructor
Generator::Generator() {
    puzzle = new Sudoku();

    generate_complete();

    solution = new Sudoku(*puzzle);
}




// Private methods
bool Generator::ac3() {
    std::vector<neighbourpair_t> np_queue;

    for (int var1 = 0; var1 < N_2; var1++) {
        for (int var2 : puzzle->get_neighbours(var1)) {
            neighbourpair_t np(var1, var2);
            np_queue.push_back(np);
        }
    }
    
    while (!np_queue.empty()) {
        neighbourpair_t np1 = *np_queue.begin();
        np_queue.erase(np_queue.begin());

        bool modified = remove_inconsistent_values(np1);

        if (modified) {
            if (puzzle->curr_domain_empty(np1.neighbour1))
                return false;
            for (int Xk : puzzle->get_neighbours(np1.neighbour1)) {
                if (Xk != np1.neighbour2) {
                    neighbourpair_t np2(Xk, np1.neighbour1);
                    np_queue.push_back(np2);
                }
            }
        }
    }
    return true;
}


bool Generator::remove_inconsistent_values(neighbourpair_t np) {
    bool modified = false;

    for (int val1 : puzzle->get_curr_domain(np.neighbour1)) {
        bool conflict = true;

        for (int val2 : puzzle->get_curr_domain(np.neighbour2)) {
            if (puzzle->satisfies_constraints(val1, val2)) {
                conflict = false;
                break;
            }
        }
        if (conflict) {
            puzzle->prune(np.neighbour1, val1);
            modified = true;
        }
    }
    return modified;
}


bool Generator::different_assignments(std::map<int, int> assignments) {
    for (auto a1 : puzzle->get_assignments()) {
        auto a2 = assignments.find(a1.first);

        if (a1.second != a2->second)
            return true;
    }
    return false;
}


bool Generator::backtracking() {
    if (puzzle->goal_test())
        return true;

    int cell = puzzle->select_unassigned_cell();

    for (int val : puzzle->get_curr_domain(cell)) {
        if (puzzle->n_conflicts(cell, val) == 0) {
            puzzle->assign(cell, val);

            std::vector<removal_t> removals = puzzle->suppose(cell, val);

            if (backtracking())
                return true;

            puzzle->restore(removals);
        }
    }
    puzzle->unassign(cell);
    return false;
}


bool Generator::backtracking(std::map<int, int> assignments) {
    if (puzzle->goal_test()) {
        if (different_assignments(assignments))
            return true;

        return false;
    }

    int cell = puzzle->select_unassigned_cell();

    for (int val : puzzle->get_curr_domain(cell)) {
        if (puzzle->n_conflicts(cell, val) == 0) {
            puzzle->assign(cell, val);

            std::vector<removal_t> removals = puzzle->suppose(cell, val);

            if (backtracking(assignments))
                return true;

            puzzle->restore(removals);
        }
    }
    puzzle->unassign(cell);
    return false;
}


bool Generator::reducible() {
    for (auto item : puzzle->get_assignments()) {
        int var = item.first;
        int val_removed = item.second;
        puzzle->unassign(var);
        puzzle->clear_curr_domain(var);
        puzzle->insert_curr_domain(var, DOMAIN);

        if (!multiple_solutions()) return true;

        puzzle->assign(var, val_removed);
        puzzle->clear_curr_domain(var);
        puzzle->insert_curr_domain(var, val_removed);
    }

    return false;
}


int Generator::multiple_solutions() {
    int multiple = false;
    Sudoku tmp_puzzle(*puzzle);

    if (ac3()) {
        puzzle->infer_assignment();

        if (backtracking(puzzle->get_assignments())) 
            multiple = true;
    }
    puzzle->copy_sudoku(tmp_puzzle);

    return multiple;
}




// Public methods
void Generator::generate_complete() {
    bool found = false;

    while (!found) {
        puzzle->clear_sudoku();
        puzzle->randomize_grid();

        if (ac3()) {
            puzzle->infer_assignment();

            if (backtracking()) found = true;
        }
    }
}


void Generator::display_puzzle() {
    puzzle->print_grid();
}


void Generator::display_solution() {
    solution->print_grid();
}


void Generator::generate_puzzle(unsigned requisite_coverage) {
    cout << endl << "Generating... won't be long :)" << endl;

    while (puzzle->get_n_assignments() > requisite_coverage) {
        int var = puzzle->select_random_assigned_cell();
        int val_removed = puzzle->get_assignment(var);
        puzzle->unassign(var);
        puzzle->clear_curr_domain(var);
        puzzle->insert_curr_domain(var, DOMAIN);

        if (multiple_solutions()) {
            puzzle->assign(var, val_removed);
            puzzle->clear_curr_domain(var);
            puzzle->insert_curr_domain(var, val_removed);

            if (!reducible()) break;
        }
    }
}
