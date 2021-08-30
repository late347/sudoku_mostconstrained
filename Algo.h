#pragma once

#include "Board.h"
#include "Cell.h"
#include <algorithm>
#include <stack>

// parameters is the board
// returns the solution by reference as solved board
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
        int valuesAmount = values.size();
        int r = cell.rowIdx, c = cell.colIdx;
        // recursively try possible moves
        for (auto&& pair : values)
        {
            auto move = pair.second;
            Board tempboard = board;
            tempboard.array[r][c].guess(move);
            if (solve(tempboard, resultBoard))
            {
                return true;
            }
        }
        return false;
    }
}

