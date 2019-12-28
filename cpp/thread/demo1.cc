// Reference: https://en.cppreference.com/w/cpp/thread/thread/thread
// Thread object creation

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

void f2(int& n)
{
    for (int i=0; i<5; ++i) {
        std::cout << "Thread: " << std::this_thread::get_id()  // get thread id of current thread
                  << " executing" << " with n: " << n << "\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

class foo
{
    public:
        void bar()
        {
            for (int i=0; i<5; ++i) {
                std::cout << "Thread: " << std::this_thread::get_id()  // get thread id of current thread
                          << " executing" << " with n: " << n << "\n";
                ++n;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    int n{0};
};

class baz
{
    public:
        void operator()()
        {
            for (int i=0; i<5; ++i) {
                std::cout << "Thread: " << std::this_thread::get_id()  // get thread id of current thread
                          << " executing" << " with n: " << n << "\n";
                ++n;

                using namespace std::chrono_literals; // from C++14
                std::this_thread::sleep_for(1s);
            }
        }
    int n{0};
};

int main()
{
    int n = 0;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n+1); //pass by value
    std::thread t3(f2, std::ref(n));  // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(), t3 is no longer a thread

    foo f;
    std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f

    baz b;
    std::thread t6(b); // t6 runs baz::operator() on object b

    t2.join();   // Blocks current thread untill thread identified by t2 finishes its execution
    //t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of foo::n is " << f.n << '\n';
}
