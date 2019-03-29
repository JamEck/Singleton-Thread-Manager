#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <vector>
#include <queue>
#include <chrono>
#include <future>
#include "Window.hpp"


struct workPackage{
    void(*func)(workPackage) = 0;
    Window* win = 0;
    SDL_Surface* surf = 0;
    int xpos = 0;
    int ypos = 0;
};

class ThreadManager{
private:
    static ThreadManager* tm;
    std::vector<std::future<void>*> threads;
    static std::queue<workPackage> jobs;

    static bool alive;
    std::thread jobThread;
    
    // constructor. assign number of threads active at once.
    // start jobThread
    ThreadManager(int numOfThreads);
    
    
    // function for jobThread
    // waits for available thread slots and assigns next job.
    static void manageJobs();
    
    
    // destroys and cleans up after singleton
    void destroy(bool finish);
    
    // gets pointer to element of 'threads' vector
    // if its thread is finished or nonexistent
    std::future<void>** getAvailable();
    
    // returns true if valid thread is finished
    bool checkFinished(std::future<void>* thread);
    
    ~ThreadManager(){}
    
public:
    
    static std::mutex mx;

    // returns false if job gets queued
    static bool addJob(workPackage);
    
    // gets Singleton tm
    static ThreadManager& get();
    
    // calls destroy on Singleton tm
    static void join(bool finish = false);
};


#endif /* ThreadManager_hpp */
