#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "window.h"
#include "action.h"
#include "texture.h"


bool Check_C(int puntaje[2], int *turno, int mark_tags[3][3]){
    bool Reseteo = false;
    /// triqi ? /////
    int Triqi_h[2] = {0,0};
    int Triqi_v[2] = {0,0};
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
           if(i==j){
                if(mark_tags[i][j] == 1){
                    Triqi_d1[0]++;
                }else if(mark_tags[i][j] == 2){
                    Triqi_d1[1]++;
                }
           }
           if((i+j)==2){
                if(mark_tags[i][j] == 1){
                    Triqi_d2[0]++;
                }else if(mark_tags[i][j] == 2){
                    Triqi_d2[1]++;
                }
           }
        }
        if(Triqi_h[0]==3){
            printf("Triqi_h 1\n");
            puntaje[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_h[1]==3){
            printf("Triqi_h 2\n");
            puntaje[1]++;
            Reseteo = true;
            break;
        }else if(Triqi_v[0]==3){
            printf("Triqi_v 1\n");
            puntaje[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_v[1]==3){
            printf("Triqi_v 2\n");
            puntaje[1]++;
            Reseteo = true;
            break;
        }else if(Triqi_d1[0]==3){
            printf("Triqi_d1 1\n");
            puntaje[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_d1[1]==3){
            printf("Triqi_d1 2\n");
            puntaje[1]++;
            Reseteo = true;
            break;
        }else if(Triqi_d2[0]==3){
            printf("Triqi_d2 1\n");
            puntaje[0]++;
            Reseteo = true;
            break;
        }else if(Triqi_d2[1]==3){
            printf("Triqi_d2 2\n");
            puntaje[1]++;
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
        Reseteo=true;
    }

    return Reseteo;
}

int main( int argc, char* args[] ){
    int SCREEN_WIDTH  = 640;
    int SCREEN_HEIGHT = 480;
    int FONT_SIZE = 20;

    int turno = 1;
    int pantalla_c[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int mark_tags [3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int puntaje[2] = {0, 0};

    bool exit = false;

    std::string PATH_FONT = "asset/font/LiberationMono-Regular.ttf";
    std::string PATH_ICON = "asset/icon.bmp";

    SDL_Point cursor = {1, 1};
    pantalla_c[cursor.x][cursor.y] = 1;
    
    SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_RED   = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Color COLOR_BLUE  = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};


    SDL_Rect Viewport1;
    Viewport1.h = 80;
    Viewport1.w = SCREEN_WIDTH;
    Viewport1.x = 0;
    Viewport1.y = 0;

    SDL_Rect Viewport;
    Viewport.h = SCREEN_HEIGHT - 90;
    Viewport.w = SCREEN_WIDTH  - 90;
    Viewport.x = 45;
    Viewport.y = 80;


    Window window("TIC-TAC-TOE", SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK);
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

            if(action->check_action(action->BUTTON_MOVE_UP)){
                pantalla_c[cursor.y][cursor.x] = 0;
                cursor.y = cursor.y - 1;
                if(cursor.y<0){
                    cursor.y = 2;
                }
                pantalla_c[cursor.y][cursor.x] = 1;
            }else if(action->check_action(action->BUTTON_MOVE_DOWN)){
                pantalla_c[cursor.y][cursor.x] = 0;
                cursor.y = cursor.y + 1;
                if(cursor.y>2){
                    cursor.y = 0;
                }
                pantalla_c[cursor.y][cursor.x] = 1;
            }else if(action->check_action(action->BUTTON_MOVE_LEFT)){
                pantalla_c[cursor.y][cursor.x] = 0;
                cursor.x = cursor.x - 1;
                if(cursor.x<0){
                    cursor.x = 2;
                }
                pantalla_c[cursor.y][cursor.x] = 1;
            }else if(action->check_action(action->BUTTON_MOVE_RIGHT)){
                pantalla_c[cursor.y][cursor.x] = 0;
                cursor.x = cursor.x + 1;
                if(cursor.x>2){
                    cursor.x = 0;
                }
                pantalla_c[cursor.y][cursor.x] = 1;
            }else if(action->check_action(action->BUTTON_ACTION)){
                if(( mark_tags[cursor.y][cursor.x] != 1 ) && ( mark_tags[cursor.y][cursor.x] != 2 ) ){
                    if(turno == 1){
                        mark_tags[cursor.y][cursor.x]  = 1;
                    }else if(turno == -1){
                        mark_tags[cursor.y][cursor.x]  = 2;
                    }
                    turno= turno*-1;
                }
            }



            // Draw


            SDL_RenderSetViewport(text_white.renderer, &Viewport1);

            text_white.render(0, 0, "Jugador 1");
            text_white.render(
                Viewport1.w-text_white.get_text_size("Jugador 1").w, 0, 
                "Jugador 2"
            );

            text_white.render(
                (Viewport1.w/2) - text_white.get_text_size("Jugador 2").w - 5, 0,
                std::to_string(puntaje[0])
            );
            text_white.render(
                (Viewport1.w/2) - text_white.get_text_size(std::to_string(puntaje[0])).w - 5, 0,
                std::to_string(puntaje[1])
            );

            /// abajo ///////////
            SDL_RenderSetViewport(text_white.renderer, &Viewport);

            int x_p=5,y_p=5;

            SDL_Rect rect;
            rect.h = (Viewport.h/3)-10;
            rect.w = (Viewport.w/3)-10;
            rect.x = x_p;
            rect.y = y_p;

            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    rect.x = x_p;
                    rect.y = y_p;
                    if(mark_tags[i][j] == 1){
                        window.draw_rectangle(rect, {73,221,238,0xFF});
                    }
                    if(mark_tags[i][j] == 2){
                        window.draw_rectangle(rect, {12,100,100,0xFF});
                    }
                    if(pantalla_c[i][j] == 1){
                        window.draw_rectangle(rect, COLOR_WHITE);
                    }
                    x_p = x_p + (Viewport.w/3);
                }
                x_p = 5;
                y_p = y_p +(Viewport.h/3);
            }



            window.draw_line(
                {Viewport.w/3,          0},
                {Viewport.w/3, Viewport.h},
                COLOR_WHITE
            );

            window.draw_line(
                {2*(Viewport.w/3),          0},
                {2*(Viewport.w/3), Viewport.h},
                COLOR_WHITE
            );

            window.draw_line(
                {0,          Viewport.h/3},
                {Viewport.w, Viewport.h/3},
                COLOR_WHITE
            );

            window.draw_line(
                {0,          2*(Viewport.h/3)},
                {Viewport.w, 2*(Viewport.h/3)},
                COLOR_WHITE
            );

            SDL_RenderSetViewport(text_white.renderer, nullptr);






            if(Check_C(puntaje, &turno, mark_tags)){
                for (int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        pantalla_c[i][j] = 0;
                    }
                }
                for (int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        mark_tags[i][j] = 0;
                    }
                }
                cursor.x=0;
                cursor.y=0;
                pantalla_c[cursor.y][cursor.x] = 1;
                turno = 1;
            }
            window.update_screen();
        }
    }
    return 0;
}

















