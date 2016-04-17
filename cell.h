#ifndef STATE
enum STATE { OFF = 0, ON };
#endif

void initializeCells (int cells[][], const int maxRows, const int maxColumns);

void printCells (const int previousCells[][], const int currentCells[][], const int maxRows,
    const int maxColumns, const WINDOW scr);

int evaluateNeighbors (const int cells[][], const int currentRow, const int currentColumn,
    const int maxRows, const int maxColumns);

void updateCells (int previousCells[][], int currentCells[][],  const int maxRows,
    const int maxColumns);

