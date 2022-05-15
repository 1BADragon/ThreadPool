#pragma once

#include <memory>
#include <functional>
#include <threadpool/abstractthread.hpp>
#include <threadpool/entrypoint.hpp>

namespace tp {

class Thread : public AbstractThread{
public:
    Thread(std::shared_ptr<EntryPoint> ep);

protected:
    std::function<void()> entry_point();

private:
    std::shared_ptr<EntryPoint> _ep;

    void entry();
};

}
