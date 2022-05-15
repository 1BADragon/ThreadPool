#include <threadpool/stdthread.hpp>

namespace tp {

StdThread::StdThread(std::shared_ptr<EntryPoint> ep)
    : Thread(ep), _thread(Thread::entry_point())
{

}

std::thread::id StdThread::get_id() const noexcept
{
    return _thread.get_id();
}

void StdThread::join()
{
    _thread.join();
}

void StdThread::detach()
{
    _thread.detach();
}

} // namespace tp
