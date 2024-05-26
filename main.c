#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 50

int i, j, height = HEIGHT, width = WIDTH;
int gameOver, score;
int x, y, fruitX, fruitY, flag;
int tailX[100], tailY[100];
int tailLength;

void setup() {
    gameOver = 0;
    x = width / 2;
    y = height / 2;
    label1:
    fruitX = rand() % 20;
    if (fruitX == 0)
        goto label1;
    label2:
    fruitY = rand() % 20;
    if (fruitY == 0)
        goto label2;
    score = 0;
}

void draw() {
    system("cls");
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                printf("#");
            } else {
                if (i == x && j == y)
                    printf("O");
                else if (i == fruitX && j == fruitY)
                    printf("*");
                else {
                    int isTailPart = 0;
                    for (int k = 0; k < tailLength; k++) {
                        if (i == tailX[k] && j == tailY[k]) {
                            printf("o");
                            isTailPart = 1;
                        }
                    }
                    if (!isTailPart)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            flag = 1;
            break;
        case 'd':
            flag = 2;
            break;
        case 'w':
            flag = 3;
            break;
        case 's':
            flag = 4;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void logic() {
    Sleep(0.01);
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    case 4:
        x++;
        break;
    default:
        break;
    }
    if (x < 0 || x > width || y < 0 || y > height)
        gameOver = 1;
    for (i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }
    if (x == fruitX && y == fruitY) {
        label3:
        fruitX = rand() % 20;
        if (fruitX == 0)
            goto label3;
        label4:
        fruitY = rand() % 20;
        if (fruitY == 0)
            goto label4;
        score += 10;
        tailLength++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
    }
    return 0;
}
