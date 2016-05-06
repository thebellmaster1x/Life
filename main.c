#include <ncurses.h>
#include "cell.h"

#define ROWMAX 25
#define COLMAX 80

#define OFF 0
#define ON 1

int main ( void ) {

    initscr() ;
    cbreak() ;
    noecho() ;
    keypad( stdscr, TRUE ) ;
    curs_set( 0 ) ;

    start_color() ;
    init_pair( 1, COLOR_WHITE, COLOR_BLACK ) ;
    init_pair( 2, COLOR_RED, COLOR_BLACK ) ;

    //TODO: dynamically obtain console size

    int cells[ ROWMAX * COLMAX ] ;
    int cellBuffer[ ROWMAX * COLMAX ] ;

    // set starting field
    initializeField( cells ) ;

    // zero cell buffer
    for( int row = 0; row < ROWMAX; row++ ) {
        for( int col = 0; col < COLMAX; col++ ) {
            cellBuffer[ row * COLMAX + col ] = OFF ;
        }
    }

    while(1) {

        printField( cells, cellBuffer ) ;

        updateField( cells, cellBuffer ) ;

        getch() ;

    }

    endwin() ;

    return 0 ;

}
