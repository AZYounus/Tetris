#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

typedef enum GameScreen { START = 0, GAMEPLAY, ENDING } GameScreen;
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
  GameScreen currScreen = START;

  Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

  Game game = Game();
  while(WindowShouldClose() == false)
  {
    switch(currScreen) {
      case START:
      {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
          Vector2 mousePosition = GetMousePosition();
          if (mousePosition.x >= 190 && mousePosition.x <= 306 && mousePosition.y >= 320 && mousePosition.y <= 358)
          {
            currScreen = GAMEPLAY;
          }
        }
      } break;
      case GAMEPLAY:
      {
        if (game.gameOver)
        {
          currScreen = ENDING;
        }
      } break;
      case ENDING:
      {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
          Vector2 mousePosition = GetMousePosition();
          if (mousePosition.x >= 165 && mousePosition.x <= 324 && mousePosition.y >= 480 && mousePosition.y <= 518)
          {
            currScreen = GAMEPLAY;
            game.gameOver = false;
            game.Reset();
          }
        }
      } break;
      default: break;
    }

    // create blank canvas to draw on
    BeginDrawing();

    // wipe previous graphics
    ClearBackground(darkBlue);

    switch(currScreen)
    {
      case START:
      {
        DrawTextEx(font, "TETRIS", {184, 120}, 44, 2, WHITE);
        DrawRectangleRounded({190, 320, 116, 38}, 0.3, 6, lightBlue);
        DrawTextEx(font, "START", {201, 320}, 38, 2, WHITE);
        DrawTextEx(font, "Press START to play", {80, 375}, 34, 2, WHITE);
      } break;
      case GAMEPLAY:
      {
        UpdateMusicStream(game.music);
        game.HandleInput();
        // move current block down by 200 ms
        if (EventTriggered(0.2))
        {
          game.MoveBlockDown();
        }
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        // convert score from int to string
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
      } break;
      case ENDING:
      {
        DrawTextEx(font, "GAME OVER", {150, 200}, 44, 2, WHITE);
        DrawTextEx(font, "Score", {205, 15}, 38, 2, WHITE);
        DrawRectangleRounded({165, 55, 170, 60}, 0.3, 6, lightBlue);
        
        // convert score from int to string
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {165 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);

        DrawRectangleRounded({165, 480, 158, 38}, 0.3, 6, lightBlue);
        DrawTextEx(font, "RESTART?", {171, 480}, 38, 2, WHITE);
      }
    }

    // close canvas
    EndDrawing();
  }

  CloseWindow();
}