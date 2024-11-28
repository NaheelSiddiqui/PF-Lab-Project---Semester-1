int main() {
    char array[8][33] = {
        "X X X X X X X X X X X X X X X X X", 
        "X                               X",
        "X       WELCOME TO TETRIS       X",
        "X                               X",
        "X         1. START GAME         X",
        "X        2. INSTRUCTIONS        X",
        "X         3. QUIT GAME          X",
        "X                               X",
        "X X X X X X X X X X X X X X X X X"
    };
    char gamechoice = '\0';
    int startscreen = 1;
    
    while (startscreen) {
        if (_khbit()) {
            gamechoice = getch();
        }
        switch (gamechoice) {
            case '1':
                // start game function
                break;
            case '2':
                // instructions
                break;
            case '3':
                // quit game
                break;
            default:
                break;
        }
    }
}