#pragma once

#include <string_view>
#include <string>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <optional>

#include <threadpool/entrypoint.hpp>
#include <threadpool/job.hpp>

namespace tp {

class JobPool {
public:
    JobPool();
    JobPool(const std::string_view &name);
    ~JobPool();

    std::string name() const noexcept;

    bool is_running() const noexcept;
    bool is_finished() const noexcept;
    bool is_queued() const noexcept;

    void wait_for_finished();

    void cancel() noexcept;

    std::optional<Job> next();

protected:
    virtual std::unique_ptr<EntryPoint> next_ep() = 0;

private:
    friend class Job;
    friend class ThreadPool;

    enum class State {
        INIT,
        QUEUED,
        RUNNING,
        FINISHED
    };

    std::mutex _state_mut;
    std::atomic<State> _state;
    std::condition_variable _state_change;
    bool _seen_final;
    std::string _name;
    std::atomic<uint32_t> _in_progress;

    void release();
    void queued();
};

}
