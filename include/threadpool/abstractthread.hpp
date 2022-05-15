#pragma once

#include <thread>

namespace tp {

class AbstractThread {
public:
    virtual std::thread::id get_id() const noexcept = 0;
    virtual void join() = 0;
    virtual void detach() = 0;
};

}
