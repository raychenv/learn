// https://www.codeproject.com/Articles/1278737/Programming-Concurrency-in-Cplusplus-Part-2
// Deadlocks
// To avoid deadlocks, 
// 1. lock mutexes at the same time and then create the guard afterwards
// 2. create the guards and then lock mutexes at the same time

#include <thread>
#include <iostream>
#include <mutex>

void print() {
    std::cout << std::this_thread::get_id() << ": Critical Data!!" << std::endl;
}

int main()
{
    std::mutex mutex1, mutex2;

    std::thread t1([&] {
        std::cout << std::this_thread::get_id() << "Acquiring first mutex... " << std::endl;

        std::lock(mutex1, mutex2);

        std::lock_guard<std::mutex>  lock1(mutex1, std::adopt_lock);
        print();

        std::cout << std::this_thread::get_id() << "Acquiring second mutex..." << std::endl;
        std::lock_guard<std::mutex>  lock2(mutex2, std::adopt_lock);
        print();
    });

    std::thread t2([&] {
        std::cout << std::this_thread::get_id() << "Acquiring second mutex... " << std::endl;

        std::lock(mutex1, mutex2);
        std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
        print();

        std::cout << std::this_thread::get_id() << "Acquiring first mutex..." << std::endl;
        std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
        print();

    });

    t1.join();
    t2.join();
}