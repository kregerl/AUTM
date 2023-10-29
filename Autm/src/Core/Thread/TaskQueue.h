#ifndef AUTM_TASKQUEUE_H
#define AUTM_TASKQUEUE_H

#include <autmpch.h>

using Task = std::function<void()>;

class TaskQueue {
public:
    TaskQueue() = default;

    template<typename Callback>
    void add_task(Callback &&callback) {
        std::lock_guard<std::mutex> guard{m_mutex};
        m_tasks.push(std::forward<Callback>(callback));
        m_tasks_remaining++;
    }

    Task get_task() {
        std::lock_guard<std::mutex> guard{m_mutex};
        if (m_tasks.empty())
            return nullptr;

        auto callback = std::move(m_tasks.front());
        m_tasks.pop();
        return callback;
    }

    static void wait() {
        std::this_thread::yield();
    }

    void wait_all() const {
        while (m_tasks_remaining > 0) {
            wait();
        }
    }

    void done() {
        m_tasks_remaining--;
    }

private:
    std::mutex m_mutex;
    std::queue<Task> m_tasks;
    std::atomic<uint32_t> m_tasks_remaining = 0;
};


#endif //AUTM_TASKQUEUE_H
