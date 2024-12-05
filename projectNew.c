#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define rows 15
#define columns 10
#define block_size 3

typedef struct player {
  char name[50];
  int age;
  int score;
} player;

void generateblocks(char grid[rows][columns]) {
  srand(time(NULL));

  int retry = 0;
  while (retry == 0) {
    int generate = rand() % 7 + 1;
    int start, check;
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
        start = rand() % (columns - 2) + 1;
        for (int i = 0; i < 3; i++) {
          if (grid[i][start] == '-') check++;
        }
        if (check == 3) {
          for (int j = 0; j < 3; j++) {
            grid[j][start] = '#';
          }
          retry = 1;
        }
        break;

      case 3:  // block S
        check = 0;
        start = rand() % (columns - 4) + 3;
        for (int i = start; i > (start - 2); i--) {
          if (grid[0][i] == '-') check++;
        }
        for (int i = start - 1; i > (start - 3); i--) {
          if (grid[1][i] == '-') check++;
        }

        if (check == 4) {
          for (int i = start; i > (start - 2); i--) {
            grid[0][i] = '#';
          }
          for (int i = start - 1; i > (start - 3); i--) {
            grid[1][i] = '#';
          }
          retry = 1;
        }
        break;

      case 4:  // block Z
        check = 0;
        start = rand() % (columns - 2) + 2;
        for (int i = start - 1; i < (start + 1); i++) {
          if (grid[0][i] == '-') check++;
        }
        for (int i = start; i < (start + 2); i++) {
          if (grid[1][i] == '-') check++;
        }
        if (check == 4) {
          for (int i = start - 1; i < (start + 1); i++) {
            grid[0][i] = '#';
          }
          for (int i = start; i < (start + 2); i++) {
            grid[1][i] = '#';
          }
          retry = 1;
        }
        break;

      case 5:  // block L
        check = 0;
        start = rand() % (columns - 3) + 1;
        for (int i = 0; i < 3; i++) {
          if (grid[i][start] == '-') check++;
        }
        if (grid[2][start + 1] == '-') check++;
        if (check == 4) {
          for (int i = 0; i < 3; i++) {
            grid[i][start] = '#';
          }
          grid[2][start + 1] = '#';
          retry = 1;
        }
        break;

      case 6:  // block J
        check = 0;
        start = rand() % (columns - 3) + 2;
        for (int i = 0; i < 3; i++) {
          if (grid[i][start] == '-') check++;
        }
        if (grid[2][start - 1] == '-') check++;
        if (check == 4) {
          for (int i = 0; i < 3; i++) {
            grid[i][start] = '#';
          }
          grid[2][start - 1] = '#';
          retry = 1;
        }
        break;

      case 7:  // block T
        check = 0;
        start = rand() % (columns - 4 - 2) + 3;
        for (int i = start; i < (start + 3); i++) {
          if (grid[0][i] == '-') check++;
        }
        if (grid[1][start + 1] == '-') check++;
        if (check == 4) {
          for (int i = start; i < (start + 3); i++) {
            grid[0][i] = '#';
          }
          grid[1][start + 1] = '#';
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

void gameInstructions() {
    system("cls");
    char array[16][100] = {
        "X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X",
        "X                                                                     X",
        "X            INITIALLY THE GRID IS POPULATED WITH DASHES (-)          X",
        "X             RANDOM BLOCKS (#) ARE GENERATED FROM THE TOP            X",
        "X        THE BLOCKS MOVE DOWN ON USER INPUT OR EVERY 2 SECONDS        X",
        "X   THE BLOCKS STACK ON TOP OF EACH OTHER ONCE THEY CAN'T MOVE DOWN   X",
        "X         ONCE THE BLOCKS ARE STACKED, THEY BECOME FIXED ($)          X",
        "X   A HORIZONTAL ROW CONTAINING ALL ($) AND NO (-) WILL BE REMOVED    X",
        "X              AND THE SCORE WILL BE IMPLEMENTED BY ONE               X",
        "X                       PRESS 'A' TO MOVE LEFT                        X",
        "X                       PRESS 'D' TO MOVE RIGHT                       X",
        "X                       PRESS 'S' TO MOVE DOWN                        X",
        "X                        PRESS 'W' TO ROTATE                          X",
        "X                PRESS 'X' AT ANY TIME TO END THE GAME                X",
        "X                                                                     X",
        "X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X"
    };
    for (int i=0; i<16; i++) {
        printf("\n%s", array[i]);
    }
    printf("\n\n- - - - - - - - - - Press 'X' to return to home page - - - - - - - - - -");
    int instructions = 0;
    char returntohome = '\0';
    while (instructions == 0) {
        if (_kbhit()) {
            returntohome = _getch();
            if (returntohome == 'X') {
                return;
            }
        }
    }
    return;
}

void showHighScore() {
  FILE *fp = fopen("GameRecords.txt", "r");
  if (fp==NULL) {
    printf("File couldn't be opened");
  }
  player p[100];
  int i = 0, highScore = 0, highestIndex = 0;
  while (fscanf(fp, "%s %d %d", p[i].name, &p[i].age, &p[i].score) != EOF) {
    i++;
    if (p[i].score > highScore) {
      highScore = p[i].score;
      highestIndex = i;
    }
  }
  if (i==0) {
    printf("Currently no records entered");
  } else {
    printf("\nHighest score was %d, belonging to %s, age %d", p[highestIndex].score, p[highestIndex].name, p[highestIndex].age);
  }
  printf("Returning in 5 seconds");
  sleep(5);
  fclose(fp);
}

void startGame(int *end, int *score) {
    char array[10][50] = {
        "X X X X X X X X X X X X X X X X X", 
        "X                               X",
        "X       WELCOME TO TETRIS       X",
        "X                               X",
        "X         1. START GAME         X",
        "X        2. INSTRUCTIONS        X",
        "X      3. CHECK HIGH SCORE      X",
        "X         4. QUIT GAME          X",
        "X                               X",
        "X X X X X X X X X X X X X X X X X"
    };
    system("cls");
    for (int i=0; i<10; i++) {
        printf("%s\n", array[i]);
    }

    char gamechoice = '\0';
    int startscreen = 1;
    while (startscreen) {
        if (_kbhit()) {
            gamechoice = _getch();
        }
        switch (gamechoice) {
            case '1':
                printf("Initiating Game...");
                *end = 0;
                *score = 0;
                sleep(1);
                return;
                break;
            case '2':
                printf("Case 2");
                gameInstructions();
                gamechoice = '\0';
                system("cls");
                for (int i=0; i<10; i++) {
                    printf("%s\n", array[i]);
                }
                break;
            case '3':
                system("cls");
                showHighScore();
                gamechoice = '\0';
                system("cls");
                for (int i=0; i<10; i++) {
                    printf("%s\n", array[i]);
                }
                break;
            case '4':
                printf("\n\nExiting the Program...");
                sleep(1);
                system("cls");
                exit(0);
            default: 
                break;
        }
    }
    return;
}

void printgrid(char grid[rows][columns], int *score) {  // function to print grid whenever needed
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
  for (int i = 0; i < rows; i++) {  // to check whether hashtags have space to move
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

  return;
}

void checkline(char grid[rows][columns], int *score) {
  char removeline[columns];
  for (int i=0; i<columns; i++) {
    if (i==0 || i==(columns-1)) removeline[i] = 'X';
    else removeline[i] = '$';
  }
  int i = 0, j = 0, samecount = 0;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      if (grid[i][j] == removeline[j]) samecount++;
      if (samecount == columns) {
        (*score)++;
        for (int k = 1; k < columns - 1; k++) {
          grid[i][k] = '-';
        }
        for (int l = i; l > 0; l--) {
          for (int m = 0; m < columns; m++) {
            grid[l][m] = grid[l - 1][m];
          }
        }
        for (int n = 0; n < columns; n++) { // repopulating the first row as default
          if (n==0 || n==columns-1) grid[0][n]='X';
          else grid[0][n] = '-';
        }
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
      *end = 1;
    }
  }
  return;
}

void initializeGrid(char grid[rows][columns]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      grid[i][j] = 'X';  
    }
  }
  for (int i = 0; i < rows-1; i++) {
    for (int j=1; j<columns-1; j++) {
      grid[i][j] = '-';
    }
  }
  return;
}

void rotateBlocks(char grid[rows][columns]) {
  int topmost, leftmost;
  for (int i=0; i<rows; i++) {
    for (int j=0; j<columns; j++) {
      if (grid[i][j] == '#') {
        topmost = i;
        j=columns;
        i=rows;
      }
    }
  }
  for (int i=0; i<columns; i++) {
    for (int j=0; j<rows; j++) {
      if (grid[j][i] == '#') {
        leftmost = i;
        j=rows;
        i=columns;
      }
    }
  }

  char block[block_size][block_size];
  memset(block, '-', sizeof(block));

  int end = 0;
  for (int i=topmost; i<topmost+3; i++) {
    for (int j=leftmost; j<leftmost+3; j++) {
      if (grid[i][j]=='X' || grid[i][j]=='$') end++;
    }
  }

  char temp[block_size][block_size];
  memset(temp, '-', sizeof(temp));
  if (end==0) {
    for (int i=topmost; i<topmost+3; i++) {
      for (int j=leftmost; j<leftmost+3; j++) {
        block[i-topmost][j-leftmost] = grid[i][j];
      }
    }
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
            temp[j][block_size - 1 - i] = block[i][j];
        }
    }
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
            block[i][j] = temp[i][j];
        }
    }
    for (int i=topmost; i<topmost+3; i++) {
      for (int j=leftmost; j<leftmost+3; j++) {
        grid[i][j] = block[i-topmost][j-leftmost];
      }
    }
    return;
  } else {
    return;
  }
}

void storeRecord(int playerScore) {
  system("cls");
  player p1;
  printf("\nEnter your name: ");
  getchar();
  fgets(p1.name, sizeof(p1.name), stdin);
  p1.name[strcspn(p1.name, "\n")] = '\0';
  printf("\nEnter your age: ");
  getchar();
  scanf("%d", &p1.age);
  p1.score = playerScore;
  FILE *fp = fopen("GameRecords.txt", "a");
  if (fp==NULL) {
    printf("File couldn't be opened");
  } else {
    printf("File opened successfully");
  }
  fprintf(fp, "%s %d %d", p1.name, p1.age, p1.score);
  printf("\nMRecord successfully added");
  fclose(fp);
  return;
}

int main() {
  char grid[rows][columns];
  initializeGrid(grid);
  
  int end = 1, score = 0;
  startGame(&end, &score);

  int block = 0;

  while (end == 0) {
    if (checkblock(grid)) generateblocks(grid);
    
    system("cls");
    printgrid(grid, &score);

    int timeout = 2;
    char choice = '\0';
    clock_t start_time = clock();  
    printf("\n- - - Enter choice: - - -");
    while ((clock() - start_time) / CLOCKS_PER_SEC < timeout) {
        if (_kbhit()) {  
          choice = _getch();  
          break;  
        }
    }
      switch (choice) {
        case 'A':
          moveleft(grid);
          break;
        case 'D':
          moveright(grid);
          break;
        case 'S':
          movedown(grid);
          break;
        case 'W':
          rotateBlocks(grid);
          break;
        case 'X':
          printf("\nEnding game...");
          end = 1;
          break;
        default:
          break;
      }
    if (choice == '\0'){
      movedown(grid);
	  }
    checkline(grid, &score);
    gameEnd(grid, &end);

    system("cls");

    if (end == 1) {
      printf("\n\n- - - - Game ended. You finished with %d points - - - -", score);
      printf("\n- - - Would you like us to record your score (Y/N) - - -");
      char choice;
      scanf("%c", &choice);
      if (choice == 'Y') {
        storeRecord(score);
      } else {
        printf("Returning to home screen...");
        sleep(1);
      }
      sleep(3);
      initializeGrid(grid);
      startGame(&end, &score);
    }
  }
  return 0;
}