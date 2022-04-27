#pragma once

#include <vector>
#include <array>
#include "Cell.h"
#include "Sudoku_includes.h"
#include <exception>
#include <iomanip>
#include <thread>
#include <execution>
#include <algorithm>

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

    bool isLegalMove(const Cell& cell, const int move) const;

    int numberOfRows() const { return array.size(); }
    int numberOfColumns() const { return numberOfRows() ? array[0].size() : 0; }
    void printBoard() const;

    void initialize(int cluesBoard[][SUDOKU_SIZE], int sudokuRows = SUDOKU_SIZE, int sudokuCols = SUDOKU_SIZE);

    bool isSolved() const;

    // legalMove must be checked by board because each cell legality is
    // affected by box cells, row cells and column cells
    bool isLegalMove(const int row, const int col, const int thevalue) const;


    // gets empty cells and returns the cell which has least possibleMoves available
    // in best case a cell only would have 1 possibleMove  so that it is certain that is the cell value
    Cell getMostConstrainedEmpty()
    {
        // get empty cells together from board
        // replace with PARALLEL copy_if() if possible and feasible
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
        
            // replace loop with  parallelized version of launching threads
        /*
        for i=0 i< emptiesSize i++
            launch thread that takes Cell by value, and board.array by value  and shraed resource empties vec by reference
            thread starts to process the guessing for the cell
            NOTE!!!: shared resource is the owning empties vector, guard it with mutex
            thread acquires mutex and returns the modified local Cell obj into the vector empties reference

         outside the for all empties loop after it
         we can join the threads
        */


            // for each cell  => could launch thread that is:::
            //              reading the isLEgalMove for any possible sudoku moves from the board object
            //              if it was legal sudoku move
            //                  modify the cell by reference, (this is sha

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

        //replace with PARALLEL min_element()
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

