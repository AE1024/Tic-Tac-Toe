#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#define clear "\033[H\033[J"

#define COLOR_GREEN   "\x1b[32m" //player win
#define COLOR_CYAN    "\x1b[36m" //computer win
#define COLOR_RESET   "\x1b[0m" 

char board[3][3];
char PLAYER = 'X';
char COMPUTER = 'O';

void reset_board();
void print_board();
int check_spaces();
void player_move();
void computer_move();
char winner_check();
char check_for_computer(int arr[3][3]);
void print_winner(char);

int main() {
char winner;
char play;
int p,c;

do
{
    //score
    p=0,c=0;
    winner = ' ';
   reset_board();
while (winner==' ' && check_spaces() != 0)
{
    print_board();
    //player move
    player_move();
    winner = winner_check();
    if(winner != ' ' || check_spaces() == 0){
        break;
    }
    //computer move
    computer_move();
    winner = winner_check();
    if(winner != ' ' || check_spaces() == 0){
        break;
    }
}

print_board();
printf("\n");
print_winner(winner);
//score calculation
if(winner==PLAYER){
    p++;
}
else if(winner==COMPUTER){
    c++;
}

printf("Do you want to play again (y/n)? ");
scanf(" %c", &play); 

}while (play=='y' || play=='Y');
printf("\t\tPlayer : %d\t",p);
printf("\tComputer : %d\n",c);

    return 0;
}

void reset_board()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[i][j]=' ';
        }
    }

}
void print_board()
{
    printf(clear);
    printf("  %c  |  %c  |  %c  \n",board[0][0],board[0][1],board[0][2]);
    printf("-----------------\n");
    printf("  %c  |  %c  |  %c  \n",board[1][0],board[1][1],board[1][2]);
    printf("-----------------\n");
    printf("  %c  |  %c  |  %c  \n",board[2][0],board[2][1],board[2][2]);
    printf("\n");

}
int check_spaces()
{
    int free = 9;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] != ' '){
                free--;
            }
        }
    }
    return free;

}
void player_move()
{
    printf("Player move:\n");
    
       int x,y;
       printf("Enter the column and row (1-3)?\n");
       scanf("%d %d", &x, &y);
       x=x-1;
       y=y-1;
       bool correct = true;    
    while(correct){
        if(board[x][y]==' ' && (x<3 && x>=0) && (y<3 && y>=0))
        {
        board[x][y]=PLAYER;
        correct = false;
        return;
        }
else if(board[x][y]!=' ' || board[x][y]=='X' || board[x][y]=='O' || x>3 || x<0 || y>3 || y<0)
        {
        printf("Invalid move\n");
        return player_move();
        }
        
    }

}
void computer_move()
{
    //ai
    printf("Computer move\n");
    int temp[3][3];
    //temp board
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp[i][j]=board[i][j];
        }
    }
    //considering own move
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(temp[i][j] == ' '){
                temp[i][j] = COMPUTER;
                if(check_for_computer(temp)==COMPUTER){
                    board[i][j]=COMPUTER;
                    return;
                }
                else{
                    temp[i][j]=' ';
                }
            }
        }
    }
    //considering player move
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(temp[i][j] == ' '){
                temp[i][j] = PLAYER;
                if(check_for_computer(temp)==PLAYER){
                    temp[i][j]=COMPUTER;
                    return;
                }
                else{
                    board[i][j]= ' ';
                }
            }
        }
    }
    //random move (other option for ai)
    int x,y;
    while(true){
        srand(time(0));
        x = rand()%3;
        y = rand()%3;
        if(board[x][y]==' '){
            board[x][y]=COMPUTER;
            return;
        }

    }

}
char check_for_computer(int arr[3][3])
{
    int i,j;
    for(int i=0;i<3;i++){
        if(board[i][0]==board[i][1] && board[i][0]==board[i][2]){
            return board[i][0];
        }
    }
    //check columns
    for(int j=0;j<3;j++){
        if(board[0][j]==board[1][j] && board[0][j]==board[2][j]){
            return board[0][j];
        }
    }
    //check diagonals
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2]){
        return board[0][0];
    }
    if(board[0][2]==board[1][1] && board[0][2]==board[2][0]){
        return board[0][2];
    }
    //no winner
    else
    return ' ';

}

char winner_check()
{    //check rows
    int i,j;
    for(int i=0;i<3;i++){
        if(board[i][0]==board[i][1] && board[i][0]==board[i][2]){
            return board[i][0];
        }
    }
    //check columns
    for(int j=0;j<3;j++){
        if(board[0][j]==board[1][j] && board[0][j]==board[2][j]){
            return board[0][j];
        }
    }
    //check diagonals
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2]){
        return board[0][0];
    }
    if(board[0][2]==board[1][1] && board[0][2]==board[2][0]){
        return board[0][2];
    }
    //no winner
    else
    return ' ';

}
void print_winner(char winner)
{
    if(winner==PLAYER) 
    printf(COLOR_GREEN "Player won\n" COLOR_RESET);
    else if(winner==COMPUTER) 
    printf(COLOR_CYAN "Computer won\n" COLOR_RESET);
    else if(winner==' ') printf("It's a tie\n");
}