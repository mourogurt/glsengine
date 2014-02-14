#include "contextmutex.hpp"

ContextMutex::ContextMutex()
{
    main_lock = 0;
}

ContextMutex::ContextMutex(bool crit, bool lockedin)
{
    main_lock = crit;
    locked = lockedin;
}

void ContextMutex::init(bool crit, bool lockedin)
{
    main_lock = crit;
    locked = lockedin;
}

void ContextMutex::lock(GLFWwindow* window)
{
    std::unique_lock<std::mutex> mlock(lock_mutex);
    if (locked) { if (main_lock) return; else wait_cond.wait(mlock,[&](){return !locked;}); }
    glfwMakeContextCurrent(window);
    locked = 1;
    mlock.unlock();
    wait_cond.notify_one();
}

void ContextMutex::unlock()
{
    std::unique_lock<std::mutex> mlock(lock_mutex);
    if (!locked) { if (main_lock) return; else wait_cond.wait(mlock,[&](){return locked;}); }
    glfwMakeContextCurrent(NULL);
    locked = 0;
    mlock.unlock();
    wait_cond.notify_one();
}
