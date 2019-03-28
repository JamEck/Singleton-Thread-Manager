#include <iostream>
#include <stdio.h>

#include "ThreadManager.hpp"

void otherFunc(){
    printf("Doing Other func!\n");
}

void threadFunc1(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "threadFunc1 finished: " << std::this_thread::get_id() << std::endl;
}

void threadFunc2(){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "threadFunc2 finished: " << std::this_thread::get_id() << std::endl;
}

void threadFunc3(){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "threadFunc3 finished: " << std::this_thread::get_id() << std::endl;
}

void threadFunc4(){
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "threadFunc4 finished: " << std::this_thread::get_id() << std::endl;
}

void quickFunc(){
    printf("Lightning Fast!\n");
}

int main(){
    printf("Start of Main\n");

    for(int i = 0; i < 4; i++){
        ThreadManager::addJob(threadFunc1);
        ThreadManager::addJob(threadFunc2);
        ThreadManager::addJob(quickFunc);
        ThreadManager::addJob(threadFunc3);
        ThreadManager::addJob(threadFunc4);
    }


    ThreadManager::join(1);
    printf("End of Main\n");
    
}
