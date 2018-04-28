#include <condition_variable>
#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

std::mutex m;
std::condition_variable cv;

constexpr int MAX_ITER = 500000;
std::atomic<bool> is_pong_time(false);

void printer(bool value);

int main()
{
    try {
        std::thread t1(printer, false);
        std::thread t2(printer, true);
        t1.join();
        t2.join();
    } catch(...) {
        printf("error\n");
        return 1;
    }
    return 0;
}

void printer(bool value)
{
    const char* str = value ? "pong\n" : "ping\n";
    for(int i = 0; i < MAX_ITER; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [value]{return is_pong_time == value;});
        std::cout << str << "\n";
        is_pong_time = !value;
        cv.notify_one();
    }
}
