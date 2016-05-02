void initializeCells (const int maxRows, const int maxColumns, int cells[maxRows][maxColumns]);

void printCells (const int maxRows, const int maxColumns, int previousCells[maxRows][maxColumns],
    int currentCells[maxRows][maxColumns], WINDOW * scr);

int evaluateNeighbors (const int maxRows, const int maxColumns, int cells[maxRows][maxColumns],
    const int currentRow, const int currentColumn);

void updateCells (const int maxRows, const int maxColumns, int previousCells[maxRows][maxColumns],
    int currentCells[maxRows][maxColumns]);
