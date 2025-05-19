#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
  public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void Reset();
    bool gameOver;
    int score;
    Music music;
    bool pause;

  private:
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    std::vector<Block> blocks;
    Block currBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};