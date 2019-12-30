#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <sstream>
#include <cstdlib>

#include "window.h"
#include "action.h"
#include "texture.h"

int Pantalla_C[3][3];
int x_c=0,y_c=0;
int Mark_Tags[3][3];

void Reset(int *turno){
    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            Pantalla_C[i][j] = 0;
        }
    }
    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            Mark_Tags[i][j] = 0;
        }
    }
    x_c=0,y_c=0;
    Pantalla_C[y_c][x_c] = 1;
    *turno = 1;
}

void Check_C(int puntaje[2],int *turno){
    bool Reseteo = false;
    /// triqi ? /////
    int Triqi_h[2] = {0,0};
    int Triqi_v[2] = {0,0};
    int Triqi_d1[2] = {0,0};
    int Triqi_d2[2] = {0,0};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           /// horizontal ///////////////
           if(Mark_Tags[i][j] == 1){
                Triqi_h[0]++;
           }else if(Mark_Tags[i][j] == 2){
                Triqi_h[1]++;
           }
           /// vertical ///////////////
           if(Mark_Tags[j][i] == 1){
                Triqi_v[0]++;
           }else if(Mark_Tags[j][i] == 2){
                Triqi_v[1]++;
           }
           /// diagonal? ///////////////
           if(i==j){
                if(Mark_Tags[i][j] == 1){
                    Triqi_d1[0]++;
                }else if(Mark_Tags[i][j] == 2){
                    Triqi_d1[1]++;
                }
           }
           if((i+j)==2){
                if(Mark_Tags[i][j] == 1){
                    Triqi_d2[0]++;
                }else if(Mark_Tags[i][j] == 2){
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
           if(Mark_Tags[i][j] == 0){
                Zeros++;
           }
        }
    }
    if(Zeros == 0){
        Reseteo=true;
    }
    if(Reseteo==true){
        Reset(&*turno);
    }
}

void SDL_Teclado(int *turno, Action* action ){


    if(action->check_action(action->BUTTON_MOVE_UP)){
        Pantalla_C[y_c][x_c] = 0;
        y_c = y_c - 1;
        if(y_c<0){
            y_c = 2;
        }
        Pantalla_C[y_c][x_c] = 1;
    }else if(action->check_action(action->BUTTON_MOVE_DOWN)){
        Pantalla_C[y_c][x_c] = 0;
        y_c = y_c + 1;
        if(y_c>2){
            y_c = 0;
        }
        Pantalla_C[y_c][x_c] = 1;
    }else if(action->check_action(action->BUTTON_MOVE_LEFT)){
        Pantalla_C[y_c][x_c] = 0;
        x_c = x_c - 1;
        if(x_c<0){
            x_c = 2;
        }
        Pantalla_C[y_c][x_c] = 1;
    }else if(action->check_action(action->BUTTON_MOVE_RIGHT)){
        Pantalla_C[y_c][x_c] = 0;
        x_c = x_c + 1;
        if(x_c>2){
            x_c = 0;
        }
        Pantalla_C[y_c][x_c] = 1;
    }else if(action->check_action(action->BUTTON_ACTION)){
        if(( Mark_Tags[y_c][x_c] != 1 ) && ( Mark_Tags[y_c][x_c] != 2 ) ){
            if(*turno == 1){
                Mark_Tags[y_c][x_c]  = 1;
            }else if(*turno == -1){
                Mark_Tags[y_c][x_c]  = 2;
            }
            *turno = (*turno)*-1;
        }
    }
   
}

void Impresor_Pantalla(TextureText* text, Window* window, int turno,int puntaje[2]){

    SDL_Rect Viewport1;
    Viewport1.h = 80;
    Viewport1.w = window->SCREEN_WIDTH;
    Viewport1.x = 0;
    Viewport1.y = 0;
    SDL_RenderSetViewport(text->renderer, &Viewport1);

    text->render(0, 0, "Jugador 1");
    text->render((Viewport1.w-text->get_text_size("Jugador 1").w), 0, "Jugador 2");

    text->render(((Viewport1.w)/2)-text->get_text_size("Jugador 2").w-5, 0, std::to_string(puntaje[0]));
    text->render(((Viewport1.w)/2)-text->get_text_size(std::to_string(puntaje[0])).w-5, 0, std::to_string(puntaje[1]));

    /// abajo ///////////
    SDL_Rect Viewport;
    Viewport.h = window->SCREEN_HEIGHT - 90;
    Viewport.w = window->SCREEN_WIDTH  - 90;
    Viewport.x = 45;
    Viewport.y = 80;
    SDL_RenderSetViewport(text->renderer, &Viewport);

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
            if(Mark_Tags[i][j] == 1){
                SDL_SetRenderDrawColor(text->renderer,73,221,238,0xFF);
                SDL_RenderFillRect(text->renderer,&rect);
            }
            if(Mark_Tags[i][j] == 2){
                SDL_SetRenderDrawColor(text->renderer,12,100,100,0xFF);
                SDL_RenderFillRect(text->renderer,&rect);
            }
            if(Pantalla_C[i][j] == 1){
                SDL_SetRenderDrawColor(text->renderer,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderFillRect(text->renderer,&rect);
                SDL_RenderFillRect(text->renderer,&rect);
                if(turno==1){
                    SDL_SetRenderDrawColor(text->renderer,73,221,238,0xFF);
                }else{
                    SDL_SetRenderDrawColor(text->renderer,12,100,100,0xFF);
                }
            }
            x_p = x_p + (Viewport.w/3);
        }
        x_p = 5;
        y_p = y_p +(Viewport.h/3);
    }
    SDL_SetRenderDrawColor(text->renderer,0,0,0,0xFF);
    SDL_RenderDrawLine(text->renderer,Viewport.w/3,0,Viewport.w/3,Viewport.h);
    SDL_RenderDrawLine(text->renderer,2*(Viewport.w/3),0,2*(Viewport.w/3),Viewport.h);
    SDL_RenderDrawLine(text->renderer,0,Viewport.h/3,Viewport.w,Viewport.h/3);
    SDL_RenderDrawLine(text->renderer,0,2*(Viewport.h/3),Viewport.w,2*(Viewport.h/3));
}

void Impresor_Consola(){
    system("cls");
    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%i", Pantalla_C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%i", Mark_Tags[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("%i %i\n", x_c, y_c);
}

int main( int argc, char* args[] ){
    int SCREEN_WIDTH  = 640;
    int SCREEN_HEIGHT = 480;
    int FONT_SIZE = 20;

    std::string PATH_FONT = "asset/font/LiberationMono-Regular.ttf";
    std::string PATH_ICON = "asset/icon.bmp";
    
    bool exit = false;
    int Turno = 1;
    int Puntaje[2]={0,0};

    Reset(&Turno);

    SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_RED   = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Color COLOR_BLUE  = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};

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
            SDL_Teclado(&Turno, action);


            Impresor_Pantalla(&text_white, &window, Turno, Puntaje);
            Impresor_Consola();
            Check_C(Puntaje,&Turno);


            window.update_screen();
        }
    }
    return 0;
}

















