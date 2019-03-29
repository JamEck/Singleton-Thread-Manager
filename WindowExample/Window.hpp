#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>

class Pixel{
public:
    Uint8 r = 0x00;
    Uint8 g = 0x00;
    Uint8 b = 0x00;
    Uint8 a = 0xFF;
    
    Pixel(){}
    Pixel(Uint32);
    
    
    void breakInt(Uint32);
};


class Window{
public:
    SDL_Window* win = nullptr;
    SDL_Renderer *ren = nullptr;
    SDL_Surface *surf = nullptr;
    
    int x = 10, y = 10;
    int w = 100, h = 100;
    unsigned int length = w*h;
    
    
    Window(int = 10, int = 10);
    ~Window();
    
    void clear(Uint32);
    void blit(SDL_Surface* surf, int y, int x, float = 1.0, Uint32 = 0xFFFFFFFF);
};

#endif /* Window_hpp */