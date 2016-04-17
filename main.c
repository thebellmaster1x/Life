#include <ncurses.h>
#include "cell.h"

#define CELLROW 25
#define CELLCOL 80

enum STATE { OFF = 0, ON };

int main (void) {

    int maxY, maxX;

    initscr();
    cbreak();
    noecho();
    keypad();

    getmaxyx(maxY, maxX);

    int currentCells[CELLROW][CELLCOL];    /* limit size for now */
    int previousCells[CELLROW][CELLCOL];

    initializeCells(currentCells, CELLROW, CELLCOL);    /* randomize starting field */ 

    for (size_t y = 0; y < CELLROW; y++) {              /* zero out cell buffer */
        for (size_t x = 0; x < CELLCOL; x++) {
            previousCells[y][x] = OFF;
        }
    }

    printCells(previousCells, currentCells, CELLROW, CELLCOL, stdscr);          /* print starting field */

    while(1) {                                                                  /* main automaton loop */
        updateCells(previousCells, currentCells, CELLROW, CELLCOL, stdscr);
        printCells(previousCells, currentCells, CELLROW, CELLCOL);
        getch();
        refresh();
    }

    endwin();

    return 0;

}
