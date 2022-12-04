#include <cassert>

#include "UpdateQueue.h"

namespace chcEarth {

UpdateQueue::UpdateQueue()
{
    _count.store(0);
}

UpdateQueue::~UpdateQueue()
{

}

void UpdateQueue::push(const Update& update)
{
    std::unique_lock<std::mutex> lck(_pendingUpdateMutex);

    if (update.merge && _pendingUpdate.size() > 0)
    {
        _pendingUpdate.remove_if([&update](const Update& item)
        {
            return item.evt == update.evt && item.merge;
        });
    }
    _pendingUpdate.push_back(update);
    _count.store(_pendingUpdate.size());
}

void UpdateQueue::push(int evt, bool merge, std::function<void()> exec)
{
    Update update;
    update.evt = evt;
    update.merge = merge;
    update.execute = exec;
    push(update);
}

UpdateQueue::Update UpdateQueue::pop()
{
    if (_pendingUpdate.size())
    {
        _count.store(_pendingUpdate.size() - 1);
        auto u = _pendingUpdate.front();
        _pendingUpdate.pop_front();
        return u;
    }
    return Update{ -1, false, nullptr };
}

void UpdateQueue::execute()
{
    if (_count.load() > 0)
    {
        std::list<Update> pendingUpdate;
        {
            std::unique_lock<std::mutex> lck(_pendingUpdateMutex);
            pendingUpdate.swap(_pendingUpdate);
        }
        for (auto& update: pendingUpdate)
        {
            assert(update.execute != nullptr);
            update.execute();
        }
    }
}

} // namespace hgc
