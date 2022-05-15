#include <threadpool/job.hpp>
#include <threadpool/jobpool.hpp>

namespace tp {

Job::Job(std::unique_ptr<EntryPoint> &&ep, JobPool *parent)
    : _ep(std::move(ep)), _parent(parent)
{

}

Job::~Job()
{
    _parent->release();
}

EntryPoint &Job::ep()
{
    return *_ep;
}


}
