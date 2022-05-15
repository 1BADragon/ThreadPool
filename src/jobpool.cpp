#include <sstream>
#include <threadpool/jobpool.hpp>

namespace tp {

JobPool::JobPool()
    : _state_mut(), _state(State::INIT), _seen_final(false)
{
    std::stringstream ss;

    ss << "<JobPool at " << this << ">";
    _name = ss.str();
}

JobPool::JobPool(const std::string_view &name)
    : _state_mut(), _state(State::INIT), _seen_final(false), _name(name)
{

}

std::string JobPool::name() const noexcept
{
    return _name;
}

bool JobPool::is_running() const noexcept
{
    return _state == State::RUNNING;
}

bool JobPool::is_finished() const noexcept
{
    return _state == State::FINISHED &&
            _in_progress == 0;
}

bool JobPool::is_queued() const noexcept
{
    return _state == State::QUEUED;
}

void JobPool::wait_for_finished()
{
    if (is_finished()) {
        return;
    }

    std::unique_lock lock(_state_mut);
    _state_change.wait(lock, [this]{
        return this->is_finished();
    });
}

void JobPool::cancel() noexcept
{
    _state = State::FINISHED;
}

std::optional<Job> JobPool::next()
{
    if (_state == State::FINISHED) {
        return std::nullopt;
    }

    std::unique_lock lock(_state_mut);

    auto next_ep = this->next_ep();

    if (!next_ep) {
        return std::nullopt;
    }

    _state = State::RUNNING;
    _in_progress++;
    return std::optional<Job>(std::in_place, std::move(next_ep), this);
}

void JobPool::release()
{
    _in_progress--;
    _state_change.notify_all();
}

void JobPool::queued()
{
    if (_state == State::INIT) {
        _state = State::QUEUED;
    }
}

}
