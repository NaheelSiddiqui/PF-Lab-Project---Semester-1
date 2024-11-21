#include <stdio.h>

void rotateblocks(int I[4][4]) {
    int j=0, a=0;
    for (int i=0; i<4; i++) {
        for (j=0+a; j<4; j++) {
            int temp = I[i][j];
            I[i][j] = I[j][i];
            I[j][i] = temp;
        }
        a++;
    }

    return;
}

void shiftleft(int I[4][4], int* rotate) {
    int abc = (*rotate)%2;
    int j=0;
    if (abc==1) {
        for (int i = 0; i < 4; i++) {
            for (j=0; j<4; j++) {
                if ((j+2)>3) {
                    break;
                }
                int temp = I[i][j];
                I[i][j] = I[i][j+2];
                I[i][j+2] = temp;
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            for (j=0; j<4; j++) {
                if ((j+2)>3) {
                    break;
                }
                int temp = I[i][j];
                I[i][j] = I[i][j+2];
                I[i][j+2] = temp;
            }
        }
        for (int i = 0; i < 4; i++) {
            for (j=0; j<4; j++) {
                if ((j+1)>3) {
                    break;
                }
                int temp = I[j][i];
                I[j][i] = I[j][i+1];
                I[j][i+1] = temp;
            }
        }
    }

    return;
}

void reverse(int I[4][4]) {
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<2; j++) {
            int temp = I[i][3-j];
            I[i][3-j] = I[i][j];
            I[i][j] = temp;
        }
    }

    return;
}

int main() {
    int I[4][4] = {
        {1, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    int rotate = 0;
    for (int i=0; i<5; i++) {
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                printf("%d ", I[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        rotateblocks(I);
        reverse(I);

        shiftleft(I, &rotate);
    }

    return 0;
}