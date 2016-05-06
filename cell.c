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

int countNeighbors( short int *cells, int row, int col ) {

    int neighbors ;

    for( int rowMod = -1; rowMod <=1; rowMod++ ) {
        for( int colMod = -1; colMod <=1; colMod++ ) {

            // handle edges and corners
            if( row + rowMod == -1 ) {
                if ( col + colMod == -1 ) {
                    // NW corner
                    neighbors += cells[ (ROWMAX - 1) * COLMAX + (COLMAX - 1) ] ;
                    continue ;
                } else if ( col + colMod == COLMAX ) {
                    // NE corner
                    neighbors += cells[ (ROWMAX - 1) * COLMAX ] ;
                    continue ;
                } else {
                    // top row
                    neighbors += cells[ (ROWMAX - 1) * COLMAX + (col + colMod) ] ;
                    continue ;
                }
            } else if ( row + rowMod == ROWMAX ) {
                if ( col + colMod == -1 ) {
                    // SW corner
                    neighbors += cells[ (COLMAX - 1) ] ;
                    continue ;
                } else if ( col + colMod == COLMAX ) {
                    // SE corner
                    neighbors += cells[ 0 ] ;
                    continue ;
                } else {
                    // bottom row
                    neighbors += cells[ (col + colMod) ] ;
                    continue ;
                }
            } else if ( col + colMod == -1 ) {
                // left column
                neighbors += cells[ (row + rowMod) * COLMAX + (COLMAX - 1 ) ] ;
                continue;
            } else if ( col + colMod == COLMAX ) {
                // right column
                neighbors += cells[ (row + rowMod) * COLMAX ] ;
                continue;
            } else {
                // center field
                neighbors += cells[ (row + rowMod) * COLMAX + (col + colMod) ] ;
            }

        }
    }

    neighbors -= cells[ row * COLMAX + col ] ;

    return neighbors ; 

}

void printField( short int *cells ) {

    int neighbors ;

    // clear field
    for( int row = 0; row < ROWMAX; row++ ) {
        for( int col = 0; col < COLMAX; col++ ) {
                mvaddch( row, col, ' ' ) ;
            }
        }

    // print if cell is on
    for( int row = 0; row < ROWMAX; row++ ) {
        for( int col = 0; col < COLMAX; col++ ) {

            neighbors = countNeighbors( cells, row, col ) ;

            if( cells[ row * COLMAX + col ] == ON ) {
                mvaddch( row, col, neighbors + '0' | COLOR_PAIR(2) ) ;
            } else {
                mvaddch( row, col, neighbors + '0' | COLOR_PAIR(1) ) ;
            }

        }
    }

    refresh() ;

}

void updateField( short int *cells, short int *cellBuffer ) {

    int neighbors ;
    int row, col ;

    // copy current field into cell buffer
    for( row = 0; row < ROWMAX; row++ ) {
        for( col = 0; col < COLMAX; col++ ) {
            cellBuffer[ row * COLMAX + col ] = cells[ row * COLMAX + col ] ;
        }
    }

    for( row = 0; row < ROWMAX; row++ ) {
        for( col = 0; col < COLMAX; col++ ) {

            neighbors = countNeighbors( cellBuffer, row, col ) ;

            if( cellBuffer[ row * COLMAX + col ] == ON ) {
                // survival conditions
                cells[ row * COLMAX + col ] = (neighbors == 2 || neighbors == 3) ? ON : OFF ;
            }/* else {
                // birth conditions
                cells[ row * COLMAX + col ] = (neighbors == 3) ? ON : OFF ;
            }*/

        }
    }

    getch();

}
