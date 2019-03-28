#include "ThreadManager.hpp"

ThreadManager* ThreadManager::tm = new ThreadManager(4);
std::queue<void(*)()> ThreadManager::jobs = std::queue<void(*)()>();
bool ThreadManager::alive = true;


// constructor. assign number of threads active at once.
// start jobThread
ThreadManager::ThreadManager(int numOfThreads){
    threads.assign(numOfThreads, 0); // fill with nullptrs
    
    jobThread = std::thread(manageJobs); // launch jobThread
}


// function for jobThread/
// waits for available thread slots and assigns next job.
void ThreadManager::manageJobs(){
    while(ThreadManager::alive){ // if Singleton is still alive
        if(!ThreadManager::jobs.empty()){ // if there are jobs to be done
            auto f = tm->getAvailable(); // check for available thread slots
            if(f){ // if found
                
                // create new thread
                *f = new std::future<void>;
                
                // launch async thread with next job on queue
                **f = std::async(std::launch::async, ThreadManager::jobs.front());
                ThreadManager::jobs.pop(); // remove job from queue
            }
        }
    }
}


// destroys and cleans up after singleton
void ThreadManager::destroy(bool finish){
    // continues unloading jobs until queue is empty
    if(finish) while(!jobs.empty());
    
    // set alive to false so jobThread while loop terminates
    ThreadManager::alive = false;
    jobThread.join();
    
    // wait for threads to finish and delete them
    for (int i = 0; i < threads.size(); i++){
        if(threads[i]){
            threads[i]->wait();
            delete threads[i];
            threads[i] = nullptr;
        }
    }
    
        delete tm; // delete Singleton
        tm = nullptr;
}

// gets pointer to element of 'threads' vector
// if its thread is finished or nonexistent
std::future<void>** ThreadManager::getAvailable(){
    // check each element in 'threads' vector
    for (int i = 0; i < threads.size(); i++){
        if(threads[i] == nullptr){ // if nothings there
            return &threads[i]; // return address of that element
        }
        else if(checkFinished(threads[i])){
            threads[i]->get(); // return void: not necessary
            delete threads[i]; // delete thread
            threads[i] = nullptr; // reset it
            return &threads[i]; // return address of that element
        }
    }
    return 0;
}

// returns true if valid thread is finished
bool ThreadManager::checkFinished(std::future<void>* thread){
    
    if(thread){ // if NOT a nullptr
        
        // check future status by waiting for 0 seconds
        return thread->wait_for(std::chrono::seconds(0)) ==
        std::future_status::ready;
    }
    
    // if there's no thread, there's no finished thread
    return false;
}

// returns false if job gets queued
bool ThreadManager::addJob(void(*func)()){
    // if theres jobs on the queue
    // dont bother checking for free threads
    if(!tm->jobs.empty()){
        tm->jobs.push(func); // push new job on queue
        return false;
    }
    
    // check for free thread
    auto f = tm->getAvailable();
    if(f == 0){ // if there's no free thread
        tm->jobs.push(func); // push new job on queue
        return false;
    }else{
        
        // create new thread
        *f = new std::future<void>;
        
        // launch async thread with next job on queue
        **f = std::async(std::launch::async, func);
        return true;
    }
}

// gets Singleton tm
ThreadManager& ThreadManager::get(){
    return *tm;
}

// calls destroy on Singleton tm
void ThreadManager::join(bool finish){
    tm->destroy(finish);
}


