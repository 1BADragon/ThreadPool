#pragma once

#include <memory>
#include <threadpool/abstractthread.hpp>
#include <threadpool/entrypoint.hpp>

namespace tp {

class AbstractThreadFactory {
public:
    virtual std::unique_ptr<AbstractThread> build_thread(std::shared_ptr<EntryPoint> ep) = 0;
};

}
