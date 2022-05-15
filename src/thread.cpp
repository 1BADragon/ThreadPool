
#include <threadpool/thread.hpp>


namespace tp {

Thread::Thread(std::shared_ptr<EntryPoint> ep)
    : _ep(ep)
{

}

std::function<void ()> Thread::entry_point()
{
    return std::bind(&Thread::entry, this);
}

void Thread::entry()
{
    (*_ep)();
}

}
