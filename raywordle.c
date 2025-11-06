#include "raylib.h"
#include <stdio.h>

#define WIDTH    1080
#define HEIGHT   1000
#define FPS      60
#define BG_COLOR 0x181818ff

#define LETTER_ICON_SIZE 80
#define SEPARATION       10

void drawkey(char k, int x, int y);

int main()
{
//    const char *word = "apple";
    const char *keyboard = "QWERTYUIOP\nASDFGHJKL\nZXCVBNM";

    InitWindow(WIDTH, HEIGHT, "Raywordle");
    SetTargetFPS(FPS);

    int offsets_x[3] = {};
    offsets_x[0] = 94;
    offsets_x[1] = offsets_x[0] + 44;
    offsets_x[2] = offsets_x[1] + 90;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(BG_COLOR));
        DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), WHITE);

        int x_offset = 0;
        int y_offset = 0;

        for (int i = 0; keyboard[i]; ++i) {
            if (keyboard[i] == '\n') {
                ++y_offset;
                x_offset = 0;
            }
            else {
                int y = (GetScreenHeight() - LETTER_ICON_SIZE*5) + ((y_offset + 1)*(LETTER_ICON_SIZE + SEPARATION));
                drawkey(keyboard[i], x_offset*(LETTER_ICON_SIZE + SEPARATION) + offsets_x[y_offset], y + 15);
                ++x_offset;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void drawkey(char k, int x, int y)
{
    Rectangle r = {x, y, LETTER_ICON_SIZE, LETTER_ICON_SIZE};

    const char *text = TextFormat("%c", k);
    Vector2 measure = MeasureTextEx(GetFontDefault(), text, 40.0f, 4);

    DrawRectangleRec(r, GRAY);
    DrawRectangleLinesEx(r, 1.0f, WHITE);
    DrawText(text, x + r.width/2 - measure.x/2, y + r.height/2 - measure.y/2, 40, WHITE);
}
