// https://www.codeproject.com/Articles/1278737/Programming-Concurrency-in-Cplusplus-Part-2
// Deadlocks
// To avoid deadlocks, always lock away the mutexes in the same order

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
        std::cout << "Acquiring first mutex... " << std::endl;

        mutex1.lock();
        print();

        std::cout << "Acquiring second mutex..." << std::endl;
        mutex2.lock();
        print();

        mutex1.unlock();
        mutex2.unlock();
    });

    std::thread t2([&] {
        std::cout << "Acquiring second mutex... " << std::endl;

        mutex2.lock();
        print();

        std::cout << "Acquiring first mutex..." << std::endl;
        mutex1.lock();
        print();

        mutex2.unlock();
        mutex1.unlock();
    });

    t1.join();
    t2.join();
}