#include "Algo.h"

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
