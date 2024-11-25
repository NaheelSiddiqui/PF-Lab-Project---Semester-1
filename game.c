#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define rows 20
#define columns 11

void generateblocks(char grid[rows][columns], int *block) {
  srand(time(NULL));
  int generate = rand() % 7 + 1;
  *block = generate;
  int start, start1, start2, start3, start4, start5, start6, end;

  switch (generate) {
    case 1:  // block O
      start = rand() % 8 + 1;
      for (int i = 0; i < 2; i++) {
        for (int j = start; j < (start + 2); j++) {
          grid[i][j] = '#';
        }
      }
      break;
    case 2:  // block I
      start2 = rand() % 9 + 1;
      for (int i = 0; i < 4; i++) {
        grid[i][start2] = '#';
      }
      break;
    case 3:  // block S
      end = rand() % 7 + 3;
      for (int i = end; i > (end - 2); i--) {
        grid[0][i] = '#';
      }
      for (int i = end - 1; i > (end - 3); i--) {
        grid[1][i] = '#';
      }
      break;
    case 4:  // block Z
      start3 = rand() % 7 + 2;
      for (int i = start3 - 1; i < (start3 + 1); i++) {
        grid[0][i] = '#';
      }
      for (int i = start3; i < (start3 + 2); i++) {
        grid[1][i] = '#';
      }
      break;
    case 5:  // block L
      start4 = rand() % 8 + 1;
      for (int i = 0; i < 3; i++) {
        grid[i][start4] = '#';
      }
      grid[2][start4 + 1] = '#';
      break;
    case 6:  // block J
      start5 = rand() % 8 + 2;
      for (int i = 0; i < 3; i++) {
        grid[i][start5] = '#';
      }
      grid[2][start5 - 1] = '#';
      break;
    case 7:  // block T
      start6 = rand() % (7 - 2) + 3;
      for (int i = start6; i < (start6 + 3); i++) {
        grid[0][i] = '#';
      }
      grid[1][start6 + 1] = '#';
      break;
  }
  return;
}

void startgame() {
  printf("Welcome to Tetris Game. Press any key to start");
  char start;
  scanf("%c", &start);
  if (start >= 32 && start <= 127) {
    return;
  } else {
    system("cls");
    startgame();
  }
  return;
}

void printgrid(char grid[rows][columns]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
}

void moveleft(char grid[rows][columns]) {
  int end = 0;
  for (int i = rows - 1; i >= 0 && end == 0; i--) {
    for (int j = 1; j < columns && end == 0; j++) {
      if (grid[i][j] == '#') {
        if (grid[i][j - 1] == 'X' || grid[i][j - 1] == '$') {
          end = 1;
          return;
        } else if (grid[i - 1][j - 1] == '#' && grid[i][j - 2] == 'X' ||
                   grid[i][j - 2] == '$') {
          end = 1;
          return;
        } else if (grid[i][j - 1] == '-' && (j - 1) > 0) {
          grid[i][j - 1] = '#';
          grid[i][j] = '-';
        }
      }
    }
  }
  return;
}

void moveright(char grid[rows][columns]) {
  int end = 0;
  for (int i = rows - 2; i >= 0 && end == 0; i--) {
    for (int j = columns - 2; j >= 0 && end == 0; j--) {
      if (grid[i][j] == '#') {
        if (grid[i][j + 1] == 'X') {
          return;
        } else if (grid[i - 1][j + 1] == '#' && grid[i][j + 2] == 'X') {
          return;
        } else if (grid[i][j + 1] == '-' && (j + 1) <= columns - 2) {
          grid[i][j + 1] = '#';
          grid[i][j] = '-';
        }
      }
    }
  }
  return;
}

void movedown(char grid[rows][columns]) {
  int end = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == '#') {
        if (grid[i + 1][j] == 'X' || grid[i + 1][j] == '$') {
          end = 1;
        }
      }
    }
  }
  if (end == 1) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (grid[i][j] == '#') grid[i][j] = '$';
      }
    }
  } else if (end == 0) {
    for (int i = rows - 2; i >= 0; i--) {
      for (int j = 0; j < columns; j++) {
        if (grid[i][j] == '#') {
          grid[i][j] = '-';
          grid[i + 1][j] = '#';
        }
      }
    }
  }
  return;
}

void checkline(char grid[rows][columns]) {
  int samecount = 0, i, j;
  char line[columns - 2];
  for (int i = 0; i < columns - 3; i++) {
    line[i] = '$';
  }

  for (i = 0; i < rows; i++) {
    for (j = 1; j < columns - 1; j++) {
      if (grid[i][j] == line[j - 1]) samecount++;
      if (samecount == 9) {
        for (int k = 1; k < columns - 1; k++) {
          grid[i][k] = '-';
        }
        for (int l = i; l >= 0; l--) {
          for (int m = 1; m < columns - 1; m++) {
            grid[l][m] = grid[l - 1][m];
          }
        }
        for (int n = 1; n < columns - 1; n++) {
          grid[0][n] = '-';
        }
        return;
      }
    }
  }
  return;
}

int checkblock(char grid[rows][columns]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == '#') {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  char grid[rows][columns];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      grid[i][j] = '-';  // Initialize the grid with '-'
    }
  }
  for (int i = 0; i < columns; i++) {
    grid[rows - 1][i] = 'X';
  }
  for (int i = 0; i < rows - 1; i++) {
    grid[i][0] = 'X';
  }
  for (int i = 0; i < rows - 1; i++) {
    grid[i][columns - 1] = 'X';
  }
  for (int i = 1; i < columns - 3; i++) {
    grid[18][i] = '$';
  }

  int block = 0;
  generateblocks(grid, &block);  // Pass the grid to the function
  printf("%d", block);
  startgame();

  while (1) {
    int check = checkblock(grid);
    if (check == 1) {
      generateblocks(grid, &block);
    }
    printgrid(grid);
    char choice;
    printf("\nEnter choice: ");
    scanf("%c", &choice);
    switch (choice) {
      case 'A':
        moveleft(grid);
        checkline(grid);
        system("cls");
        break;
      case 'S':
        movedown(grid);
        checkline(grid);
        system("cls");
        break;
      case 'D':
        moveright(grid);
        checkline(grid);
        system("cls");
        break;
      case 'W':
        system("cls");
      default:
        system("cls");
    }
  }
  return 0;
}