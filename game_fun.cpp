#include<iostream>
#include"game_fun.h"
#include<array>
#ifdef _WIN32
	#include<windows.h>
#endif
#include<cstdlib>

using namespace std;
using matrix = array<array<char,3>,3>;

matrix init(){
	matrix res;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			res[i][j] = '_';
		}
	}
	return res;
}

void print_board(matrix &board){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			cout<<board[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

GameResults judge(matrix &board, char sy){
	//GameResults: WIN,ONGOING,DRAW
	
	//row check
	for(int i=0;i<3;++i)
		if(board[i][0]== sy)
			if(board[i][0]==board[i][1] && board[i][1]==board[i][2]) return GameResults::WIN;

	//column check
	for(int j=0;j<3;++j){
		if(board[0][j] == sy)
			if(board[0][j]==board[1][j] && board[1][j] == board[2][j]) return GameResults::WIN;
	}

	//Diagonal check
	if(board[0][0]==sy)
		if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return GameResults::WIN;
	if(board[0][2] == sy)
		if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return GameResults::WIN;

	//Draw check
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j)
			if(board[i][j] != 'X' && board[i][j] !='O') return GameResults::ONGOING;
	}
	return GameResults::DRAW;
}

matrix ch_game_state(matrix& board, int x,int y,char sy){
	//changing the game state
	matrix update = board;
	update[x][y] = sy;
	return update;
}

bool avail(matrix& board,int x,int y){
	if(x>2 || y>2) return false;
	if(board[x][y]=='_') return true;
	return false;
}

void screen_clear(){
#ifdef _WIN32
	int r = system("cls");
#else
	int r = system("clear");
#endif
	(void)r;
}
