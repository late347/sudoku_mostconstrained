#pragma once


#include "Sudoku_includes.h"
#include "Algo.h"
#include <exception>
#include <iomanip>
#include <thread>
#include <execution>
#include <algorithm>
#include <mutex>
#include <vector>
#include <array>



class Board;
class Cell;

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

    void printBoard() const;

    void initialize(int cluesBoard[][SUDOKU_SIZE], int sudokuRows = SUDOKU_SIZE, int sudokuCols = SUDOKU_SIZE);

    bool isSolved() const;

    // legalMove must be checked by board because each cell legality is
    // affected by box cells, row cells and column cells
    bool isLegalMove(const int row, const int col, const int thevalue) const;

    bool isLegalMove(const Cell& cell, const int move) const;


    // gets empty cells and returns the cell which has least possibleMoves available
    // in best case a cell only would have 1 possibleMove  so that it is certain that is the cell value
    Cell getMostConstrainedEmpty();


public:
    /* data */
    std::vector<std::vector<Cell>> array;
};

