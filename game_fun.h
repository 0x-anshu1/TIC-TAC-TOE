#pragma once
#ifndef GAME_FUN_H
#define GAME_FUN_H

#include<array>

using matrix = std::array<std::array<char,3>,3>;
enum class GameResults{WIN,ONGOING,DRAW};

matrix init();
void print_board(matrix &board);
GameResults judge(matrix &board,char sy);
matrix ch_game_state(matrix& board,int x,int y,char sy);

bool avail(matrix &board,int x,int y);

#endif
