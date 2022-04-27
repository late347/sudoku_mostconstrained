// sudoku_mostconstrained.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Board.h"
#include "Cell.h"
#include "Algo.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>



int main()
{
    std::cout << "Hello World!\n";

    namespace chr = std::chrono;
    using namespace std;

    int sudoku_easy_1[9][9]
    { {0, 7, 2,      9, 0, 1,        4, 0, 6},
     {9, 0, 1,      8, 0, 6,        0, 0, 0},
     {0, 5, 0,      7, 3, 0,        1, 0, 0},

     {0, 0, 6,      5, 0, 0,        9, 0, 4},
     {0, 0, 0,      0, 4, 9,        0, 5, 7},
     {4, 0, 0,      3, 0, 0,        0, 0, 2},

     {2, 0, 0,      0, 8, 0,        0, 6, 0},
     {0, 0, 0,      2, 0, 0,        0, 9, 5},
     {5, 0, 7,      0, 0, 3,        0, 0, 8} };

    int sudoku_hard_118[9][9]
    { {0, 0, 0,      0, 0, 0,        7, 0, 1},
     {6, 0, 4,      7, 0, 5,        0, 0, 0},
     {0, 0, 2,      0, 1, 0,        0, 0, 0},

     {0, 0, 0,      0, 0, 0,        3, 7, 0},
     {7, 0, 0,      1, 0, 0,        0, 0, 2},
     {0, 0, 0,      0, 8, 0,        0, 0, 6},

     {0, 0, 1,      8, 9, 0,        0, 0, 0},
     {0, 9, 0,      3, 0, 0,        5, 0, 0},
     {4, 3, 7,      2, 0, 1,        0, 0, 0} };

    int sudoku_hard_skiena[9][9]
    { {0, 0, 0,      0, 0, 0,        0, 1, 2},
     {0, 0, 0,      0, 3, 5,        0, 0, 0},
     {0, 0, 0,      6, 0, 0,        0, 7, 0},

     {7, 0, 0,      0, 0, 0,        3, 0, 0},
     {0, 0, 0,      4, 0, 0,        8, 0, 0},
     {1, 0, 0,      0, 0, 0,        0, 0, 0},

     {0, 0, 0,      1, 2, 0,        0, 0, 0},
     {0, 8, 0,      0, 0, 0,        0, 4, 0},
     {0, 5, 0,      0, 0, 0,        6, 0, 0} };


    int sudoku_hard_hardest_sudoku[9][9]
    { {8, 0, 0,      0, 0, 0,        0, 0, 0},
     {0, 0, 3,      6, 0, 0,        0, 0, 0},
     {0, 7, 0,      0, 9, 0,        2, 0, 0},

     {0, 5, 0,      0, 0, 7,        0, 0, 0},
     {0, 0, 0,      0, 4, 5,        7, 0, 0},
     {0, 0, 0,      1, 0, 0,        0, 3, 0},

     {0, 0, 1,      0, 0, 0,        0, 6, 8},
     {0, 0, 8,      5, 0, 0,        0, 1, 0},
     {0, 9, 0,      0, 0, 0,        4, 0, 0} };

    Board realBoard(SUDOKU_SIZE, SUDOKU_SIZE);
    realBoard.initialize(sudoku_hard_skiena, 9, 9);

    realBoard.printBoard();

    cout << endl;
    Board solutionboard = realBoard;
    cout << "solving the sudoku... please wait..." << endl;
    auto start = chr::high_resolution_clock::now();

    // return solution by reference to solutionboard
    solve(realBoard, solutionboard);
    auto stop = chr::high_resolution_clock::now();
    auto lasted = chr::duration_cast<chr::microseconds>(stop - start);
    cout << endl << "solving lasted... " << lasted.count() << " microseconds" << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
