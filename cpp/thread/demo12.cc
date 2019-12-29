// std::packaged_task is a class template wrapper that imples a normal function to run as asynchronous
// std::promise 

#include <iostream>
#include <future>
#include <thread>

int func()
{
    int a=10, b=5;

    std::cout << std::this_thread::get_id() << ": " 
              << "From inside the Thread...."
              << std::endl;
    return a+b;
}

int main()
{
    std::packaged_task<int()> p(func);
    std::future<int> f = p.get_future();
    std::thread th(std::move(p));
    std::cout << std::this_thread::get_id() << ": " << f.get() << std::endl;
    th.join();
    return 0;
}
