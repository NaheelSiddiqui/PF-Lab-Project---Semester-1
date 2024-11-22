#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void generateblocks(char grid[11][9], int *block) {
  srand(time(NULL));
  int generate = rand() % 7 + 1;
  *block = generate;
  int start, start1, start2, start3, start4, start5, start6, end;

  switch (generate) {
    case 1:  // block O
      start = rand() % 6 + 1;  
      for (int i = 0; i < 2; i++) {
        for (int j = start; j < (start + 2); j++) {
          if (grid[i][j]=='-') grid[i][j] = '#';
          else {
            start = rand() % 6 + 1;
            i = 0;
          }
        }
      }
      break;
    case 2: // block I
      start2 = rand() % 7 + 1;
      for (int i = 0; i < 4; i++) {
        grid[i][start2] = '#';
      }
      break;
    case 3: // block S
      end = rand() % 5 + 3;
      for (int i = end; i > (end - 2); i--) {
        grid[0][i] = '#';
      }
      for (int i = end - 1; i > (end - 3); i--) {
        grid[1][i] = '#';
      }
      break;
    case 4: // block Z
      start3 = rand() % 5 + 2;
      for (int i = start3 - 1; i < (start3 + 1); i++) {
        grid[0][i] = '#';
      }
      for (int i = start3; i < (start3 + 2); i++) {
        grid[1][i] = '#';
      }
      break;
    case 5: // block L
      start4 = rand() % 6 + 1;
      for (int i = 0; i < 3; i++) {
        grid[i][start4] = '#';
      }
      grid[2][start4 + 1] = '#';
      break;
    case 6: // block J
      start5 = rand() % 6 + 2;
      for (int i = 0; i < 3; i++) {
        grid[i][start5] = '#';
      }
      grid[2][start5 - 1] = '#';
      break;
    case 7: // block T
      start6 = rand() % (5 - 2) + 3;
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

void printgrid(char grid[11][9]) {
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
}

void moveleft(char grid[11][9]) {
  int end = 0;
  for (int i = 9; i >= 0 && end == 0; i--) {
    for (int j = 1; j < 9 && end == 0; j++) {
      if (grid[i][j] == '#') {
        if (grid[i][j - 1] == 'X') {
          end = 1;
        } else if (grid[i - 1][j - 1] == '#' && grid[i][j - 2] == 'X') {
          end = 1;
        } else if (grid[i][j - 1] == '-' && (j - 1) > 0) {
          grid[i][j - 1] = '#';
          grid[i][j] = '-';
        }
      }
    }
  }
  return;
}

void moveright(char grid[11][9]) {
  int end = 0;
  for (int i = 9; i >= 0 && end == 0; i--) {
    for (int j = 7; j >= 0 && end == 0; j--) {
      if (grid[i][j] == '#') {
        if (grid[i][j + 1] == 'X') {
          end = 1;
        } else if (grid[i - 1][j + 1] == '#' && grid[i][j + 2] == 'X') {
          end = 1;
        } else if (grid[i][j + 1] == '-' && (j + 1) <= 7) {
          grid[i][j + 1] = '#';
          grid[i][j] = '-';
        }
      }
    }
  }
  return;
}

void movedown(char grid[11][9]) {
  int end = 0, change = 0;
  for (int i = 9; i >= 0 && end == 0; i--) {
    for (int j = 0; j <= 9 && end == 0; j++) {
      if (grid[i][j] == '#') {
        if (grid[i+1][j] == 'X' || grid[i+1][j] == '$') { // stops the block in its place
          end = 1;
          change++;
        } else if (grid[i + 1][j] == '-' && (i + 1) <= 9) {
          grid[i + 1][j] = '#';
          grid[i][j] = '-';
        } 
      }
    }
  }
  if (change==1) { // to convert all hashtags to dollar signs
    for (int i=0; i<11; i++) {
      for (int j=0; j<9; j++) {
        if (grid[i][j]=='#') {
          grid[i][j] = '$';
        }
      }
    }
  }
  return;
}

void checkline(char grid[11][9]) { // to check if there is a complete line
  int samecount = 0, i, j;
  char line[9] = {'X','$','$','$','$','$','$','$','X'};
  for (i=0; i<11; i++) {
    for (j=0; j<9; j++) {
      if (grid[i][j] == line[j]) samecount++;
      if (samecount==9) {
        for (int k=1; k<8; k++) {
          grid[i][k] = '-';
        }
        for (int l=i; l>=0; l--) {
          for (int m=1; m<8; m++) {
            grid[l][m] = grid[l-1][m];
          }
        }
        for (int n=1; n<8; n++) {
          grid[0][n] = '-';
        }
      }
    }
    samecount = 0;
  }
  return;
}

int checkblock (char grid[11][9]) {
  int hashtag = 0;
  for (int i=0; i<11; i++) {
    for (int j=0; j<9; j++) {
      if (grid[i][j]=='#') {
        hashtag++;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  char grid[11][9];
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 9; j++) {
      grid[i][j] = '-';  // Initialize the grid with '-'
    }
  }
  for (int i = 0; i < 11; i++) {
    grid[10][i] = 'X';
  }
  for (int i = 0; i < 10; i++) {
    grid[i][0] = 'X';
  }
  for (int i = 0; i < 10; i++) {
    grid[i][8] = 'X';
  }
  for (int i=1; i<6; i++) {
    grid[9][i] = '$';
  }

  int block = 0; // to receive what type of block is created (for rotation)
  printf("%d", block); 
  startgame();

  while (1) {
    int check = checkblock(grid);
    if (check==0) {
      generateblocks(grid, &block); // Pass the grid to the function
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