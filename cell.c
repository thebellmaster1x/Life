#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define INITIALDENSITY 8        /* initial random ON cells, lower = denser starting field */

enum STATE { OFF = 0, ON };

void initializeCells (int cells[][], const int maxRows, const int maxColumns) {

    srand(time(0));

    for (size_t x = 0; x < maxColumns; x++) {
        for (size_t y = 0; y < maxRows; y++) {

            cells[y][x] = (rand() % INITIALDENSITY) == 0 ? ON : OFF;

        }
    }

}

void printCells (const int previousCells[][], const int currentCells[][], const int maxRows,
    const int maxColumns, const WINDOW scr) {

    for (size_t x = 0; x < maxColumns; x++) {
        for (size_t y = 0; y < maxRows; y++) {

            if (currentCells[y][x] != previousCells[y][x]) {
                if (currentCells[y][x] == ON) {
                    mvwaddch(scr, y, x, '#');
                } else {
                    mvwaddch(scr, y, x, ' ');
                }
            }

        }
    }

}

int evaluateNeighbors (const int cells[][], const int currentRow, const int currentColumn,
    const int maxRows, const int maxColumns) {

    int neighbors;
    int evaluationRow, evaluationColumn;

    for (int rowModifier = -1; rowModifier <= 1; rowModifier++) {

        evaluationRow = currentRow + rowModifier;

        if (evaluationRow == -1) { evaluationRow = maxRows - 1; }       /* handle top row */
        else if (evaluationRow == maxRows) { evaluationRow = 0; }       /* handle bottom row */

        for (int columnModifier = -1; columnModifier <= 1; columnModifier++) {
            
            evaluationColumn = currentColumn + columnModifier;

            if (evaluationColumn == -1) { evaluationColumn = maxColumns - 1; }       /* handle left column */
            else if (evaluationColumn == maxColumns) { evaluationColumn = 0; }       /* handle right column */

            neighbors += cells[evaluationRow][evaluationColumn];

        }

    }

    neighbors -= cells[currentRow][currentColumn];      /* exclude cell's current value */

    return neighbors;

}

void updateCells (int previousCells[][], int currentCells[][],  const int maxRows,
    const int maxColumns) {

    int cellNeighbors;

    for (size_t y = 0; y < maxRows; y++) {
        for (size_t x = 0; x < maxColumns; x++) {

            previousCells[y][x] = currentCells[y][x];   /* copy current field to cell buffer */

        }
    }

    for (size_t y = 0; y < maxRows; y++) {
        for (size_t x = 0; x < maxColumns; x++) {

            cellNeighbors = evaluateNeighbors(previousCells[y][x]);

            if (previousCells[y][x] == OFF) {

                if (cellNeighbors == 3) {
                    currentCells[y][x] = ON;    /* birth condition */
                }

            } else {

                if (!(cellNeighbors == 2 || cellNeighbors == 3)) {      
                    currentCells[y][x] = OFF;   /* death condition */
                }

            }

        }
    }

}