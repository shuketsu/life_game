#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    assume_default_colors(COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    bkgd(COLOR_PAIR(1));

    int height, width;
    getmaxyx(stdscr, height, width);

    int (*grid)[width] = malloc(sizeof(int[height][width]));
    int (*new_grid)[width] = malloc(sizeof(int[height][width]));

    if (!grid || !new_grid) {
        endwin();
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = (rand() % 100 < 15) ? 1 : 0;
        }
    }

    while (getch() == ERR) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int neighbors = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (i == 0 && j == 0) continue;
                        int ny = (y + i + height) % height;
                        int nx = (x + j + width) % width;
                        neighbors += grid[ny][nx];
                    }
                }

                if (grid[y][x] == 1) {
                    new_grid[y][x] = (neighbors == 2 || neighbors == 3);
                } else {
                    new_grid[y][x] = (neighbors == 3);
                }
            }
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x] = new_grid[y][x];
                if (grid[y][x]) {
                    attron(A_REVERSE);
                    mvaddch(y, x, ' ');
                    attroff(A_REVERSE);
                } else {
                    mvaddch(y, x, ' ');
                }
            }
        }

        refresh();
        usleep(60000);
    }

    free(grid);
    free(new_grid);
    endwin();
    return 0;
}
