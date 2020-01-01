#include <SDL2/SDL.h>
#include <string>

#include "window.h"
#include "action.h"
#include "texture.h"


bool check_board(int score[2], int *turno, int mark_tags[3][3]){
    bool Reseteo = false;
    /// triqi ? /////
    int Triqi_h[2]  = {0,0};
    int Triqi_v[2]  = {0,0};
    int Triqi_d1[2] = {0,0};
    int Triqi_d2[2] = {0,0};

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           /// horizontal ///////////////
           if(mark_tags[i][j] == 1){
                Triqi_h[0]++;
           }else if(mark_tags[i][j] == 2){
                Triqi_h[1]++;
           }
           /// vertical ///////////////
           if(mark_tags[j][i] == 1){
                Triqi_v[0]++;
           }else if(mark_tags[j][i] == 2){
                Triqi_v[1]++;
           }
           /// diagonal? ///////////////
           if(i == j){
                if(mark_tags[i][j] == 1){
                    Triqi_d1[0]++;
                }else if(mark_tags[i][j] == 2){
                    Triqi_d1[1]++;
                }
           }
           if((i+j) == 2){
                if(mark_tags[i][j] == 1){
                    Triqi_d2[0]++;
                }else if(mark_tags[i][j] == 2){
                    Triqi_d2[1]++;
                }
           }
        }
        if(Triqi_h[0] == 3){
            printf("Triqi_h 1\n");
            score[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_h[1] == 3){
            printf("Triqi_h 2\n");
            score[1]++;
            Reseteo = true;
            break;
        }else if(Triqi_v[0] == 3){
            printf("Triqi_v 1\n");
            score[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_v[1] == 3){
            printf("Triqi_v 2\n");
            score[1]++;
            Reseteo = true;
            break;
        }else if(Triqi_d1[0] == 3){
            printf("Triqi_d1 1\n");
            score[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_d1[1] == 3){
            printf("Triqi_d1 2\n");
            score[1]++;
            Reseteo = true;
            break;
        }else if(Triqi_d2[0] == 3){
            printf("Triqi_d2 1\n");
            score[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_d2[1] == 3){
            printf("Triqi_d2 2\n");
            score[1]++;
            Reseteo = true;
            break;
        }else{
            Triqi_h[0] = 0;
            Triqi_h[1] = 0;
            Triqi_v[0] = 0;
            Triqi_v[1] = 0;
        }
    }
    /// se lleno? /////////////
    int Zeros = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           if(mark_tags[i][j] == 0){
                Zeros++;
           }
        }
    }
    if(Zeros == 0){
        Reseteo = true;
    }

    return Reseteo;
}

int main( int argc, char* args[] ){
    int SCREEN_WIDTH  = 640;
    int SCREEN_HEIGHT = 480;
    int FONT_SIZE     =  20;

    int turn = 1;
    bool exit = false;

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
        80
    };

    SDL_Rect view_board = {
        45, 
        80,
        SCREEN_WIDTH  - 90,
        SCREEN_HEIGHT - 90
    };

    SDL_Rect mark = {
        5,
        5,
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
                    turn= turn*-1;
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



            mark.y = 5;
            for(int i=0;i<3;i++){
                mark.x = 5;
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
                {view_board.w/3,            0},
                {view_board.w/3, view_board.h},
                COLOR_WHITE
            );

            window.draw_line(
                {2*(view_board.w/3),            0},
                {2*(view_board.w/3), view_board.h},
                COLOR_WHITE
            );

            window.draw_line(
                {0,            view_board.h/3},
                {view_board.w, view_board.h/3},
                COLOR_WHITE
            );

            window.draw_line(
                {0,            2*(view_board.h/3)},
                {view_board.w, 2*(view_board.h/3)},
                COLOR_WHITE
            );

            window.set_viewport(nullptr);


            // check state
            if(check_board(score, &turn, board)){
                for (int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        board[i][j] = 0;
                    }
                }
                cursor.x = 0;
                cursor.y = 0;
                turn     = 1;
            }
            window.update_screen();
        }
    }
    return 0;
}
