#include <iostream>
#include <stdio.h>

#include "Window.hpp"
#include "ThreadManager.hpp"



void drawToWindow(workPackage wp){
    ThreadManager::mx.lock();
    
    std::cout << "Drawing In Thread: " << std::this_thread::get_id() << std::endl;

    wp.win->clear(0xFF);
    wp.win->blit(wp.surf, wp.ypos, wp.xpos);
    
    ThreadManager::mx.unlock();
}


void presentWindow(workPackage wp){
    ThreadManager::mx.lock();
    
    std::cout << "Presenting In Thread: " << std::this_thread::get_id() << std::endl;
    SDL_RenderPresent(wp.win->ren);
    
    ThreadManager::mx.unlock();
}

int main(){
    printf("Start of Main\n");

    bool singleThread = false;
    
    SDL_Surface* surf1 = SDL_LoadBMP("assets/tile1.bmp");
    SDL_Surface* surf2 = SDL_LoadBMP("assets/tile2.bmp");
    SDL_Surface* surf3 = SDL_LoadBMP("assets/tile3.bmp");
    SDL_Surface* surf4 = SDL_LoadBMP("assets/tile4.bmp");
    SDL_Surface* surf5 = SDL_LoadBMP("assets/tile5.bmp");
    SDL_Surface* surf6 = SDL_LoadBMP("assets/tile6.bmp");
    SDL_Surface* surf7 = SDL_LoadBMP("assets/tile7.bmp");
    SDL_Surface* surf8 = SDL_LoadBMP("assets/tile8.bmp");
    SDL_Surface* surf9 = SDL_LoadBMP("assets/mine.bmp");
    SDL_Surface* surf10 = SDL_LoadBMP("assets/tileFlag.bmp");
    
    Window win1(10,10);
    Window win2(10,150);
    Window win3(10,300);
    Window win4(10,450);
    Window win5(10,600);
    Window win6(200,10);
    Window win7(200,150);
    Window win8(200,300);
    Window win9(200,450);
    Window win10(200,600);
    
    workPackage wp;

    wp.ypos = 0;
    wp.xpos = 0;

    
    auto start = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < 30; i ++){
        wp.xpos+=2;
        wp.ypos+=2;
        for(int j = 0; j < 2; j++){
            wp.func = (j==0)?drawToWindow:presentWindow;
            
            wp.win  = &win1;
            wp.surf = surf1;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);

            wp.win  = &win2;
            wp.surf = surf2;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);

            wp.win  = &win3;
            wp.surf = surf3;

            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);

            wp.win  = &win4;
            wp.surf = surf4;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);

            wp.win  = &win5;
            wp.surf = surf5;

            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);

            wp.win  = &win6;
            wp.surf = surf6;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);
            
            wp.win  = &win7;
            wp.surf = surf7;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);
            
            wp.win  = &win8;
            wp.surf = surf8;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);
            
            wp.win  = &win9;
            wp.surf = surf9;
            
            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);
            
            wp.win  = &win10;
            wp.surf = surf10;

            if(singleThread)
                wp.func(wp);
            else
                ThreadManager::addJob(wp);
        }
    }
    
    ThreadManager::join(1);

    auto finish = std::chrono::high_resolution_clock::now();
    
    
    std::chrono::duration<double> diff = finish - start;
    
    std::cout << "Duration of Code: " << diff.count() << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    printf("End of Main\n");
    
}
