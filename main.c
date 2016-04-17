#include <ncurses.h>
#include "cell.h"

#define CELLROW 25
#define CELLCOL 80

int main (void) {

    int maxY, maxX;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, maxY, maxX);

    int currentCells[CELLROW][CELLCOL];    /* limit size for now */
    int previousCells[CELLROW][CELLCOL];

    initializeCells(CELLROW, CELLCOL, currentCells);    /* randomize starting field */ 

    for (size_t y = 0; y < CELLROW; y++) {              /* zero out cell buffer */
        for (size_t x = 0; x < CELLCOL; x++) {
            previousCells[y][x] = OFF;
        }
    }

    printCells(CELLROW, CELLCOL, previousCells, currentCells, stdscr);          /* print starting field */

    while(1) {                                                                  /* main automaton loop */
        updateCells(CELLROW, CELLCOL, previousCells, currentCells);
        printCells(CELLROW, CELLCOL, previousCells, currentCells, stdscr);
        getch();
        refresh();
    }

    endwin();

    return 0;

}
