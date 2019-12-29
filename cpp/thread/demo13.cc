// std::async is a high-level abstracting over promises to accomplish asynchronous excution of tasks

#include <iostream>
#include <future>
#include <thread>
#include <vector>

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
    // simple usage with function
    std::future<int> f = std::async(func);
    std::cout << f.get() << " from thread:" << std::this_thread::get_id() << std::endl;

    // working with lambda function
    std::vector<std::future<int>> fv;
    for (int i=0; i<5; ++i) {
        fv.push_back (std::async([] (int x) {return x*x;}, i));
    }

    for (auto &result: fv) {
        std::cout << result.get() << std::endl;
    }
}
