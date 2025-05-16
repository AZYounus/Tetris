#include "game.h"
#include <random>

Game::Game()
{
  grid = Grid();
  blocks = GetAllBlocks();
  currBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  InitAudioDevice();
  music = LoadMusicStream("Sounds/music.mp3");
  PlayMusicStream(music);
  rotateSound = LoadSound("Sounds/rotate.mp3");
  clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{
  // unload music stream and sounds
  UnloadSound(rotateSound);
  UnloadSound(clearSound);
  UnloadMusicStream(music);
  CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
  if (blocks.empty())
  {
    blocks = GetAllBlocks();
  }
  int randIdx = rand() % blocks.size();
  Block block = blocks[randIdx];
  // remove from vector so it is not available
  blocks.erase(blocks.begin() + randIdx);
  return block;
}

std::vector<Block> Game::GetAllBlocks()
{
  return {CrossBlock(), TBlock(), DBlock(), BBlock(), SBlock(), CBlock(), ZBlock()};
}

void Game::Draw()
{
  grid.Draw();
  currBlock.Draw(11, 11);
  switch(nextBlock.id)
  {
    case 3:
      nextBlock.Draw(275, 260);
      break;
    case 4:
      nextBlock.Draw(265, 260);
      break;
    case 6:
      nextBlock.Draw(265, 260);
      break;
    default:
      nextBlock.Draw(270, 260);
      break;
  }
}

void Game::HandleInput()
{
  int keyPressed = GetKeyPressed();

  switch(keyPressed)
  {
    case KEY_LEFT:
      MoveBlockLeft();
      break;
    
    case KEY_RIGHT:
      MoveBlockRight();
      break;

    case KEY_DOWN:
      MoveBlockDown();
      UpdateScore(0, 1);
      break;

    case KEY_UP:
      RotateBlock();
      break;
  }
}

void Game::MoveBlockLeft()
{
  if (!gameOver)
  {
    currBlock.Move(0, -1);
    if (IsBlockOutside() || BlockFits() == false)
    {
      currBlock.Move(0, 1);
    }
  }
}

void Game::MoveBlockRight()
{
  if (!gameOver)
  {
    currBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits() == false)
    {
      currBlock.Move(0, -1);
    }
  }
  
}

void Game::MoveBlockDown()
{
  if (!gameOver)
  {
    currBlock.Move(1, 0);
    if (IsBlockOutside() || BlockFits() == false)
    {
      currBlock.Move(-1, 0);
      LockBlock();
    }
  }
}

bool Game::IsBlockOutside()
{
  std::vector<Position> tiles = currBlock.GetCellPositions();
  // check if any tile of block is outside of grid
  for(Position tile: tiles)
  {
    if (grid.IsCellOutside(tile.row, tile.col))
    {
      return true;
    }
  }
  return false;
}

void Game::RotateBlock()
{
  if (!gameOver)
  {
    currBlock.Rotate();
    if (IsBlockOutside() || BlockFits() == false)
    {
      currBlock.UndoRotation();
    } else
    {
      PlaySound(rotateSound);
    }
  }
}

void Game::LockBlock()
{
  std::vector<Position> tiles = currBlock.GetCellPositions();
  for(Position tile: tiles)
  {
    grid.grid[tile.row][tile.col] = currBlock.id;
  }
  currBlock = nextBlock;
  if (BlockFits() == false)
  {
    gameOver = true;
  }
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  if (rowsCleared > 0)
  {
    PlaySound(clearSound);
    UpdateScore(rowsCleared, 0);
  }
}

bool Game::BlockFits()
{
  std::vector<Position> tiles = currBlock.GetCellPositions();
  for(Position tile: tiles)
  {
    if (grid.IsCellEmpty(tile.row, tile.col) == false)
    {
      return false;
    }
  }
  return true;
}

void Game::Reset()
{
  grid.Initialize();
  blocks = GetAllBlocks();
  currBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
  switch(linesCleared)
  {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 500;
      break;
    default:
      break;
  }

  score += moveDownPoints;
}
