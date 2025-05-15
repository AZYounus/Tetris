#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
  double currTime = GetTime();
  if (currTime - lastUpdateTime >= interval)
  {
    lastUpdateTime = currTime;
    return true;
  }
  return false;
}

int main() 
{
  Color darkBlue = {44, 44, 127, 255};
  InitWindow(500, 620, "raylib Tetris");
  SetTargetFPS(60);

  Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

  Game game = Game();
  while(WindowShouldClose() == false)
  {
    UpdateMusicStream(game.music);
    game.HandleInput();
    // move current block down by 200 ms
    if (EventTriggered(0.2))
    {
      game.MoveBlockDown();
    }
    // create blank canvas to draw on
    BeginDrawing();

    // wipe previous graphics
    ClearBackground(darkBlue);
    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    if (game.gameOver)
    {
      DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
    }
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

    // convert score from int to string
    char scoreText[10];
    sprintf(scoreText, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
    game.Draw();
    // close canvas
    EndDrawing();
  }

  CloseWindow();
}