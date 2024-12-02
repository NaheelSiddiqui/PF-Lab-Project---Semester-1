#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// #include <windows.h>

#define rows 15
#define columns 10

void generateblocks(char grid[rows][columns], int *block) {
  srand(time(NULL));

  int retry = 0;
  // int possibleblocks[7] = {1, 2, 3, 4, 5, 6, 7};
  for (; retry == 0;) {
    int generate = rand() % 7 + 1;
    // int generate = 7;
    *block = generate;
    int start, start1, start2, start3, start4, start5, start6, end;
    int check;
    switch (generate) {
      case 1:  // block O
        check = 0;
        start = rand() % (columns - 3) + 1;
        for (int i = 0; i < 2; i++) {
          for (int j = start; j < (start + 2); j++) {
            if (grid[i][j] == '-') check++;
          }
        }
        if (check == 4) {
          for (int i = 0; i < 2; i++) {
            for (int j = start; j < (start + 2); j++) {
              grid[i][j] = '#';
            }
          }
          retry = 1;
        }
        break;

      case 2:  // block I
        check = 0;
        start2 = rand() % (columns - 2) + 1;
        for (int i = 0; i < 4; i++) {
          if (grid[i][start2] == '-') check++;
        }
        if (check == 4) {
          for (int j = 0; j < 4; j++) {
            grid[j][start2] = '#';
          }
          retry = 1;
        }
        break;

      case 3:  // block S
        check = 0;
        end = rand() % (columns - 4) + 3;
        for (int i = end; i > (end - 2); i--) {
          if (grid[0][i] == '-') check++;
        }
        for (int i = end - 1; i > (end - 3); i--) {
          if (grid[1][i] == '-') check++;
        }

        if (check == 4) {
          for (int i = end; i > (end - 2); i--) {
            grid[0][i] = '#';
          }
          for (int i = end - 1; i > (end - 3); i--) {
            grid[1][i] = '#';
          }
          retry = 1;
        }
        break;

      case 4:  // block Z
        check = 0;
        start3 = rand() % (columns - 2) + 2;
        for (int i = start3 - 1; i < (start3 + 1); i++) {
          if (grid[0][i] == '-') check++;
        }
        for (int i = start3; i < (start3 + 2); i++) {
          if (grid[1][i] == '-') check++;
        }
        if (check == 4) {
          for (int i = start3 - 1; i < (start3 + 1); i++) {
            grid[0][i] = '#';
          }
          for (int i = start3; i < (start3 + 2); i++) {
            grid[1][i] = '#';
          }
          retry = 1;
        }
        break;

      case 5:  // block L
        check = 0;
        start4 = rand() % (columns - 3) + 1;
        for (int i = 0; i < 3; i++) {
          if (grid[i][start4] == '-') check++;
        }
        if (grid[2][start4 + 1] == '-') check++;
        if (check == 4) {
          for (int i = 0; i < 3; i++) {
            grid[i][start4] = '#';
          }
          grid[2][start4 + 1] = '#';
          retry = 1;
        }
        break;

      case 6:  // block J
        check = 0;
        start5 = rand() % (columns - 3) + 2;
        for (int i = 0; i < 3; i++) {
          if (grid[i][start5] == '-') check++;
        }
        if (grid[2][start5 - 1] == '-') check++;
        if (check == 4) {
          for (int i = 0; i < 3; i++) {
            grid[i][start5] = '#';
          }
          grid[2][start5 - 1] = '#';
          retry = 1;
        }
        break;

      case 7:  // block T
        check = 0;
        start6 = rand() % (columns - 4 - 2) + 3;
        for (int i = start6; i < (start6 + 3); i++) {
          if (grid[0][i] == '-') check++;
        }
        if (grid[1][start6 + 1] == '-') check++;
        if (check == 4) {
          for (int i = start6; i < (start6 + 3); i++) {
            grid[0][i] = '#';
          }
          grid[1][start6 + 1] = '#';
          retry = 1;
        }
        break;

      default:
        printf("Error");
        break;
    }
  }
  return;
}

void startgame() {
  printf("Welcome to Tetris Game. Press 'X' to end the game");  // Menu screen
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

void printgrid(char grid[rows][columns],
               int *score) {  // function to print grid whenever needed
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
  printf("\nCurrent score = %d", *score);
  return;
}

void moveleft(char grid[rows][columns]) {
  int end = 0;
  for (int i = 0; i < rows;
       i++) {  // to check whether hashtags have space to move
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == '#') {
        if (grid[i][j - 1] == 'X' || grid[i][j - 1] == '$') end = 1;
      }
    }
  }
  if (end == 1) {
    return;
  } else {
    for (int i = rows - 1; i >= 0; i--) {
      for (int j = 0; j < columns; j++) {
        if (grid[i][j] == '#') {
          grid[i][j] = '-';
          grid[i][j - 1] = '#';
        }
      }
    }
  }
  return;
}

void moveright(char grid[rows][columns]) {
  int end = 0;
  for (int i = 0; i < rows;
       i++) {  // to check whether hashtags have space to move
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == '#') {
        if (grid[i][j + 1] == 'X' || grid[i][j + 1] == '$') end = 1;
      }
    }
  }
  if (end == 1) {
    return;
  } else {
    for (int i = rows - 1; i >= 0; i--) {
      for (int j = columns - 1; j >= 0; j--) {
        if (grid[i][j] == '#') {
          grid[i][j] = '-';
          grid[i][j + 1] = '#';
        }
      }
    }
  }
  return;
}

void movedown(char grid[rows][columns]) {
  int end = 0;
  // to check whether hashtags have space to move:
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
  // to create situation where game ends when a hashtag appears in 2nd row
  // when hashtag present in 2nd row, game should end:

  // char endstring[14] = "$$$$$$$$$$$$$X";

  return;
}

void checkline(char grid[rows][columns], int *score) {
  int samecount = 0;
  int i = 0, j = 0;
  char line[columns] = "X$$$$$$$$X";
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      if (grid[i][j] == line[j]) samecount++;
      if (samecount == columns) {
        for (int k = 1; k < columns - 1; k++) {
          grid[i][k] = '-';
        }
        for (int l = i; l > 0; l--) {
          for (int m = 0; m < columns; m++) {
            grid[l][m] = grid[l - 1][m];
          }
        }
        grid[0][0] = 'X';
        grid[0][columns - 1] = 'X';
        for (int n = 1; n < columns - 1; n++) {
          grid[0][n] = '-';
        }
        (*score)++;
      }
    }
    samecount = 0;
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

void gameEnd(char grid[rows][columns], int *end) {
  for (int i = 0; i < columns; i++) {
    if (grid[1][i] == '$') {
      (*end)++;
    }
  }
  return;
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
  for (int i = 1; i < columns - 3; i++) {  // to be removed from final version
    grid[13][i] = '$';
  }

  int block = 0, score = 0;
  generateblocks(grid, &block);  // Pass grid to function to generate block
  printf("%d", block);
  startgame();

  int end = 0;
  while (end == 0) {
    int check = checkblock(grid);
    if (check == 1) {
      generateblocks(grid, &block);
    }
    printgrid(grid, &score);

    int seconds = 2;
    char choice;
    while (seconds > 0) {
      clock_t stop = clock() + CLOCKS_PER_SEC * seconds;
      while (clock() < stop) {
      }
      printf("\nEnter choice: ");
      scanf("%c", &choice);
      switch (choice) {
        case 'A':
          moveleft(grid);
          system("cls");
          break;
        case 'D':
          moveright(grid);
          system("cls");
          break;
        case 'S':
          movedown(grid);
          checkline(grid, &score);
          gameEnd(grid, &end);
          system("cls");
          break;
        case 'X':
          end = 1;
          break;
        default:
          system("cls");
          break;
      }
      if (choice == 'A' || choice == 'S' || choice == 'D') seconds = 0;
      seconds--;
    }

    if (choice == 'A' || choice == 'S' || choice == 'D') {
      system("cls");
      printgrid(grid, &score);
    }
    sleep(2);
    if (end == 0) {
      movedown(grid);
      system("cls");
      printgrid(grid, &score);
    }
    checkline(grid, &score);
    gameEnd(grid, &end);

    if (end == 1) {
      system("cls");
      printf("Game ended. You finished with %d points", score);
    }
  }
  return 0;
}