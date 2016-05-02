#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define INITIALDENSITY 8        /* initial random ON cells, lower = denser starting field */

#define OFF 0
#define ON 1

void initializeCells (const int maxRows, const int maxColumns, int cells[maxRows][maxColumns]) {

    srand(time(0));

    for (size_t x = 0; x < maxColumns; x++) {
        for (size_t y = 0; y < maxRows; y++) {

            cells[y][x] = (rand() % INITIALDENSITY) == 0 ? ON : OFF;

        }
    }

}

int evaluateNeighbors (const int maxRows, const int maxColumns, int cells[maxRows][maxColumns],
    const int currentRow, const int currentColumn);

void printCells (const int maxRows, const int maxColumns, int previousCells[maxRows][maxColumns],
    int currentCells[maxRows][maxColumns], WINDOW * scr) {

    for (size_t y = 0; y < maxRows; y++) {
        for (size_t x = 0; x < maxColumns; x++) {

            if (currentCells[y][x] == OFF) { attron(COLOR_PAIR(1)); }
            else if (currentCells[y][x] == ON) { attron(COLOR_PAIR(2)); }

            mvprintw(y, x, "%i", evaluateNeighbors(maxRows, maxColumns, currentCells, y, x));

/*            if (currentCells[y][x] != previousCells[y][x]) {
                if (currentCells[y][x] == ON) {
                    mvwaddch(scr, y, x, '#');
                } else {
                    mvwaddch(scr, y, x, ' ');
                }
            }
*/
        }
    }

}

int evaluateNeighbors (const int maxRows, const int maxColumns, int cells[maxRows][maxColumns],
    const int currentRow, const int currentColumn) {

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

void updateCells (const int maxRows, const int maxColumns, int previousCells[maxRows][maxColumns],
    int currentCells[maxRows][maxColumns]) {

    int cellNeighbors;

    for (size_t y = 0; y < maxRows; y++) {
        for (size_t x = 0; x < maxColumns; x++) {

            previousCells[y][x] = currentCells[y][x];   /* copy current field to cell buffer */

        }
    }

    for (size_t y = 0; y < maxRows; y++) {
        for (size_t x = 0; x < maxColumns; x++) {

            cellNeighbors = evaluateNeighbors(maxRows, maxColumns, previousCells, y, x);

            if (previousCells[y][x] == OFF) {

                if (cellNeighbors == 3) {
                    currentCells[y][x] = ON;    /* birth condition */
                } else {
                    currentCells[y][x] = OFF;
                }

            }/* else {

                if (!(cellNeighbors == 2 || cellNeighbors == 3)) {      
                    currentCells[y][x] = OFF;   /* death condition *//*
                } else {
                    currentCells[y][x] = ON;
                }

            }*/

        }
    }

}
