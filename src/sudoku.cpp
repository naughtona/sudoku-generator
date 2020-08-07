// Author: Andrew Naughton, 8/8/2020

#include "sudoku.h"

using std::cout;
using std::cin;
using std::endl;


// Default Constructor
Sudoku::Sudoku() {
    add_neighbours_and_domains();
}

// Copy Constructor
Sudoku::Sudoku(const Sudoku &original) {
    copy_sudoku(original);
}


// Private methods
void Sudoku::add_neighbours_and_domains() {
    for (int i = 0; i < N_2; i++) {
        neighbours[i].clear();
        curr_domains[i].insert(DOMAIN);

        int row = i / N;
        int col = i % N;
        
        // add column neighbours
        for (int j = col; j <= (N - 1) * N + col; j += N) {
            if (j == i) continue;
            neighbours[i].insert(j);
        }

        // add row neighbours
        for (int j = row * N; j < (row * N) + N; j++) {
            if (j == i) continue;
            neighbours[i].insert(j);
        }

        // add district neighbours
        int start_r = (row / N_ROOT) * N_ROOT;
        int start_c = (col / N_ROOT) * N_ROOT;

        for (int j = start_r; j < (start_r + N_ROOT); j++) {
            for (int k = start_c; k < (start_c + N_ROOT); k++) {
                int var = (j * N) + k;
                if (var == i) continue;
                neighbours[i].insert(var);
            }
        }
    }
}



// Public methods
void Sudoku::clear_sudoku() {
    for (int i = 0; i < N_2; i++) {
        curr_domains[i].clear();
        curr_domains[i].insert(DOMAIN);
    }
    clear_assignments();
}


void Sudoku::copy_sudoku(const Sudoku &original) {
    for (int i = 0; i < N_2; i++) {
        neighbours[i].clear();
        neighbours[i].insert(original.neighbours[i].begin(), original.neighbours[i].end());

        curr_domains[i].clear();
        curr_domains[i].insert(original.curr_domains[i].begin(), original.curr_domains[i].end());
    }

    assignments.clear();
    for (auto item : original.assignments)
        assignments[item.first] = item.second;
}


void Sudoku::restore(std::vector<removal_t> removals) {
    for (removal_t r : removals)
        curr_domains[r.var].insert(r.assignment);
}


void Sudoku::infer_assignment() {
    for (int i = 0; i < N_2; i++) {
        if (curr_domains[i].size() == 1) 
            assignments[i] = *curr_domains[i].begin();
    }
}


void Sudoku::prune(int var, int val) {
    auto item = curr_domains[var].find(val);

    if (item != curr_domains[var].end()) 
        curr_domains[var].erase(item);
}


void Sudoku::randomize_grid() {
    unsigned seed = time(NULL);
    std::vector<int> values = DOMAIN;
    shuffle(values.begin(), values.end(), std::default_random_engine(seed));

    for (int i = 0; i < N; i++) {
        auto value = values.begin();

        assign(i, *value);
        clear_curr_domain(i);
        insert_curr_domain(i, *value);

        values.erase(value);
    }
}


void Sudoku::print_grid() {
    cout << endl;
    for (int i = 0; i < N; i++) {
        if (i % N_ROOT == 0) cout << ROW_SEPARATOR << endl;

        for (int j = 0; j < N; j++) {
            if (j % N_ROOT == 0) cout << BORDER;
            auto item = assignments.find(i * N + j);

            cout << SPACE;
            if (item != assignments.end()) cout << item->second;
            else cout << " ";
            cout << SPACE;
        }
        cout << BORDER << endl;
    }
    cout << ROW_SEPARATOR << endl << endl;
}


int Sudoku::get_assignment(int var) {
    auto item = assignments.find(var);

    if (item != assignments.end()) 
        return item->second;
    
    return -1;
}


int Sudoku::n_conflicts(int var1, int val1) {
    int n = 0;
    for (int var2 : neighbours[var1]) {
        auto item2 = assignments.find(var2);

        if (item2 != assignments.end() && !(satisfies_constraints(val1, item2->second)))
            n++;
    }
    return n;
}


int Sudoku::select_random_assigned_cell() {
    int cell = rand() % N_2;

    while (curr_domains[cell].size() > 1)
        cell = rand() % N_2;
    
    return cell;
}


int Sudoku::select_unassigned_cell() {
    int i = 0;
    while (i < N_2) {
        auto item = assignments.find(i);
        if (item == assignments.end())
            break;

        i++;
    }
    return i;
}


std::vector<removal_t> Sudoku::suppose(int var, int val) {
    std::vector<removal_t> removals;

    for (int a : curr_domains[var]) {
        if (a != val) {
            removal_t rmvl(var, a);
            removals.push_back(rmvl);
        }
    }
    curr_domains[var].clear();
    curr_domains[var].insert(val);

    return removals;
}


std::unordered_set<int> Sudoku::get_curr_domain(int var) {
    std::unordered_set<int> curr_domains_copy(curr_domains[var]);
    return curr_domains_copy;
}


std::unordered_set<int> Sudoku::get_neighbours(int var) {
    std::unordered_set<int> neighbours_copy(neighbours[var]);
    return neighbours_copy;
}


std::map<int, int> Sudoku::get_assignments() {
    std::map<int, int> assignments_copy(assignments);
    return assignments_copy;
}
