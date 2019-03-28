#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <vector>
#include <queue>
#include <chrono>
#include <future>

class ThreadManager{
private:
    static ThreadManager* tm;
    std::vector<std::future<void>*> threads;
    static std::queue<void(*)()> jobs;
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
    
    
    // returns false if job gets queued
    static bool addJob(void(*)());
    
    // gets Singleton tm
    static ThreadManager& get();
    
    // calls destroy on Singleton tm
    static void join(bool finish = false);
};


#endif /* ThreadManager_hpp */
