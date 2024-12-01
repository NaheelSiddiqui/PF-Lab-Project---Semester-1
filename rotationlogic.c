void rotateblock(char grid[rows][columns], int *block, int *orientation) {
    // Clear the current block '#' from the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid[i][j] == '#') grid[i][j] = '-';
        }
    }

    // Define rotation logic for each block type
    switch (*block) {
        case 1: // O-block doesn't rotate
            break;

        case 2: // I-block
            if (*orientation == 0) { // Vertical to Horizontal
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        if (grid[i][j] == '#') {
                            if (j + 1 < columns && j + 2 < columns && j + 3 < columns &&
                                grid[i][j + 1] == '-' && grid[i][j + 2] == '-' && grid[i][j + 3] == '-') {
                                grid[i][j] = '#';
                                grid[i][j + 1] = '#';
                                grid[i][j + 2] = '#';
                                grid[i][j + 3] = '#';
                                *orientation = 1;
                            }
                            return;
                        }
                    }
                }
            } else { // Horizontal to Vertical
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        if (grid[i][j] == '#') {
                            if (i + 1 < rows && i + 2 < rows && i + 3 < rows &&
                                grid[i + 1][j] == '-' && grid[i + 2][j] == '-' && grid[i + 3][j] == '-') {
                                grid[i][j] = '#';
                                grid[i + 1][j] = '#';
                                grid[i + 2][j] = '#';
                                grid[i + 3][j] = '#';
                                *orientation = 0;
                            }
                            return;
                        }
                    }
                }
            }
            break;

        case 3: // S-block
            if (*orientation == 0) { // Horizontal to Vertical
                // Implement rotation logic here
            } else { // Vertical to Horizontal
                // Implement rotation logic here
            }
            break;

        // Repeat similar logic for other blocks (Z, L, J, T)
        default:
            break;
    }
}


int block = 0, orientation = 0;


case 'W':
    rotateblock(grid, &block, &orientation);
    break;


*block = generate;
*orientation = 0;
