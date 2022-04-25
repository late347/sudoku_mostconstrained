#pragma once

#include "Board.h"
#include "Cell.h"
#include <algorithm>
#include <stack>

// parameters is the board
// returns the solution by reference as solved board
// uses recursion and pass-by-value and RAII for the board solving
// therefore, we can skip any board-undo operations on the board when we backtrack
// from wrong sudoku guesses.
// 
// this approach, creates more memory need, but its simpler to program
// stack usage will become higher though, because for every recursion it has a board.
bool solve(Board board, Board& resultBoard)
{
    if (board.isSolved())
    {
        using namespace std;
        Board solution = board;
        resultBoard = solution;
        cout << endl
            << "SOLUTION BOARD is as follows!!!" << endl;
        resultBoard.printBoard();
        cout << endl;
        return true;
    }
    else
    {
        // get most optimal cell to guess moves into to prune off bad guesses
        Cell cell = board.getMostConstrainedEmpty();
        // get possible moves
        auto values = cell.getPossibleValues();
        const int r = cell.rowIdx;
        const int c = cell.colIdx;
        // recursively try possible moves
        for (auto&& pair : values)
        {
            const auto move = pair.second;
            board.array[r][c].guess(move);
            if (solve(board, resultBoard))
            {
                return true;
            }
        }
        return false;
    }
}

