#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<array>
#include"game_fun.h"

using namespace std;
using matrix = array<array<char,3>,3>;

int main(){
	int sersock = socket(AF_INET,SOCK_STREAM,0);
	if(sersock<0){
		perror("socket");
		return 1;
	}

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8000);

	if(bind(sersock,(struct sockaddr*) &server,sizeof(server))<0){
		perror("bind");
		close(sersock);
		return 1;
	}

	if(listen(sersock,5)<0){
		perror("listen");
		close(sersock);
		return 1;
	}

	cout<<"!!!!TIC-TAC-TOE!!!!"<<endl;
	cout<<"You are player1(P1,'X')."<<endl;
	cout<<"Waiting for player2(P2,'O')."<<endl;

	int clientsock = accept(sersock,nullptr,nullptr);
	if(clientsock<0){
		perror("accept");
		close(sersock);
		return 1;
	}

	 cout<<"P2 is ready.Game Start:"<<endl;
	 matrix board = init();
	 char buffer[1024];
	 int x,y;
	 print_board(board);
	 cout<<"Enter your move: X-";
	 cin>>x;
	 cout<<"Y-";
	 cin>>y;
	 while(!avail(board,x,y)){
		 cout<<"Entered wrong move. Pls re-enter."<<endl;
		 cout<<"X-";
		 cin>>x;
		 cout<<"Y-";
		 cin>>y;
	 }
	 board = ch_game_state(board,x,y,'X');
	 screen_clear();
	 print_board(board);
	 while(true){
		 memset(buffer,0,sizeof(buffer));
		 buffer[0]='0'+x;
		 buffer[1]='0'+y;
		 GameResults g;

		 ssize_t sen = send(clientsock,buffer,sizeof(buffer),0);
		 if(sen<0){
			 perror("send");
			 break;
		 }
			
		 cout<<"P2(O)'s turn"<<endl;
		 memset(buffer,0,sizeof(buffer));
		 ssize_t rec = recv(clientsock,buffer,sizeof(buffer),0);
		 if(rec<0){
			 perror("recv");
			 break;
		 }

		 x=buffer[0]-'0';
		 y=buffer[1]-'0';
		 board = ch_game_state(board,x,y,'O');
		 screen_clear();
		 print_board(board);
		 g = judge(board,'O');
		 if(g==GameResults::WIN){
			 cout<<"P2(O) won."<<endl;
			 break;
		 }else if(g==GameResults::DRAW){
			 cout<<"Game Over. DRAW."<<endl;
			 break;
		 }

		 cout<<"Enter your move(X):"<<endl;
		 cout<<"X: ";
		 cin>>x;
		 cout<<"Y: ";
		 cin>>y;
		 while(!avail(board,x,y)){
			 cout<<"The entered move is invalid. Pls enter a correct move:"<<endl;
			 cout<<"X: ";
			 cin>>x;
			 cout<<"Y: ";
			 cin>>y;
		 }
		 board=ch_game_state(board,x,y,'X');
		 screen_clear();
		 print_board(board);
		 g=judge(board,'X');
		 if(g==GameResults::WIN){
			 cout<<"You Won!!!"<<endl;
			 break;
		 }else if(g==GameResults::DRAW){
			 cout<<"Game Over.DRAW"<<endl;
			 break;
		 }
	 }
	 close(clientsock);
	 close(sersock);
	 return 0;
}
