#include "raylib.h"
#include <stdio.h>

#define WIDTH      820
#define HEIGHT     1000
#define FPS        60
#define BG_COLOR   0x151515ff
#define GRID_COLOR 0x181818ff

#define LETTER_ICON_SIZE  70
#define LETTER_GUESS_SIZE 88
#define SEPARATION        5

#define MAX_ATTEMPTS 6
#define MAX_LETTERS  5

void drawletter(char k, int x, int y, Vector2 size, Color inner_color, Color line_color);

int main()
{
//    const char *word = "apple";
    const char *keyboard = "QWERTYUIOP\nASDFGHJKL\nZXCVBNM";

    SetTraceLogLevel(LOG_NONE);
    InitWindow(WIDTH, HEIGHT, "Raywordle");
    SetTargetFPS(FPS);

    int offsets_x[3] = {};
    offsets_x[0] = 37;
    offsets_x[1] = offsets_x[0] + 38;
    offsets_x[2] = offsets_x[1] + 75;

    char attempts[MAX_ATTEMPTS][MAX_LETTERS] = {0};
    int attempt = 0;
    int letter_idx = 0;

    Rectangle delete_button = { 7*(LETTER_ICON_SIZE + SEPARATION) + (offsets_x[2]), (GetScreenHeight() - LETTER_ICON_SIZE*5) + (3*(LETTER_ICON_SIZE + SEPARATION)), LETTER_ICON_SIZE, LETTER_ICON_SIZE };

    Rectangle grid_container;
    grid_container.width = GetScreenWidth() - 290;
    grid_container.height = GetScreenHeight() - 330;
    grid_container.x = GetScreenWidth()/2 - grid_container.width/2;
    grid_container.y = 10;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(BG_COLOR));
        DrawRectangleRec(grid_container, GetColor(GRID_COLOR));
        DrawRectangleLinesEx(grid_container, 2.0f, GRAY);

        for (int i = 0; i < MAX_LETTERS; ++i)
            for (int j = 0; j < MAX_ATTEMPTS; ++j)
                drawletter(' ', i*(LETTER_GUESS_SIZE + SEPARATION*3) + grid_container.x + 15, j*(LETTER_GUESS_SIZE + SEPARATION*5) + grid_container.y + 8, (Vector2){LETTER_ICON_SIZE, LETTER_ICON_SIZE}, GetColor(BG_COLOR), GRAY);

        int x_offset = 0;
        int y_offset = 0;

        for (int i = 0; keyboard[i]; ++i) {
            if (keyboard[i] == '\n') {
                ++y_offset;
                x_offset = 0;
            }
            else {
                int y = (GetScreenHeight() - LETTER_ICON_SIZE*5) + ((y_offset + 1)*(LETTER_ICON_SIZE + SEPARATION));
                drawletter(keyboard[i], x_offset*(LETTER_ICON_SIZE + SEPARATION) + offsets_x[y_offset], y, (Vector2){LETTER_ICON_SIZE, LETTER_ICON_SIZE}, GRAY, WHITE);
                ++x_offset;
            }
        }
        drawletter('<', delete_button.x, delete_button.y, (Vector2){delete_button.width + 37, delete_button.height}, GRAY, WHITE);
//        DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void drawletter(char k, int x, int y, Vector2 size, Color inner_color, Color line_color)
{
    Rectangle r = {x, y, size.x, size.y};

    const char *text = TextFormat("%c", k);
    Vector2 measure = MeasureTextEx(GetFontDefault(), text, 40.0f, 4);

    DrawRectangleRec(r, inner_color);
    DrawRectangleLinesEx(r, 1.0f, line_color);
    DrawText(text, x + r.width/2 - measure.x/2, y + r.height/2 - measure.y/2, 40, line_color);
}
