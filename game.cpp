#include<iostream>
#include<cstring>
#include<array>

using matrix = std::array<std::array<char,3>,3>;
using namespace std;

matrix ch_game_state(matrix board,int op,char sy);
void print_board(matrix &board);
bool judge(matrix &board,char sy);
int main(){
	matrix board;
	int count = 1;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			board[i][j] = '0'+count;
			++count;
		}
	}

	//Input for player names.
	string p1,p2;
	cout<<"Enter name for p1(X): ";
	getline(cin,p1);
	cout<<"Enter name for p2(O): ";
	getline(cin,p2);

	//game operation.
	int op,turn=0;
	while(true){
		if(turn%2 == 0){
			cout<<p1<<"'s turn"<<endl;
			print_board(board);
			cout<<"Enter your move: ";
			cin>>op;
			board = ch_game_state(board,op,'X');
			system("clear");
			if(judge(board,'X')){
				cout<<p1<<" Won!!!"<<endl;
				break;
			}
		}else{
			cout<<p2<<"'s turn"<<endl;
			print_board(board);
			cout<<"Enter your move: ";
			cin>>op;
			board = ch_game_state(board,op,'O');
			system("clear");
			if(judge(board,'O')){
				cout<<p2<<" Won!!!"<<endl;
				break;
			}
		}
		++turn;
	}
	return 0;
}

matrix ch_game_state(matrix board,int op,char sy){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			if(board[i][j] == '0'+op){
				board[i][j]=sy;
				break;
			}
		}
	}
	return board;
}

void print_board(matrix &board){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			cout<<board[i][j]<<"\t";
		}
		cout<<"\n";
	}
	return;
}

bool judge(matrix &board, char sy){
	for(int i=0;i<3;++i){
		if(board[i][0] == sy)
			if(board[i][0]==board[i][1] && board[i][1]==board[i][2]) return true;
	}
	for(int i=0;i<3;++i){
		if(board[0][i] == sy)
			if(board[0][i]==board[1][i] && board[1][i]==board[2][i]) return true;
	}
	if(board[0][0] == sy)
		if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) return true;

	if(board[0][2]==sy)
		if(board[0][2]==board[1][1] && board[1][1]==board[2][0]) return true;
	return false;
}
