#pragma once

#include <memory>
#include <queue>
#include <threadpool/entrypoint.hpp>
#include <threadpool/jobpool.hpp>

namespace tp {

struct WorkerOpts {
    WorkerOpts();

    std::queue<std::weak_ptr<JobPool>> jobs;
    std::mutex job_mut;
    std::condition_variable job_ready;
    std::atomic<bool> should_run;
};

class Worker : public EntryPoint {
public:
    Worker(std::shared_ptr<WorkerOpts> opts);

    void operator()();

private:
    std::shared_ptr<WorkerOpts> _opts;
};

}
