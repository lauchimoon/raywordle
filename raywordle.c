#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

#define NUM_BUTTONS 28

typedef struct Button {
    Rectangle box;
    char *text;
    int key;
} Button;

void drawbutton(Button b, Color inner_color, Color line_color);

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

    Button buttons[NUM_BUTTONS] = { 0 };
    Button delete_button = {(Rectangle){7*(LETTER_ICON_SIZE + SEPARATION) + (offsets_x[2]), (GetScreenHeight() - LETTER_ICON_SIZE*5) + (3*(LETTER_ICON_SIZE + SEPARATION)), LETTER_ICON_SIZE + 37, LETTER_ICON_SIZE}, "Delete", KEY_BACKSPACE};
    Button enter_button = {(Rectangle){offsets_x[0], (GetScreenHeight() - LETTER_ICON_SIZE*5) + (3*(LETTER_ICON_SIZE + SEPARATION)), LETTER_ICON_SIZE + 37, LETTER_ICON_SIZE}, "Enter", KEY_ENTER};
    buttons[NUM_BUTTONS - 1] = enter_button;
    buttons[NUM_BUTTONS - 2] = delete_button;

    Rectangle grid_container;
    grid_container.width = GetScreenWidth() - 290;
    grid_container.height = GetScreenHeight() - 330;
    grid_container.x = GetScreenWidth()/2 - grid_container.width/2;
    grid_container.y = 10;

    while (!WindowShouldClose()) {
        for (int i = 0; i < NUM_BUTTONS; ++i)
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i].box) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isalpha(buttons[i].key) && letter_idx < MAX_LETTERS)
                    attempts[attempt][letter_idx++] = buttons[i].key;
                else if (buttons[i].key == KEY_BACKSPACE && letter_idx > 0)
                    attempts[attempt][--letter_idx] = '\0';
                else if (buttons[i].key == KEY_ENTER && letter_idx >= MAX_LETTERS && attempt < MAX_ATTEMPTS) {
                    ++attempt;
                    letter_idx = 0;
                }
            }

        BeginDrawing();
        ClearBackground(GetColor(BG_COLOR));
        DrawRectangleRec(grid_container, GetColor(GRID_COLOR));
        DrawRectangleLinesEx(grid_container, 2.0f, GRAY);

        DrawRectangle(grid_container.x, grid_container.y + attempt*grid_container.height/MAX_ATTEMPTS, grid_container.width, grid_container.height/MAX_ATTEMPTS, Fade(GRAY, 0.4f));

        for (int i = 0; i < MAX_LETTERS; ++i)
            for (int j = 0; j < MAX_ATTEMPTS; ++j) {
                int x = i*(LETTER_GUESS_SIZE + SEPARATION*3) + grid_container.x + 15;
                int y = j*(LETTER_GUESS_SIZE + SEPARATION*5) + grid_container.y + 8;
                Rectangle box = {x, y, LETTER_ICON_SIZE, LETTER_ICON_SIZE};
                DrawRectangleRec(box, GetColor(BG_COLOR));
                DrawRectangleLinesEx(box, 1.0f, GRAY);

                const char *text = TextFormat("%c", attempts[j][i]);
                Vector2 measure = MeasureTextEx(GetFontDefault(), text, 40.0f, 4);
                DrawText(text, x + box.width/2 - measure.x/2, y + box.height/2 - measure.y/2, 40, WHITE);
            }

        int x_offset = 0;
        int y_offset = 0;

        for (int i = 0; keyboard[i]; ++i) {
            if (keyboard[i] == '\n') {
                ++y_offset;
                x_offset = 0;
            }
            else {
                int x = x_offset*(LETTER_ICON_SIZE + SEPARATION) + offsets_x[y_offset];
                int y = (GetScreenHeight() - LETTER_ICON_SIZE*5) + ((y_offset + 1)*(LETTER_ICON_SIZE + SEPARATION));
                char text[2] = { keyboard[i], '\0' };
                buttons[i - y_offset].box = (Rectangle){ x, y, LETTER_ICON_SIZE, LETTER_ICON_SIZE };
                buttons[i - y_offset].text = calloc(2, sizeof(char));
                buttons[i - y_offset].key = keyboard[i];
                strncpy(buttons[i - y_offset].text, text, 2);
                ++x_offset;
            }
        }

        for (int i = 0; i < NUM_BUTTONS; ++i)
            drawbutton(buttons[i], GRAY, WHITE);

        EndDrawing();
    }

    for (int i = 0; i < NUM_BUTTONS - 2; ++i)
        free(buttons[i].text);

    CloseWindow();
    return 0;
}

void drawbutton(Button b, Color inner_color, Color line_color)
{
    int font_size = 30;
    Vector2 measure = MeasureTextEx(GetFontDefault(), b.text, (float)font_size, 4);
    DrawRectangleRec(b.box, inner_color);
    DrawRectangleLinesEx(b.box, 1.0f, line_color);
    DrawText(b.text, b.box.x + b.box.width/2 - measure.x/2, b.box.y + b.box.height/2 - measure.y/2, font_size, line_color);
}
