#include <ncurses.h>
#include "cell.h"

#define CELLROW 25
#define CELLCOL 80

#define OFF 0
#define ON 1

int main ( void ) {

    initscr() ;
    cbreak() ;
    noecho() ;
    keypad( stdscr, TRUE ) ;

    start_color() ;
    init_pair( 1, COLOR_WHITE, COLOR_BLACK ) ;
    init_pair( 2, COLOR_RED, COLOR_BLACK ) ;

    //TODO: dynamically obtain console size

    short int cells[ CELLROW * CELLCOL ] ;
    short int cellBuffer[ CELLROW * CELLCOL ] ;

    initializeField( cells ) ;

    /*
    for( int row = 0; row < CELLROW; row++ ) {
        for( int col = 0; col < CELLCOL; col++ ) {
            cellBuffer[ row * col ] = OFF ;
        }
    }
    */

    printField( cells ) ;

    getch() ;

    endwin() ;

    return 0 ;

}
