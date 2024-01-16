#pragma once  
#include "Cell.h"  

class Grid {
public:
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        cells.resize(rows, std::vector<Cell>(cols));
    }

    const Cell& getCell(int row, int col) const {
        return cells[row][col];
    }

    void revealCell(int row, int col) {
        cells[row][col].reveal();
    }

    void fillCell(int row, int col) {
        cells[row][col].fill();
    }

private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> cells;
};
