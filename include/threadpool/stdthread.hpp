#pragma once

#include <thread>
#include <threadpool/thread.hpp>

namespace tp {

class StdThread : public Thread
{
public:
    StdThread(std::shared_ptr<EntryPoint> ep);

    virtual std::thread::id get_id() const noexcept override;
    virtual void join() override;
    virtual void detach() override;

private:
    std::thread _thread;
};

} // namespace tp

