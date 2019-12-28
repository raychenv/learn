// Reference: https://en.cppreference.com/w/cpp/thread/thread/thread
// Get thread id
// Get current thread id: std::this_thread::get_id()
// Get thread id in main thread: thread.get_id()

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

void f1(int n)
{
    for (int i=0; i<5; ++i) {
        std::cout << "Thread: " << std::this_thread::get_id()  // get thread id of current thread
                  << " executing" << " with n: " << n << "\n";
        ++n;
        
        // Blocks the execution of the current thread for at least the specified sleep_duration.
        // This function may block for longer than sleep_duration due to scheduling or resource contention delays.
        // The standard recommends that a steady clock is used to measure the duration. If an implementation uses a system clock instead, the wait time may also be sensitive to clock adjustments.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    int n = 0;
    std::thread t1(f1, n); //pass by value

    std::thread::id t1_id = t1.get_id();
    std::cout << "Thread id of t1: " << t1_id << "\n";     
    t1.join();
    std::cout << "Thread id of t1: " << t1.get_id() << "\n";

    std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency();
}
