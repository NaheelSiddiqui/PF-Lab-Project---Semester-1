#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 10

typedef struct {
    char name[50];
    int score;
} Player;

Player highScores[MAX_PLAYERS];
int playerCount = 0;


void addHighScore(Player player) {
    // Add the player to the high scores
    highScores[playerCount++] = player;

    // Sort the high scores in descending order of scores
    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = i + 1; j < playerCount; j++) {
            if (highScores[i].score < highScores[j].score) {
                Player temp = highScores[i];
                highScores[i] = highScores[j];
                highScores[j] = temp;
            }
        }
    }

    // Limit the high scores to the top MAX_PLAYERS
    if (playerCount > MAX_PLAYERS) {
        playerCount = MAX_PLAYERS;
    }
}

void displayHighScores() {
    printf("\n- - - High Score Board - - -\n");
    printf("Rank   Name                    Score\n");
    printf("----   ---------------------   -----\n");
    for (int i = 0; i < playerCount; i++) {
        printf("%-6d %-22s %d\n", i + 1, highScores[i].name, highScores[i].score);
    }
}


void getPlayerName(Player *player) {
    printf("Enter your name: ");
    fgets(player->name, 50, stdin);
    player->name[strcspn(player->name, "\n")] = '\0';  // Remove trailing newline
    player->score = 0;  // Initialize score to 0
}


int main() {
    Player currentPlayer;
    char grid[rows][columns];

    // Get player name
    getPlayerName(&currentPlayer);

    initializeGrid(grid);

    int end = 1;
    startGame(&end, &currentPlayer.score);

    int block = 0, orientation = 0;

    while (end == 0) {
        if (checkblock(grid)) generateblocks(grid, &block);

        system("cls");
        printgrid(grid, &currentPlayer.score);

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
                rotateblock(grid, &block, &orientation);
                break;
            case 'X':
                printf("\nEnding game...");
                sleep(1);
                end = 1;
                break;
            default:
                break;
        }

        if (choice == '\0') {
            movedown(grid);
        }
        checkline(grid, &currentPlayer.score);
        gameEnd(grid, &end);

        system("cls");

        if (end == 1) {
            printf("\n\n- - - - Game ended. %s scored %d points - - - -", currentPlayer.name, currentPlayer.score);
            sleep(1);

            // Update high scores
            addHighScore(currentPlayer);

            // Display high scores
            displayHighScores();

            // Restart or quit
            initializeGrid(grid);
            startGame(&end, &currentPlayer.score);
        }
    }
    return 0;
}


