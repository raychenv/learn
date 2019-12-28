// https://www.codeproject.com/Articles/1278737/Programming-Concurrency-in-Cplusplus-Part-2
// Task-based parallelism

#include <thread>
#include <iostream>
#include <future>

void  func(std::promise<int> *p)
{
    int a=10, b=5;
    int result = a+b;
    std::cout << "From inside the Thread..." << std::endl;
    p->set_value(result);
}


int main()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread th(func, &p);
    std::cout << f.get() << std::endl;
    th.join();
    return 0;
}