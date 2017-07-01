/*
 *  编译环境：Ubuntu gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3)
 *  编译指令：g++  AsyncTest.cpp -o asyncDownload.out -std=c++11 -pthread
 *  作者：returnzer0
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <future>
#include <vector>
#include <chrono>
#include <thread>

int Fun(){
    for(int i = 0 ;i < 20;i++){
        std::cout<<"this thread ="<<std::this_thread::get_id()<<" num = "<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<int>> threadpools;
    for(int i = 0 ; i < 3 ; i++){
        threadpools.push_back(std::async(std::launch::async,Fun));//在独立的线程中异步执行
        //threadpools.push_back(std::async(std::launch::deferred,Fun));//在主线程中懒加载执行，在第一次请求时执行，始终只有一个线程
        std::cout<<"async task"<<i<<" created"<<std::endl;
    }
    std::cout<<"main thread ="<<std::this_thread::get_id()<<" "<<std::endl;
    threadpools[0].wait();
    threadpools[1].wait();
    threadpools[2].wait();

    std::cout << "end" << " time = " << (std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    return 0;
}