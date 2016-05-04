#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ROWMAX 25
#define COLMAX 80

#define OFF 0
#define ON 1

#define FIELDDENSITY 8

void initializeField( short int *cells ) {

    srand( time( 0 ) ) ;

    for( int row = 0; row < ROWMAX; row++ ) {
        for( int col = 0; col < COLMAX; col++ ) {
            cells[ row * COLMAX + col ] = ( rand() % FIELDDENSITY == 0 ) ? ON : OFF ;
        }
    }

}

void printField( short int *cells ) {

    // clear field
    for( int row = 0; row < ROWMAX; row++ ) {
        for( int col = 0; col < COLMAX; col++ ) {
                mvaddch( row, col, ' ' ) ;
            }
        }

    // print if cell is on
    for( int row = 0; row < ROWMAX; row++ ) {
        for( int col = 0; col < COLMAX; col++ ) {
            if( cells[ row * COLMAX + col ] == ON ) {
                mvaddch( row, col, '#' | COLOR_PAIR(2) ) ;
            }
        }
    }

    refresh() ;

}
