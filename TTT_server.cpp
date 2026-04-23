#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080


int main(){
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    if (listen(server_fd, 2) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("Waiting for players...\n");
    
//players 
int player1, player2; 
int current_socket; 

player1 = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
printf("Player 1 connected\n");

player2 = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
printf("Player 2 connected\n");

const char *start1 = "Game started for Player 1.\n";
const char *start2 = "Game started for Player 2. Waiting for Player 1...\n";

send(player1, start1, strlen(start1), 0);
send(player2, start2, strlen(start2), 0);

int choose; // players choice on where to mark
int player; // tracks players 
int turn = 0;  // tracks turns by even and odd
int moves = 0; // Tracks each move to see if the players hit the max and tie. 
bool end = false; 
int table[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}}; //3x3 table
char buffer[BUFFER_SIZE]; 

//main game decisions
while(!end){ //ends when false

int validMove = 1; 

//decides player based on turn
    if(turn%2 == 0){
    player = 1;
    current_socket = player1; 
    const char *p1turn = "Player 1. Enter number between 1 and 9:\n";
    const char *wait1 = "Waiting for Player 1...\n";

send(player1, p1turn, strlen(p1turn), 0);
send(player2, wait1, strlen(wait1), 0);
}
else{
    player = 2;
    current_socket = player2; 
    const char *p2turn = "Player 2. Enter number between 1 and 9:\n";
const char *wait2 = "Waiting for Player 2...\n";

send(player2, p2turn, strlen(p2turn), 0);
send(player1, wait2, strlen(wait2), 0);
}

//input
memset(buffer, 0, BUFFER_SIZE);
int bytes = read(current_socket, buffer, BUFFER_SIZE - 1);

if (bytes <= 0) {
    printf("Player disconnected.\n");
    break;
}

buffer[bytes] = '\0';
choose = atoi(buffer);

if (choose < 1 || choose > 9) {
    validMove = 0;
}

switch(choose){ //switch statement to keep track of player input in matrix.
    case 1: 
   if(table[0][0] == 0){
    if(player == 1){
    table[0][0] = 1;  
    }
    else if(player == 2){
    table[0][0] = 2; 
    }
    }else{
       validMove = 0; 
    }
    break; 
    case 2:
    if(table[0][1] == 0){
    if(player == 1){
    table[0][1] = 1;  
    }
    else if(player == 2){
    table[0][1] = 2; 
    }  
}else{
       validMove = 0;  
    }
    break; 
    case 3:
   if(table[0][2] == 0){
   if(player == 1){
    table[0][2] = 1;  
    }
    else if(player == 2){
    table[0][2] = 2; 
    }  
    }else{
       validMove = 0;  
    }
    break; 
    case 4: 
   if(table[1][0] == 0){
    if(player == 1){
    table[1][0] = 1;  
    }
    else if(player == 2){
    table[1][0] = 2; 
    } 
    }else{
       validMove = 0;  
    }

    break; 
    case 5: 
    if(table[1][1] == 0){
    if(player == 1){
    table[1][1] = 1;  
    }
    else if(player == 2){
    table[1][1] = 2; 
    } 
    }else{
       validMove = 0;  
    }
    break; 
    case 6: 
    if(table[1][2] == 0){
    if(player == 1){
    table[1][2] = 1;  
    }
    else if(player == 2){
    table[1][2] = 2; 
    } 
    }else{
       validMove = 0;  
    }
    break; 
    case 7: 
    if(table[2][0] == 0){
    if(player == 1){
    table[2][0] = 1;  
    }
    else if(player == 2){
    table[2][0] = 2; 
    } 
    }else{
       validMove = 0;  
    }
    break; 
    case 8: 
    if(table[2][1] == 0){
    if(player == 1){
    table[2][1] = 1;  
    }
    else if(player == 2){
    table[2][1] = 2; 
    }
    }else{
       validMove = 0;  
    } 
    break; 
    case 9: 
    if(table[2][2] == 0){
    if(player == 1){
    table[2][2] = 1;  
    }
    else if(player == 2){
    table[2][2] = 2; 
    }  
    }else{
       validMove = 0;  
    } 
    break; 
    default:
    validMove = 0; 
}

//sees if player has input a valid move
if(!validMove){
    const char *invalid = "Invalid, please choose a non occupied space\n";
    send(current_socket, invalid, strlen(invalid), 0);
    continue; 
}

moves++;
turn++;


if((//straight forward
    table[0][0]==player && table[0][1]==player && table[0][2]==player) ||
    (table[1][0]==player && table[1][1]==player && table[1][2]==player) ||
    (table[2][0]==player && table[2][1]==player && table[2][2]==player) ||

    // column
    (table[0][0]==player && table[1][0]==player && table[2][0]==player) ||
    (table[0][1]==player && table[1][1]==player && table[2][1]==player) ||
    (table[0][2]==player && table[1][2]==player && table[2][2]==player) ||

    // diagonal
    (table[0][0]==player && table[1][1]==player && table[2][2]==player) ||
    (table[0][2]==player && table[1][1]==player && table[2][0]==player)){


char victMessage[50];
sprintf(victMessage, "Player %d VICTORY\n", player);

send(player1, victMessage, strlen(victMessage), 0);
send(player2, victMessage, strlen(victMessage), 0);
    end = true; 
}else if(moves == 9 && end == false){

   const char *drawMsg = "Game is a draw.\n";
send(player1, drawMsg, strlen(drawMsg), 0);
send(player2, drawMsg, strlen(drawMsg), 0);
    end = true;

}else{
    printf("next players turn\n"); 
}

}
close(player1); 
close(player2); 
close(server_fd); 

return 0;
}
