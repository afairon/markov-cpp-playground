#ifndef INTERUPT_HANDLER_HPP_
#define INTERUPT_HANDLER_HPP_

#include <condition_variable>
#include <mutex>
#include <signal.h>

static std::condition_variable _condition;
static std::mutex _mutex;

class InteruptHandler {
    public:
        static void hookSIGINT() {
            signal(SIGINT, HandleInterupt);
        }

        static void HandleInterupt(int signal) {
            if (signal == SIGINT) {
                _condition.notify_one();
            }
        }

        static void waitInterupt() {
            std::unique_lock<std::mutex> lock { _mutex };
            _condition.wait(lock);
            lock.unlock();
        }
};

#endif