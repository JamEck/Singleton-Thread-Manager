#include "Window.hpp"

Pixel::Pixel(Uint32 color){
    breakInt(color);
}

void Pixel::breakInt(Uint32 color){
    a = color & 0xFF; color >>= 8;
    b = color & 0xFF; color >>= 8;
    g = color & 0xFF; color >>= 8;
    r = color & 0xFF;
}


Window::Window(int posy, int posx){
    
    bool success = true;
    
    x = posx;
    y = posy;
    
    win  = SDL_CreateWindow("Test",x,y,w,h,SDL_WINDOW_SHOWN);
    ren  = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(ren);

    surf = SDL_CreateRGBSurface(
        0, w, h, 32,
        0xFF000000,
        0x00FF0000,
        0x0000FF00,
        0x000000FF
     ); // in case you want a surface to manip.
    
    if(win == nullptr){
        printf("Problem Creating Window.\n");
        success = false;
    }
    
    if (ren == nullptr){
        printf("Problem Creating Renderer.\n");
        printf("%s\n", SDL_GetError());
    }
    
    if(surf == nullptr){
        printf("Problem Getting Window Surface.\n");
        printf("%s", SDL_GetError());
    }
    
    if(!ren & !surf) success = false;
    
    if(!success){
        win  = nullptr;
        ren  = nullptr;
        surf = nullptr;
    }
}

Window::~Window(){
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
}

void Window::clear(Uint32 color = 0xFF0000FF){
    
    Pixel p(color);
    
    SDL_SetRenderDrawColor(ren, p.r, p.g, p.b, p.a);
    
    SDL_RenderClear(ren);
}

void Window::blit(SDL_Surface* surf, int y, int x, float scale, Uint32 colorMod){
    

    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,surf);
    
    {
        colorMod |= 0xFF;
        Uint8* c = (Uint8*)&colorMod;
        SDL_SetTextureColorMod(tex, c[3], c[2], c[1]);
    }
    
    if(tex == nullptr){
        printf("Could Not Generate Texture.\n");
        return;
    }
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w*scale;
    rect.h = surf->h*scale;
    
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}
