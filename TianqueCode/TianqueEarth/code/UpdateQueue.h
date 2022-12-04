#ifndef HGC_UPDATE_QUEUE_H
#define HGC_UPDATE_QUEUE_H

#include <functional>
#include <mutex>
#include <list>
#include <atomic>

namespace chcEarth {

class UpdateQueue
{
public:
    struct Update
    {
        int evt;
        bool merge;
        std::function<void()> execute;
    };

    UpdateQueue();

    ~UpdateQueue();

    void push(const Update& update);
    void push(int evt, bool merge, std::function<void()> exec);

    void execute();

protected:
    Update pop();

private:
    std::mutex _pendingUpdateMutex;
    std::list<Update> _pendingUpdate;
    std::atomic<size_t> _count;
};

} // hgc

#endif //HGC_UPDATE_QUEUE_H
