#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 20

int x, y;
int obstacleX;
int jumping;
int gameOver;
int score;

void setup() {
    x = SCREEN_WIDTH / 4;
    y = SCREEN_HEIGHT - 4;
    obstacleX = SCREEN_WIDTH - 5;
    jumping = 0;
    gameOver = 0;
    score = 0;
}

void draw() {
    system("clear");
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (i == y && j == x) {
                printf("R");
            } else if (i == SCREEN_HEIGHT - 1) {
                printf("_");
            } else if (i == SCREEN_HEIGHT - 2 && (j == obstacleX || j == obstacleX + 1)) {
                printf("+");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    if (ch == ' ' && !jumping) {
        jumping = 1;
        y -= 3;
    } else if (ch == 'x') {
        gameOver = 1;
    }
}

void update() {
    if (jumping) {
        y++;
        if (y == SCREEN_HEIGHT - 4) {
            jumping = 0;
        }
    }
    obstacleX--;
    if (obstacleX == 0) {
        obstacleX = SCREEN_WIDTH - 5;
        score++;
    }
    if ((y == SCREEN_HEIGHT - 1 && (x == obstacleX || x == obstacleX + 1)) || y >= SCREEN_HEIGHT - 1) {
        gameOver = 1;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        update();
        usleep(50000);
    }
    printf("Game Over! Your score: %d\n", score);
    return 0;
}
