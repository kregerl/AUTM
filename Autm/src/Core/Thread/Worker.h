#ifndef AUTM_WORKER_H
#define AUTM_WORKER_H

#include "autmpch.h"
#include "TaskQueue.h"

class Worker {
public:
    Worker() = default;

    Worker(std::shared_ptr<TaskQueue>& task_queue, uint32_t id) : m_queue(task_queue), m_id(id) {
        m_thread = std::thread([this]() {
            run();
        });
    }

    void run() {
        while (m_running) {
            m_task = m_queue->get_task();
            if (m_task == nullptr) {
                TaskQueue::wait();
            } else {
                m_task();
                m_queue->done();
                m_task = nullptr;
            }
        }
    }

    void stop() {
        m_running = false;
        if (m_thread.joinable())
            m_thread.join();
    }

private:
    uint32_t m_id = 0;
    std::thread m_thread;
    bool m_running = true;
    Task m_task = nullptr;
    std::shared_ptr<TaskQueue> m_queue;
};

#endif //AUTM_WORKER_H
