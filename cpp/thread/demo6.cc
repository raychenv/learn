// https://www.codeproject.com/Articles/1278737/Programming-Concurrency-in-Cplusplus-Part-2
// Race condition
// use mutex with lock to avoid race condition

#include <thread>
#include <iostream>
#include <mutex>

class RaceCondition
{
public:
    int n;
    std::mutex m_mutex;
    RaceCondition() : n{0} {}

    void increment() {
        // RAII used for lock_guard
        std::lock_guard<std::mutex> lock(m_mutex);
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