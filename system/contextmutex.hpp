#ifndef CONTEXTMUTEX_HPP
#define CONTEXTMUTEX_HPP

#include <GLFW/glfw3.h>
#include <mutex>
#include <condition_variable>

class ContextMutex
{
public:
    ContextMutex();
    ContextMutex(bool, bool lockedin = 0);
    void init (bool,bool);
    void lock(GLFWwindow*);
    void unlock();
private:
    bool locked;
    bool main_lock;
    std::mutex lock_mutex;
    std::condition_variable wait_cond;
};

#endif // CONTEXTMUTEX_HPP
