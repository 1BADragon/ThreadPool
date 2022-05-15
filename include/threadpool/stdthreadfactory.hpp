#pragma once

#include <memory>
#include <threadpool/entrypoint.hpp>
#include <threadpool/abstractthread.hpp>
#include <threadpool/threadfactory.hpp>

namespace tp {

class StdThreadFactory : public ThreadFactory
{
public:
    virtual std::unique_ptr<AbstractThread> build_thread(std::shared_ptr<EntryPoint> ep) override;
};

}
