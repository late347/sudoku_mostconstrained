#include "Board.h"

bool Board::isLegalMove(const Cell& cell, const int move) const
{

    // legalMove must be checked by board because each cell legality is
    // affected by box cells, row cells and column cells


    const int R = cell.rowIdx;
    const int C = cell.colIdx;

    // iterate to sweep the rows and columns to see if legally unique
    for (auto c = 0; c < this->numberOfColumns(); c++)
    {
        if (array[R][c].theValue == move && C != c) {
            return false;
        }
    }

    for (auto r = 0; r < this->numberOfRows(); r++)
    {
        if (array[r][C].theValue == move && R != r) {
            return false;
        }
    }

    // iterate to sweep the sudoku box 
    const int boxCols = cell.colIdx / (3);
    const int boxRows = cell.rowIdx / (3);

    for (int i = boxRows * 3; i < boxRows * 3 + 3; i++)
    {
        for (int j = boxCols * 3; j < boxCols * 3 + 3; j++)
        {
            if (array[i][j].theValue == move && (R != i && C != j))
            {
                return false;
            }
        }
    }

    return true;

}

void Board::printBoard() const
{

    using namespace std;

    auto rows = numberOfRows();
    auto cols = numberOfColumns();
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {

            if ((c) % 3 == 0)
            {
                char tab = 9;
                cout << tab;
            }

            cout << " " << array[r][c];
        }
        cout << endl;
        //print extra newline for every third row to cleanly print the boxes NOTE!: uses magic value 3 for sudoku
        if ((r + 1) % 3 == 0) {
            cout << endl;
        }
    }

}

void Board::initialize(int cluesBoard[][SUDOKU_SIZE], int sudokuRows, int sudokuCols)
{

    if (sudokuRows != sudokuCols || (sudokuCols != 9) || (sudokuRows != 9)) // keep condition for now, because elsewhere in codes there is magic values still
    {
        throw std::logic_error("invalid sudoku, rows and cols unequal!");
    }

    for (int r = 0; r < sudokuRows; r++)
    {
        for (int c = 0; c < sudokuCols; c++)
        {
            auto given = cluesBoard[r][c];
            bool is_clue = (given != 0) ? true : false;
            this->array[r][c] = Cell(r, c, is_clue, cluesBoard[r][c]);
        }
    }

}

bool Board::isSolved() const
{

    for (int i = 0; i < this->numberOfRows(); i++)
    {
        for (int j = 0; j < this->numberOfColumns(); j++)
        {
            if (this->array[i][j].theValue == 0) {
                return false;
            }
        }
    }
    return true;

}

bool Board::isLegalMove(const int row, const int col, const int thevalue) const
{
    // legalMove must be checked by board because each cell legality is
// affected by box cells, row cells and column cells

        // check if current cell value was legal move in sudoku


    const auto cellvalue = thevalue;

    // iterate to sweep the rows and columns to see if legally unique
    for (auto c = 0; c < this->numberOfColumns(); c++)
    {
        // if its duplicate its illegal
        if (array[row][c].theValue == cellvalue && col != c) {
            return false;
        }
    }

    for (auto r = 0; r < this->numberOfRows(); r++)
    {
        // if its duplicate its illegal
        if (array[r][col].theValue == cellvalue && row != r) {
            return false;
        }
    }

    // iterate to sweep and check the sudoku box 
    int boxCols = col / (3);
    int boxRows = row / (3);

    for (int i = boxRows * 3; i < boxRows * 3 + 3; i++)
    {
        for (int j = boxCols * 3; j < boxCols * 3 + 3; j++)
        {
            if (array[i][j].theValue == cellvalue && (row != i && col != j))
            {
                return false;
            }
        }
    }

    return true;

}
