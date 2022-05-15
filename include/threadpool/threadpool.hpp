#pragma once

#include <cstddef>
#include <vector>
#include <memory>
#include <threadpool/abstractthread.hpp>
#include <threadpool/abstractthreadfactory.hpp>
#include <threadpool/jobpool.hpp>
#include <threadpool/worker.hpp>

namespace tp {

class ThreadPool {
public:
    ThreadPool();
    ThreadPool(std::size_t n_workers);
    ThreadPool(AbstractThreadFactory &factory);
    ThreadPool(std::size_t n_workers, AbstractThreadFactory &factory);
    ~ThreadPool();

    void push(std::shared_ptr<JobPool> &pool);

private:
    std::shared_ptr<WorkerOpts> _opts;
    std::vector<std::unique_ptr<AbstractThread>> _threads;

    void spawn_threads(std::size_t n_workers, AbstractThreadFactory &factory);

};

}
