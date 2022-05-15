#pragma once

#include <memory>
#include <threadpool/entrypoint.hpp>

namespace tp {

class JobPool;

class Job {
public:
    Job(std::unique_ptr<EntryPoint> &&ep, JobPool *parent);
    ~Job();

    EntryPoint& ep();

private:
    std::unique_ptr<EntryPoint> _ep;
    JobPool *_parent;
};

}
