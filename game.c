#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateblocks(char *grid[10][]) {
  srand(time(NULL));

  int generate = rand() % 7;

  switch (generate) {
    case 0:                    // O block
      int start = rand() % 6;  // rand() % (max - min + 1) + min
      for (int i = 0; i < 2; i++) {
        for (int j = start; j < (start + 2); j++) {
          *grid[i][j] = '#';
        }
      }
      break;
    case 1:                     // I block
      int start2 = rand() % 7;  // rand() % (max - min + 1) + min
      for (int i = 0; i < 4; i++) {
        *grid[i][start2] = '#';
      }
      break;
    case 2:                                // S block
      int end = rand() % (6 - 2 + 1) + 2;  // rand() % (max - min + 1) + min
      for (int i = end; i > (end - 2); i--) {
        *grid[0][i] = '#';
      }
      for (int i = end - 1; i > (end - 3); i--) {
        *grid[1][i] = '#';
      }
      break;
    case 3:                                   // Z block
      int start3 = rand() % (5 - 0 + 1) + 0;  // rand() % (max - min + 1) + min
      for (int i = start3 + 1; i < (start3 + 3); i++) {
        *grid[0][i] = '#';
      }
      for (int i = start3; i < (start3 + 2); i++) {
        *grid[1][i] = '#';
      }
      break;
    case 4:                     // L block
      int start4 = rand() % 6;  // rand() % (max - min + 1) + min
      for (int i = 0; i < 3; i++) {
        *grid[i][start4] = '#';
      }
      *grid[2][start4 + 1] = '#';
      break;
    case 5:                         // J block
      int start5 = rand() % 7 + 1;  // rand() % (max - min + 1) + min
      for (int i = 0; i < 3; i++) {
        *grid[i][start5] = '#';
      }
      *grid[2][start5 - 1] = '#';
      break;
    case 6:                               // J block
      int start6 = rand() % (6 - 2) + 2;  // rand() % (max - min + 1) + min
      for (int i = start6; i < (start6 + 3); i++) {
        *grid[0][i] = '#';
      }
      *grid[1][start6 + 1] = '#';
      break;
  }

  return;
}

void printgrid(char grid[10][7]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
  return;
}

int main() {
  char grid[10][7];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      grid[i][j] = '-';
    }
  }

  generateblocks(&grid);
  printgrid(grid);

  return 0;
}