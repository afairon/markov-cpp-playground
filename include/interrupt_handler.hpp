#ifndef INTERRUPT_HANDLER_HPP_
#define INTERRUPT_HANDLER_HPP_

#include <condition_variable>
#include <mutex>
#include <signal.h>

static std::condition_variable _condition;
static std::mutex _mutex;

class InterruptHandler {
    public:
        static void hookSIGINT() {
            signal(SIGINT, HandleInterrupt);
        }

        static void HandleInterrupt(int signal) {
            if (signal == SIGINT) {
                _condition.notify_one();
            }
        }

        static void waitInterrupt() {
            std::unique_lock<std::mutex> lock { _mutex };
            _condition.wait(lock);
            lock.unlock();
        }
};

#endif