#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"game_fun.h"
#include<array>

using namespace std;
using matrix = array<array<char,3>,3>;

int main(){
	int clientsock = socket(AF_INET,SOCK_STREAM,0);
	if(clientsock<0){
		perror("socket");
		return 1;
	}

	sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(8000);

	if(connect(clientsock,(struct sockaddr*)&client, sizeof(client))<0){
		perror("client");
		return 1;
	}

	cout<<"Welcome to TIC-TAC-TOE!!!!"<<endl;
	cout<<"You are player2(P2,'O')."<<endl;

	matrix board=init();
	int x,y;
	char buffer[1024];
	print_board(board);
	cout<<"P1(X)'s turn."<<endl;
	while (true){
		ssize_t r=recv(clientsock,buffer,sizeof(buffer),0);
		if(r<0){
			perror("recv");
			break;
		}
		x=buffer[0]-'0';
		y=buffer[1]-'0';
		board = ch_game_state(board,x,y,'X');
		screen_clear();
		print_board(board);
		GameResults g;
		g=judge(board,'X');
		if(g==GameResults::WIN){
			cout<<"P1 Won!!!!"<<endl;
			break;
		}else if(g==GameResults::DRAW){
			cout<<"GAME OVER.DRAW"<<"\n";
			break;
		}

		cout<<"Enter your move:"<<"\n";
		cout<<"X: ";
		cin>>x;
		cout<<"Y: ";
		cin>>y;
		while(!avail(board,x,y)){
			cout<<"You have entered a wrong move. PLS re-enter:";
			cout<<"X:";
			cin>>x;
			cout<<"Y:";
			cin>>y;
		}
		board=ch_game_state(board,x,y,'O');
		memset(buffer,0,sizeof(buffer));
		buffer[0]='0'+x;
		buffer[1]='0'+y;
		ssize_t se = send(clientsock,buffer,sizeof(buffer),0);
		if(se<0){
			perror("send");
			break;
		}
		screen_clear();
		print_board(board);
		g=judge(board,'O');

		if(g==GameResults::WIN){
			cout<<"You Won!!!!"<<"\n";
			cout<<"Game Over";
			break;
		}else if(g==GameResults::DRAW){
			cout<<"Game Over.DRAW";
			break;
		}
		memset(buffer,0,sizeof(buffer));
		cout<<"P1(X)'s turn."<<endl;
	}
	close(clientsock);
	return 0;
}
