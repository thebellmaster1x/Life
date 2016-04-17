#include <ncurses.h>

#define CELLROW 25
#define CELLCOL 80

enum { OFF = 0, ON };

int main (void) {

    int maxY, maxX;

    initscr();
    cbreak();
    noecho();
    keypad();

    getmaxyx(maxY, maxX);

    int currentCells[CELLROW][CELLCOL];    // limit size for now

    initializeCells(currentCells);

    while(1) {
        printCells(currentCells);
        updateCells(currentCells);
        refresh();
    }

    endwin();

    return 0;

}
