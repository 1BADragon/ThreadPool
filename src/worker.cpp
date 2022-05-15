#include <threadpool/worker.hpp>

namespace tp {

WorkerOpts::WorkerOpts()
    : jobs(), job_mut(), job_ready(), should_run(true)
{

}

Worker::Worker(std::shared_ptr<WorkerOpts> opts)
    : _opts(opts)
{

}

void Worker::operator()()
{
    std::shared_ptr<JobPool> current_pool;
    while (_opts->should_run) {
        if (!current_pool) {
            std::unique_lock lock(_opts->job_mut);

            if (_opts->jobs.empty()) {
                _opts->job_ready.wait(lock, [this]{
                    return !_opts->should_run ||
                           !_opts->jobs.empty();
                });
            }

            current_pool = _opts->jobs.front().lock();

            if (!current_pool) {
                // The ref count on the jobpool hit 0 pop it and continue
                // the loop
                _opts->jobs.pop();
                continue;
            }

            if (current_pool->is_finished()) {
                // The current jobpool is finished, pop it and continue
                // the loop
                _opts->jobs.pop();
                current_pool.reset();
                continue;
            }
        }

        auto next_job = current_pool->next();

        if (!next_job) {
            current_pool.reset();
            continue;
        }

        next_job->ep()();
    }
}

}
