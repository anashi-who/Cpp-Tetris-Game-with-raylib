#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();
    bool paused = false;

    while (WindowShouldClose() == false)
    {
        if (!paused)
        {
            UpdateMusicStream(game.music);
            game.HandleInput();
            if (EventTriggered(0.2))
            {
                game.MoveBlockDown();
            }
        }

        if (IsKeyPressed(KEY_P))
        {
            paused = !paused; // Toggle pause state
        }

        BeginDrawing();
        // Draw a grid-like pattern as background
        for (int x = 0; x < 500; x += 30)
        {
            for (int y = 0; y < 620; y += 30)
            {
                DrawRectangle(x, y, 30, 30, Fade(DARKGRAY, 0.1f));
            }
        }
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
            game.grid.Clear(); // Clear the grid
        }
        else if (paused) // Draw pause menu if paused
        {
            DrawTextEx(font, "PAUSED", {320, 450}, 38, 2, WHITE);
        }
        else // Draw game elements if not paused
        {
            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
            game.Draw();
        }
        EndDrawing();
    }

    CloseWindow();
}
