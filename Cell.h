#pragma once

#include <vector>
#include <set>
#include <iostream>
#include <deque>
#include <map>
#include "Sudoku_includes.h"

class Cell
{
public:
    enum State
    {
        CLUE,
        GUESSED_VALUE,
        EMPTY
    };

    Cell(int rowCoord = 0, int colCoord = 0, bool isClue = false, int val = -1);

    friend std::ostream& operator<<(std::ostream& os, const Cell& c);

    void setPossibleMove(int move)
    {
        possibleMoves[move] = move;
    }

    std::map<int, int> getPossibleValues()
    {

        return possibleMoves;
    }

    void guess(int guessedVal)
    {
        searchState = GUESSED_VALUE;
        theValue = guessedVal;
        possibleMoves.erase(guessedVal);
    }

    void setAsClue(int sureValue)
    {
        searchState = CLUE;
        theValue = sureValue;
        possibleMoves.erase(sureValue);
    }

public:
    int theValue; // cell's actual sudoku numeric value, the cell entry
    State searchState; // state of the cell  possibly useful to differentiate between guess and clue (?)
    int rowIdx;
    int colIdx;
    // use key and value as the same tried number, map rebalances the keys and values into ascending order which is good.
    // also can pop off first value from the beginning if necessary
    std::map<int, int> possibleMoves;
};
