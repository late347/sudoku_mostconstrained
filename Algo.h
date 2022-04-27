#pragma once

#include "Cell.h"
#include "Board.h"
#include <algorithm>
#include <stack>
#include <mutex>
#include <iostream>


// parameters is the board
// returns the solution by reference as solved board
// uses recursion and pass-by-value and RAII for the board solving
// therefore, we can skip any board-undo operations on the board when we backtrack
// from wrong sudoku guesses.
// 
// this approach, creates more memory need, but its simpler to program
// stack usage will become higher though, because for every recursion it has a board.

class Board;
class Cell;

bool solve(Board board, Board& resultBoard);

