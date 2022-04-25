#pragma once

#include <vector>
#include <array>
#include "Cell.h"
#include "Sudoku_includes.h"
#include <exception>
#include <iomanip>

class Board
{
public:
    Board(int rows, int cols) : array(rows)
    {
        for (auto&& row : array)
        {
            row.resize(cols);
        }
    }

    Board(std::vector<std::vector<Cell>> v) : array{ v }
    {
    }

    Board(std::vector<std::vector<Cell>>&& v) : array{ std::move(v) }
    {
    }

    const std::vector<Cell>& operator[](int row) const
    {
        return array[row];
    }
    std::vector<Cell>& operator[](int row)
    {
        return array[row];
    }
    int numberOfRows() const { return array.size(); }
    int numberOfColumns() const { return numberOfRows() ? array[0].size() : 0; }
    void printBoard() const
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

    void initialize(int cluesBoard[][SUDOKU_SIZE], int sudokuRows = SUDOKU_SIZE, int sudokuCols = SUDOKU_SIZE)
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

    bool isSolved()
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

    // legalMove must be checked by board because each cell legality is
    // affected by box cells, row cells and column cells
    bool isLegalMove(const int row, const int col, const int thevalue)
    {
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

    // legalMove must be checked by board because each cell legality is
    // affected by box cells, row cells and column cells
    bool isLegalMove(const Cell& cell, const int move)
    {

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

    // gets empty cells and returns the cell which has least possibleMoves available
    // in best case a cell only would have 1 possibleMove  so that it is certain that is the cell value
    Cell getMostConstrainedEmpty()
    {
        // get empty cells together from board
        std::vector<Cell> empties;

        for (int r = 0; r < this->numberOfRows(); r++)
        {
            for (int c = 0; c < this->numberOfColumns(); c++)
            {
                if (array[r][c].theValue == 0)
                {
                    Cell e = array[r][c];
                    empties.push_back(e);
                }
            }
        }
        if (empties.empty()) {
            throw std::logic_error("unexpectedly called getMostConstrainedEmpty() cannot return an empty cell from the board!!!??? think again about the algo\n");
        }

        // for all cells in empties must see what the possibleMoves are for those emptycells
        // they might have been updated (most likely were)
        // only board class can do the update because all cells affect all cells's possibleMoves
        // and board knows himself and his cells
        for (auto&& eCell : empties)
        {
            for (int i = 1; i <= SUDOKU_SIZE; i++)
            {
                if (this->isLegalMove(eCell, i))
                {
                    eCell.setPossibleMove(i);
                }
            }
        }

        // we should always get a real empty cell into here
        
        Cell minCell = empties.front();
        bool first = true;
        if (minCell.theValue != 0) {
            throw std::invalid_argument("most constrained empty cell was nonempty!");
        }


        // iterate and get the empty cell with least possible values and return it
        for (const auto& cell : empties)
        {
            if (first)
            {
                first = false;
                continue;
            }
            else
            {
                auto curMin = cell.possibleMoves.size();
                if (curMin < minCell.possibleMoves.size())
                {
                    minCell = cell;
                }
            }
        }
        return minCell;
    }



public:
    /* data */
    std::vector<std::vector<Cell>> array;
};

