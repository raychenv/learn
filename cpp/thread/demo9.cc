// https://www.codeproject.com/Articles/1278737/Programming-Concurrency-in-Cplusplus-Part-2
// use condition variable to sync tasks/actions

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>


std::mutex mutex;
std::condition_variable cv;
bool ready = false;

void print() {
    std::cout << std::this_thread::get_id()
              << "Waiting for other thread to signal ready!" << std::endl;
    std::unique_lock<std::mutex> lock(mutex);

    while(!ready) {
        cv.wait(lock);
    }

    std::cout << "thread is executing now..." << std::endl;
}

void execute()
{
    std::cout << "Thread is ready!!!" << std::endl;
    ready = true;
    cv.notify_all();
}

int main()
{
    std::thread t1(print);
    std::thread t2(print);
    std::thread t3(execute);

    t1.join();
    t2.join();
    t3.join();
}