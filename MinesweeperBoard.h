#pragma once

#include "Field.h"
#include "GameMode.h"

class MinesweeperBoard
{
    Field board[100][100];
    int width;
    int height;
    GameState gameState;
    bool firstMove;
    bool debugMode;

    bool isValidPosition(int row, int col) const;
    void clearBoard();
    void applyDefaultLayout();
    void placeRandomMines(int count);
    void placeDebugMines();
    void relocateMine(int row, int col);

public:
    MinesweeperBoard();
    MinesweeperBoard(int width, int height, GameMode mode);

    int getBoardWidth()  const;
    int getBoardHeight() const;
    int getMineCount()   const;

    int  countMines(int row, int col)  const;
    bool hasFlag(int row, int col)     const;
    bool isRevealed(int row, int col)  const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);

    GameState getGameState()           const;
    char      getFieldInfo(int row, int col) const;

    void debug_display() const;
};
