# Sudoku Generator
A program that treats the logic-based, combinatorial, number placement puzzle game, [Sudoku](https://en.wikipedia.org/wiki/Sudoku), as a Constraint Satisfaction Problem (CSP) and consequently leverages solving algorithms Arc Consistency (AC-3) and Backtracking.

The user drives this program from their command line, where they can generate as many random Sudoku puzzles as desired and even peak at solutions. **Note** that each puzzle that is created is guaranteed to have a unique solution (see method for algorithm).

Additionally, the user can choose from the following three levels of Sudoku puzzle difficulties:
- ``Easy`` : 35 known cells
- ``Medium`` : 30 known cells
- ``Hard`` : 25 known cells
## Method
The method behind generating random Sudoku puzzles that are guaranteed to have a unique solution is as follows:
- Fill the first row with numbers 1 to 9 shuffled randomly
- Solve the remainder of the puzzle, using AC3 and Backtracking to get a complete Sudoku
- Repeatedly erase the numbers of currently assigned cells (picked at random) one at a time, until it is observed that to go any further would render the puzzle solvable by more than one solution
## Getting started
To compile the program, type the following in your terminal:
```bash
make
```
This creates an executable `sudogen`, which you want to execute with:
```bash
./sudogen
```
Then, you should be greeted with this:
```
Start Menu:
[1] Easy
[2] Medium
[3] Hard
[4] Quit

Which option would you like to take? 
```
From there, you can generate as many Sudoku puzzles as you like, as well as view their unique solutions should you elect to do so.

When you are finished, you can clean your directory of its `.o` files, including `sudogen` with the following:
```bash
make clean
```
## Examples
Below are some examples of output that is produced for each difficulty level.
### Easy
```
+---------+---------+---------+
| 2       | 5     6 |    7    |
|       7 | 3  2    | 6     4 |
|    5  4 | 9       |       1 |
+---------+---------+---------+
|    9    |         |    1    |
| 7     5 |    1  3 | 8  9    |
| 3     2 | 8       |    4    |
+---------+---------+---------+
|    7    | 4  3  8 |         |
|    6  8 |    9    | 5     7 |
|         |         | 4       |
+---------+---------+---------+
```
### Medium
```
+---------+---------+---------+
|         |       1 |    4    |
|       5 | 7       | 3       |
|    2  1 | 8       |       6 |
+---------+---------+---------+
|    9    |         |    1    |
| 6     3 |    1  9 | 7  8    |
| 2       | 3       |    5    |
+---------+---------+---------+
|    7    | 4  3  8 |         |
|    4  2 |    7    | 5     8 |
|         |         | 4       |
+---------+---------+---------+
```
### Hard
```
+---------+---------+---------+
|         |         |         |
|    6    |         |         |
|       1 | 8  6    | 9  7  5 |
+---------+---------+---------+
| 9     7 |       5 |    1    |
|         |    1    |         |
|         | 3       | 6       |
+---------+---------+---------+
|    7    | 4  3    |    6    |
| 2     8 |         |       3 |
| 1       |    9    |    8  7 |
+---------+---------+---------+
```
**Note** that it usually takes ~10 seconds to generate the hard puzzle.
# License
[MIT](https://choosealicense.com/licenses/mit/)
