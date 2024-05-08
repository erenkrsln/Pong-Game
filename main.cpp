#include "gfx.h"
#include "gridfont.h"

// Funktion zum Zeichnen eines Quadrats auf y, x mit Höhe und Breite
void draw_square(int y, int x, int height, int width)
{
    height -= 1;
    width -= 1;
    // oben
    draw_line(y, x + 1, y, x + width - 1);
    // unten
    draw_line(y + height, x + 1, y + height, x + width - 1);
    // links
    draw_line(y + 1, x, y + height - 1, x);
    // rechts
    draw_line(y + 1, x + width, y + height - 1, x + width);
}

// Funktion zum Drucken des Hinweises, das Spiel zu starten
void printHintToStartGame()
{
    const char start[] = "Press space to start the game";
    move(LINES - 3, (COLS / 2) - strlen(start) / 2);
    printw(start);
    refresh();
}

// Funktion zum Drucken des Spielnamens
void printGamesName()
{
    const char text[] = "Pong Game";
    int tx = COLS / 2;
    int ty = (LINES - 4) / 2 + 1;
    init_grid_font();
    draw_grid_text(ty - get_grid_char_lines() / 2, tx - strlen(text) * get_grid_char_cols() / 2, text);
    refresh();
}

// Funktion zum Drucken der Spielregeln und Tastensteuerung
void printGameRules()
{
    move(2, 3);
    printw("Game rules: \n\n   Players control paddles on opposite sides of the screen \n   and try to bounce the ball past their opponent's paddle. \n   The first player to reach a certain score wins the game. \n\n   Player 1 controls their paddle with 'W' to move up and 'S' \n   to move down, while Player 2 uses the up and down arrow keys.");

    draw_square(1, 1, 10, 67); // Aufruf der draw_square Funktion
}

// Funktion zum Zeichnen der Spielintro
void intro()
{
    initscr();
    init_color(); // Hier wird init_color() aus gfx.h aufgerufen
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    printGamesName();
    printHintToStartGame();
    printGameRules();

    int input = tolower(getch());

    while (input != ' ')
    {
        if (input == 'q')
        {
            exit_gfx();
            exit(0);
        }
        msleep(1);

        input = tolower(getch());
    }

    clear();
    endwin();
}

int main()
{
    // initialize frameworks
    init_gfx();

    // display intro
    intro();

    // exit gfx framework
    exit_gfx();

    return 0;
}
