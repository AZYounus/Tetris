#include "block.h"
#include "position.h"

class CrossBlock : public Block
{
  public:
    CrossBlock()
    {
      id = 1;
      cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2), Position(2,1)};
      Move(0, 3);
    }
};

class TBlock : public Block
{
  public:
    TBlock()
    {
      id = 2;
      cells[0] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 1), Position(2,1)};
      cells[1] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2), Position(2,2)};
      cells[2] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1), Position(2,2)};
      cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2), Position(2,0)};
      Move(0, 3);
    }
};

class DBlock : public Block
{
  public:
    DBlock()
    {
      id = 3;
      cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0), Position(2, 1)};
      cells[1] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
      cells[2] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
      cells[3] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 1), Position(1, 2)};
      Move(0, 3);
    }
};

class BBlock : public Block
{
  public:
    BBlock()
    {
      id = 4;
      cells[0] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1), Position(2, 2)};
      cells[1] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
      cells[2] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 2)};
      cells[3] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)};
      Move(0, 3);
    }
};

class SBlock : public Block
{
  public:
    SBlock()
    {
      id = 5;
      cells[0] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 0), Position(2, 1)};
      cells[1] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
      Move(0, 3);
    }
};

class CBlock : public Block
{
  public:
    CBlock()
    {
      id = 6;
      cells[0] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1), Position(2, 2)};
      cells[1] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 2)};
      cells[2] = {Position(0, 1), Position(0, 2), Position(1, 2), Position(2, 1), Position(2, 2)};
      cells[3] = {Position(1, 0), Position(1, 2), Position(2, 0), Position(2, 1), Position(2, 2)};
      Move(0, 3);
    }
};

class ZBlock : public Block
{
  public:
    ZBlock()
    {
      id = 7;
      cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
      cells[1] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
      Move(0, 3);
    }
};