#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#define scr_height 600
#define scr_width 400
#define fps 15
#define framedelay (1000/fps)

#define cell_width (scr_height/cell_size)
#define cell_size 10
#define cell_height (scr_width/cell_size)

#define start_cell_x 0
#define start_cell_y 0
#define speed 20
#define max 60

int dir = 6;
int snake_l = 3;
int posx[max] = {20,20,20};
int posy[max] = {20,19,18};
int foodx, foody;
int score;

int eventcontrol(SDL_Window *window){
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
        {   
            dir = 1;
        }
        else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP && dir!=2){
            dir = 8;
        }
        else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN && dir!=8){
            dir = 2;
        }
        else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT && dir!=6){
            dir = 4;
        }
        else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT && dir!=4){
            dir = 6;
        }
        else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
            dir = 5;
        }
    }
    return dir;
}

void generategrid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect field = {
        start_cell_x * cell_size,
        start_cell_y * cell_size,
        cell_width * cell_size,
        cell_height * cell_size
    };

    SDL_RenderFillRect(renderer, &field);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= cell_width; i++) {
        if(i==0 || i==cell_width ){
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
            SDL_RenderDrawLine(renderer, i * cell_size, 0, i * cell_size, cell_height * cell_size);
        }
    }
    for (int i = 0; i <= cell_height; i++) {
        if(i==0 || i==cell_height ){
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
            SDL_RenderDrawLine(renderer, 0, i * cell_size, cell_width * cell_size, i * cell_size);
        }
    }
}

int placefood(SDL_Renderer *renderer) {
    srand(time(NULL));
    foodx = rand() % cell_width;
    foody = rand() % cell_height;
}

void generatefood(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect rect = { foodx*cell_size, foody*cell_size, cell_size, cell_size };
    SDL_RenderFillRect(renderer, &rect);
}

void generatesnake(SDL_Renderer *renderer) {
    for(int i = snake_l-1; i>0; i--){
        posx[i] = posx[i-1];
        posy[i] = posy[i-1];
    }
    for(int i = 0; i<snake_l; i++){
        if(i==0 || i==1){
            SDL_SetRenderDrawColor(renderer, 148, 0, 211, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        SDL_Rect sn = { posx[i], posy[i], cell_size, cell_size };
        SDL_RenderFillRect(renderer, &sn);
    }
}

void gamestatus(SDL_Renderer *renderer){
    if(posy[0]==0-cell_size || posy[0]==(scr_width) || posx[0]==0-cell_size || posx[0]==(scr_height)){
    printf("\nGame over \n\nyour score: %d\n\n", score);
    exit(0);
    }
    int fx = foodx*cell_size;
    int fy = foody*cell_size;
    if(posx[0]==fx && posy[0]==fy){
        placefood(renderer);
        generatefood(renderer);
        score++;
        snake_l++;
    }
    for(int i=2; i<snake_l; i++){
        if(posx[0]==posx[i] && posy[0]==posy[i]){
            printf("\nGame over \n\nyour score: %d\n\n", score);
            exit(0);
        }
    }
}

void gamewindow(SDL_Renderer *renderer) {
    generategrid(renderer);
    generatefood(renderer);
    generatesnake(renderer);
    gamestatus(renderer);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("snake game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scr_height+1, scr_width+1, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int framestart;
    int frametime;
    generatefood(renderer);
    placefood(renderer);
    int quit = 0;
    while(!quit)
    {   
        framestart = SDL_GetTicks();
        frametime = SDL_GetTicks() - framestart;
        if(framedelay > frametime){
            SDL_Delay(framedelay - frametime);
        }
        int keypress = eventcontrol(window);
        if(keypress==1){ quit=1; }
        if(keypress==6){posx[0]+=cell_size;}
        if(keypress==8){posy[0]-=cell_size;}
        if(keypress==4){posx[0]-=cell_size;}
        if(keypress==2){posy[0]+=cell_size;}
        if(keypress==5){posy[0];posx[0];}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        gamewindow(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
