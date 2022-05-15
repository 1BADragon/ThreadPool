#include <threadpool/stdthreadfactory.hpp>
#include <threadpool/stdthread.hpp>

namespace tp {

std::unique_ptr<AbstractThread>
StdThreadFactory::build_thread(std::shared_ptr<EntryPoint> ep)
{
    return std::make_unique<StdThread>(ep);
}

}
