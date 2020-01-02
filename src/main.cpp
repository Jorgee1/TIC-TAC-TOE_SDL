#include <SDL.h>
#include <string>

#include "window.h"
#include "action.h"
#include "texture.h"


int main( int argc, char* args[] ){
    int SCREEN_WIDTH  = 800;
    int SCREEN_HEIGHT = 600;
    int FONT_SIZE     =  20;

    int turn = 1;
    int turn_number = 1;

    bool exit = false;
    bool win_condition = false;

    int board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int score[2] = {0, 0};

    std::string PATH_FONT = "asset/font/LiberationMono-Regular.ttf";
    std::string PATH_ICON = "asset/icon.bmp";
    std::string GAME_NAME = "TIC-TAC-TOE";

    std::string PLAYER1 = "Jugador 1";
    std::string PLAYER2 = "Jugador 2";

    SDL_Point cursor = {1, 1};
    
    SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_RED   = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Color COLOR_BLUE  = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};

    SDL_Color COLOR_P1    = {  73,  221,  238, 0xFF};
    SDL_Color COLOR_P2    = {  12,  100,  100, 0xFF};

    SDL_Rect view_stat = {
        0, 
        0,
        SCREEN_WIDTH,
        FONT_SIZE
    };

    SDL_Rect view_board = {
        45, 
        90,
        SCREEN_WIDTH  - 90,
        SCREEN_HEIGHT - 135
    };

    SDL_Rect mark = {
        view_board.x + 5,
        view_board.y + 5,
        (view_board.w/3) - 10,
        (view_board.h/3) - 10
    };

    Window window(GAME_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK);
    window.set_icon(PATH_ICON);

    TextureText text_white(window.get_render(), PATH_FONT, COLOR_WHITE, FONT_SIZE);

    Action* action = Action::get_instance();
    action->init(
        SDL_SCANCODE_Z,
        SDL_SCANCODE_X,
        SDL_SCANCODE_RETURN,
        SDL_SCANCODE_UP,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT
    );

    while(!exit){
        if(window.check_exit()){
            exit = true;
        }else{
            window.clear_screen();

            // Player actions
            if(action->check_action(action->BUTTON_MOVE_UP)){
                cursor.y = cursor.y - 1;
            }else if(action->check_action(action->BUTTON_MOVE_DOWN)){
                cursor.y = cursor.y + 1;
            }else if(action->check_action(action->BUTTON_MOVE_LEFT)){
                cursor.x = cursor.x - 1;
            }else if(action->check_action(action->BUTTON_MOVE_RIGHT)){
                cursor.x = cursor.x + 1;
            }else if(action->check_action(action->BUTTON_ACTION)){
                if(( board[cursor.y][cursor.x] != 1 ) && ( board[cursor.y][cursor.x] != 2 ) ){
                    if(turn == 1){
                        board[cursor.y][cursor.x]  = 1;
                    }else if(turn == -1){
                        board[cursor.y][cursor.x]  = 2;
                    }
                    turn = turn*-1;
                    turn_number += 1;
                }
            }

            if(cursor.y<0){
                cursor.y = 2;
            }else if(cursor.y>2){
                cursor.y = 0;
            }

            if(cursor.x<0){
                cursor.x = 2;
            }else if(cursor.x>2){
                cursor.x = 0;
            }


            // Draw

            text_white.render(0, 0, PLAYER1);
            text_white.render(
                view_stat.w - text_white.get_text_size(PLAYER1).w, 0, 
                PLAYER2
            );

            text_white.render(
                (view_stat.w/2) - text_white.get_text_size(std::to_string(score[0])).w - 5, 0,
                std::to_string(score[0])
            );
            text_white.render(
                (view_stat.w/2) + text_white.get_text_size(std::to_string(score[1])).w - 5, 0,
                std::to_string(score[1])
            );

            mark.y = view_board.y + 5;
            for(int i=0;i<3;i++){
                mark.x = view_board.x + 5;
                for(int j=0;j<3;j++){
                    if(board[i][j] == 1){
                        window.draw_rectangle(mark, COLOR_P1);
                    }
                    if(board[i][j] == 2){
                        window.draw_rectangle(mark, COLOR_P2);
                    }
                    if((cursor.x==j) && (cursor.y==i)){
                        window.draw_rectangle(mark, COLOR_WHITE);
                    }
                    mark.x = mark.x + (view_board.w/3);
                }
                mark.y = mark.y + (view_board.h/3);
            }



            window.draw_line(
                {
                    view_board.x + view_board.w/3,
                    view_board.y
                },
                {
                    view_board.x + view_board.w/3,
                    view_board.y + view_board.h
                },
                COLOR_WHITE
            );

            window.draw_line(
                {
                    view_board.x + 2*(view_board.w/3),
                    view_board.y
                },
                {
                    view_board.x + 2*(view_board.w/3),
                    view_board.y + view_board.h
                },
                COLOR_WHITE
            );

            window.draw_line(
                {
                    view_board.x,
                    view_board.y + view_board.h/3
                },
                {
                    view_board.x + view_board.w,
                    view_board.y + view_board.h/3
                },
                COLOR_WHITE
            );

            window.draw_line(
                {
                    view_board.x,
                    view_board.y + 2*(view_board.h/3)
                },
                {
                    view_board.x + view_board.w,
                    view_board.y + 2*(view_board.h/3)
                },
                COLOR_WHITE
            );

            window.set_viewport(nullptr);


            // check win condition

            for (int player_id = 1; player_id < 3; ++player_id)
            {
                // Horizontal
                for (int i = 0; i < 3; ++i)
                {
                    if (
                        (board[i][0] == player_id) &&
                        (board[i][1] == player_id) &&
                        (board[i][2] == player_id)
                    ){
                        score[player_id - 1]++;
                        win_condition = true;
                        break;
                    }
                }
                // Vertical

                for (int i = 0; i < 3; ++i)
                {
                    if (
                        (board[0][i] == player_id) &&
                        (board[1][i] == player_id) &&
                        (board[2][i] == player_id)
                    ){
                        score[player_id - 1]++;
                        win_condition = true;
                        break;
                    }
                }
                // Diagonal 1

                if (
                    (board[0][0] == player_id) &&
                    (board[1][1] == player_id) &&
                    (board[2][2] == player_id)
                ){
                    score[player_id - 1]++;
                    win_condition = true;
                }

                // Diagonal 2

                if (
                    (board[0][2] == player_id) &&
                    (board[1][1] == player_id) &&
                    (board[2][0] == player_id)
                ){
                    score[player_id - 1]++;
                    win_condition = true;
                }

            }


            // reset
            if (turn_number == 9){
                win_condition = true;
            }


            if(win_condition){
                win_condition = false;
                for (int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        board[i][j] = 0;
                    }
                }
                cursor.x = 0;
                cursor.y = 0;
                turn     = 1;
                turn_number = 1;
            }

            window.update_screen();
        }
    }
    return 0;
}
