#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 30
#define HEIGHT 10

int x, y;
int ballX, ballY;
int dirX, dirY;
int paddle;

void setup() {
    x = 2;
    y = HEIGHT / 2;
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    dirX = 1;
    dirY = 1;
    paddle = HEIGHT / 2;
}

void draw() {
    int i;
    clear();
    // Draw top border
    for (i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "-");
    // Draw bottom border
    for (i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "-");
    // Draw left and right borders
    for (i = 1; i < HEIGHT + 1; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, WIDTH + 1, "|");
    }
    // Draw paddle
    for (i = 0; i < 4; i++)
        mvprintw(paddle - 1 + i, x, "#");
    // Draw ball
    mvprintw(ballY, ballX, "O");
    // Print score
    mvprintw(HEIGHT + 2, 0, "Score: 0");
    refresh();
}

void input() {
    int ch = getch();
    if (ch == 'w')
        paddle--;
    if (ch == 's')
        paddle++;
}

void logic() {
    ballX += dirX;
    ballY += dirY;
    // Ball collision with top/bottom borders
    if (ballY == 0 || ballY == HEIGHT + 1)
        dirY = -dirY;
    // Ball collision with left paddle
    if (ballX == x + 1 && ballY >= paddle - 1 && ballY <= paddle + 2)
        dirX = -dirX;
    // Ball collision with right wall
    if (ballX == WIDTH + 1) {
        setup();
    }
}

int main() {
    int score = 0;
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);

    setup();

    while (1) {
        draw();
        input();
        logic();
        usleep(10000);
    }
    endwin();
    return 0;
}

