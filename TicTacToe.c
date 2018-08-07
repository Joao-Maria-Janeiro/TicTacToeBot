#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXROWS 3
#define MAXCOLS 3


void user_params(char *casa){
    printf("Chose the house to play: ");
    scanf(" %c", casa);
}

int valid_play(char game_board[MAXCOLS][MAXROWS], char casa){
    for(int i = 0; i < MAXCOLS; i++){
        for(int j = 0; j < MAXROWS; j++){
            if ( casa == game_board[i][j]){
                return 1;
            }
        }
    }
    return 0;
}

void board_update(char game_board[MAXCOLS][MAXROWS], char casa){
    for(int i = 0; i < MAXCOLS; i++){
        for(int j = 0; j < MAXROWS; j++){
            if ( casa == game_board[i][j]){
                game_board[i][j] = 'x';
            }
        }
    }
}

void bot_board_update(char game_board[MAXCOLS][MAXROWS], char casa){
    for(int i = 0; i < MAXCOLS; i++){
        for(int j = 0; j < MAXROWS; j++){
            if ( casa == game_board[i][j]){
                game_board[i][j] = 'o';
            }
        }
    }
}

void board_display(char game_board[MAXCOLS][MAXROWS]){
    system("clear");

    for(int i = 0; i < MAXCOLS; i++){
        for(int j = 0; j < MAXROWS; j++){
            printf(" %c", game_board[i][j]);
            if ( j < 2){
                printf(" |");
            }
        }
        printf("\n");
        if(i < 2){
            printf("-----------");
        }

        printf("\n");
    }
}

int win_game(char game_board[MAXCOLS][MAXROWS]){
    int reps = 0;
    //Player Victory
   for(int i = 0; i < MAXCOLS; i++){
        if( game_board[i][0] == game_board[i][1] && game_board[i][0] == game_board[i][2] && game_board[i][0] == 'x'){
            return 1;
        }
    }

    for(int i = 0; i < MAXROWS; i++){
        if( game_board[0][i] == game_board[1][i] && game_board[0][i] == game_board[2][i] && game_board[0][i] == 'x'){
            return 1;
        }
    }

    if( game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2] && game_board[0][0] == 'x'){
        return 1;
    }

    if( game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0] && game_board[2][0] == 'x'){
        return 1;
    }

    //Bot Victory
    for(int i = 0; i < MAXCOLS; i++){
        if( game_board[i][0] == game_board[i][1] && game_board[i][0] == game_board[i][2] && game_board[i][0] == 'o'){
            return 2;
        }
    }

    for(int i = 0; i < MAXROWS; i++){
        if( game_board[0][i] == game_board[1][i] && game_board[0][i] == game_board[2][i] && game_board[0][i] == 'o'){
            return 2;
        }
    }

    if( game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2] && game_board[0][0] == 'o'){
        return 2;
    }

    if( game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0] && game_board[2][0] == 'o'){
        return 2;
    }

    return -1;
    
    
}


int bot_move(char game_board[MAXCOLS][MAXROWS]){
    int bot_play = 0;
    char bot_play_temp = '0';
    int reps_cols = 0;
    int col = 0;
    int reps_rows = 0;
    int row = 0;
    int i = 0;
    int j = 0;

    //If two 'x' are in a column the bot plays in that column
    for(i = 0;i < MAXCOLS; i++){
        if( (game_board[0][i] == game_board[1][i] && game_board[0][i] == 'x') || (game_board[0][i] == game_board[2][i] && game_board[0][i] == 'x') || (game_board[2][i] == game_board[1][i] && game_board[1][i] == 'x')){
            for( j = 0; j < MAXCOLS; j++){
                if(game_board[j][i] == 'o'){
                    reps_cols = -1;
                }
            }
            reps_cols++;
        }
        if( reps_cols == 1){
            break;
        }
    }

    if(reps_cols == 1){
        col = i;

        for(i = 0; i < MAXCOLS; i++){
            if( game_board[i][col] != 'x'){
                bot_play_temp = game_board[i][col];
                bot_play = bot_play_temp - '0';
            }
        }
    }


    //If two 'x' are in a row the bot plays in that row
    for(i = 0;i < MAXROWS; i++){
        if( (game_board[i][0] == game_board[i][1] && game_board[i][0] == 'x') || (game_board[i][0] == game_board[i][2] && game_board[i][0] == 'x') || (game_board[i][2] == game_board[i][1] && game_board[i][1] == 'x')){
            for( j = 0; j < MAXROWS; j++){
                if(game_board[i][j] == 'o'){
                    reps_rows = -1;
                }
            }
            reps_rows++;
        }
        if( reps_rows == 1){
            break;
        }
    }

    if(reps_rows == 1){
        row = i;

        for(i = 0; i < MAXROWS; i++){
            if( game_board[row][i] != 'x'){
                bot_play_temp = game_board[row][i];
                bot_play = bot_play_temp - '0';
            }
        }
    }

    // Diagonals 
    
    //Left to right Diagonal
    if( game_board[2][2] == '8' ){
        if( (game_board[0][0] == game_board[1][1] && game_board[0][0] == 'x') ){
        bot_play_temp = game_board[2][2];
        bot_play = bot_play_temp - '0';
        }
    }

    if( game_board[0][0] == '0' ){
        if( (game_board[1][1] == game_board[2][2] && game_board[1][1] == 'x') ){
            bot_play_temp = game_board[0][0];
            bot_play = bot_play_temp - '0';
        }
    }

    if( game_board[1][1] == '4' ){
        if( (game_board[2][2] == game_board[0][0] && game_board[2][2] == 'x') ){
            bot_play_temp = game_board[1][1];
            bot_play = bot_play_temp - '0';
        }
    }

    
    //Right to left diagonal
    if( game_board[0][2] == '2' ){
        if( (game_board[2][0] == game_board[1][1] && game_board[2][0] == 'x') ){
            bot_play_temp = game_board[0][2];
            bot_play = bot_play_temp - '0';
        }
    }

    if( game_board[2][0] == '6'){
        if( (game_board[1][1] == game_board[0][2] && game_board[1][1] == 'x') ){
            bot_play_temp = game_board[2][0];
            bot_play = bot_play_temp - '0';
        }
    }

    if( game_board[1][1] == '4'){
        if( (game_board[0][2] == game_board[2][0] && game_board[0][2] == 'x') ){
            bot_play_temp = game_board[1][1];
            bot_play = bot_play_temp - '0';
        }
    }
    
    

    if ( bot_play == 0){
      bot_play = rand()%9;  
    }

    return bot_play;
}

int tied_game(char game_board[MAXCOLS][MAXROWS]){
    int reps = 0;
    for(int i = 0; i < MAXCOLS; i++){
        if((game_board[i][0] == 'o' ||  game_board[i][0] == 'x') && (game_board[i][1] == 'o' ||  game_board[i][1] == 'x') && (game_board[i][2] == 'o' ||  game_board[i][2] == 'x')){
            reps++;
        }
    }
    if(reps == 3){
        return 1;
    }else{
        return 0;
    }
}

void board_copy(char game_board[MAXCOLS][MAXROWS], char aux[MAXCOLS][MAXROWS]){
    for(int i = 0; i < MAXCOLS; i++){
        aux[i][0] = game_board[i][0]; 
        aux[i][1] = game_board[i][1]; 
        aux[i][2] = game_board[i][2];
    }
}

int main(){
    char game_board[MAXROWS][MAXCOLS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    char aux[MAXROWS][MAXCOLS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    int quit = 0;
    char casa = 'n';
    int valid = 0;
    int game_Won = 0;
    int bot_play_temp = -1;
    char bot_play = 'n';
    int bot_valid = 0;
    int tie = 0;

    srand(time(NULL));
    
    
    board_display(game_board); 

    while(quit != 1 && game_Won != 1 && game_Won != 2 && tie != 1){
        user_params(&casa);
        valid = valid_play(game_board, casa);
        if( valid == 1){
            board_update(game_board, casa);
            game_Won = win_game(game_board);
            board_display(game_board);
            tie = tied_game(game_board);
            if(game_Won != 0 & tie != 1){
                while(bot_valid != 1){
                    bot_play_temp = bot_move(game_board);
                    bot_play = bot_play_temp + '0';
                    bot_valid = valid_play(game_board, bot_play);
                    bot_board_update(aux, bot_play);
                    game_Won = win_game(aux);
                    if(game_Won == 1 || game_Won == 2){
                        break;
                    }
                    tie = tied_game(aux);
                    if(tie == 1){
                        break;
                    }
                }
                bot_board_update(game_board, bot_play);
                board_display(game_board);
                board_copy(game_board, aux);
            }

            tie = tied_game(game_board);
            game_Won = win_game(game_board);

        }else{
            printf("\nInvalid play\n");
        }

        if( game_Won == 1){
            printf("\nGame Won\n");
        }

        if( game_Won == 2){
            printf("\nGame Lost\n");
        }

        if(tie == 1 && game_Won != 1 && game_Won != 2){
            printf("\n It's a Tie!\n");
        }

        bot_valid = 0;
        
    } 

}





