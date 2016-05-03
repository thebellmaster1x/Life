#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define CELLROW 25
#define CELLCOL 80

#define OFF 0
#define ON 1

#define FIELDDENSITY 8

void initializeField( short int *cells ) {

    srand( time(0) ) ;

    for( int row = 0; row < CELLROW; row++ ) {
        for( int col = 0; col < CELLCOL; col++ ) {
            cells[ row * col ] = ( rand() % FIELDDENSITY == 0 ) ? ON : OFF ;
        }
    }

}

void printField( short int *cells ) {

    for( int row = 0; row < CELLROW; row++ ) {
        for( int col = 0; col < CELLCOL; col++ ) {
            if( cells[ row * col ] == ON ) {
                mvaddch( row, col, '#' | COLOR_PAIR(2) ) ;
            }
        }
    }

    refresh() ;

}
