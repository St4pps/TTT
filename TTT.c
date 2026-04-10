#include <stdio.h>
#include <stdbool.h>

int main(){
int choose = 0; ; // players choice on where to mark
int player = 0; // tracks players 
int turn = 1;  // tracks turns by even and odd
int moves = 0; // Tracks each move to see if the players hit the max and tie. 
bool end = false; 
int table[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}}; //3x3 table



while(end == false){ //ends when false
turn++; //turns increment 
moves++; //moves increments to count them 

    if(turn%2 == 0){
    player = 1;
}
else{
    player = 2;
}

printf("Player %d please input a number seen above\n",player); 
scanf("%d",&choose); 

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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player); 
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
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
        printf("Player %d, stop cheating, you must pick a sqaure that has not been chosen.\n Turn lost\n", player);  
    } 
    break; 
    default:
    printf("Please choose the a sqaure that actually exists, turn lost\n"); 


}

if(table[0][0] == player && table[0][1] == player && table[0][2] == player|| 
    table[1][0] == player && table[1][1] == player && table[1][2] == player || 
    table[2][0] == player &&table[2][1] == player &&table[2][2] == player ||
    table[0][0] == player && table[1][1] == player && table[2][2] == player ||
    table[0][2] == player && table[1][1] == player && table[2][0]== player){

    printf("The victor is player %d\n",player); 
    end = true; 
}else if(moves == 9 && end == false){
    printf("Tie\n");
    end = true;

}else{
    printf("next players turn\n"); 
}

}

}