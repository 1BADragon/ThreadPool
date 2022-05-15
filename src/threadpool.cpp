#include <thread>

#include <threadpool/threadpool.hpp>
#include <threadpool/stdthreadfactory.hpp>

namespace tp {

ThreadPool::ThreadPool()
{
    StdThreadFactory factory;

    spawn_threads(std::thread::hardware_concurrency(), factory);
}

ThreadPool::ThreadPool(std::size_t n_workers)
{
    StdThreadFactory factory;

    spawn_threads(n_workers, factory);
}

ThreadPool::ThreadPool(AbstractThreadFactory &factory)
{
    spawn_threads(std::thread::hardware_concurrency(), factory);
}

ThreadPool::ThreadPool(std::size_t n_workers, AbstractThreadFactory &factory)
{
    spawn_threads(n_workers, factory);
}

ThreadPool::~ThreadPool()
{
    _opts->should_run = false;
    _opts->job_ready.notify_all();

    for (auto &thread : _threads) {
        thread->join();
    }
}

void ThreadPool::push(std::shared_ptr<JobPool> &pool)
{
    std::unique_lock lock(_opts->job_mut);

    _opts->jobs.push(pool);
    _opts->job_ready.notify_all();
}

void ThreadPool::spawn_threads(std::size_t n_workers, AbstractThreadFactory &factory)
{
    _opts = std::make_shared<WorkerOpts>();
    auto worker = std::make_shared<Worker>(_opts);

    for (std::size_t i = 0; i < n_workers; ++i) {
        _threads.push_back(factory.build_thread(worker));
    }
}

}
