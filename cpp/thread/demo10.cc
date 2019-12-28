// https://www.codeproject.com/Articles/1278737/Programming-Concurrency-in-Cplusplus-Part-2
// Use atomic to avoid race condition

#include <thread>
#include <iostream>

class RaceCondition
{
public:
    std::atomic<int> n;
    RaceCondition() : n{0} {}

    void increment() {
        ++n;
    }
};


int main()
{
    RaceCondition racer;

    std::thread t1([&racer] {
        for (int i=0; i<10000; ++i) {
            racer.increment();
        }
    });

    std::thread t2([&racer] {
        for (int i=0; i<10000; ++i) {
            racer.increment();
        }
    });

    t1.join();
    t2.join();

    std::cout << racer.n << std::endl;
}