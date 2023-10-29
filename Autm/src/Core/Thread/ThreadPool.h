#ifndef AUTM_THREADPOOL_H
#define AUTM_THREADPOOL_H

#include "autmpch.h"
#include "Worker.h"

class ThreadPool {
public:
    explicit ThreadPool(uint32_t num_threads) : m_num_threads(num_threads) {
        m_workers.reserve(num_threads);
        for (uint32_t i = 0; i < num_threads; i++) {
            m_workers.emplace_back(m_task_queue, static_cast<uint32_t>(m_workers.size()));
        }
    }

    ~ThreadPool() {
        for (auto &worker: m_workers) {
            worker.stop();
        }
    }

    template<typename Callback>
    void add_task(Callback &&callback) {
        m_task_queue->add_task(std::forward<Callback>(callback));
    }

    void wait() const {
        m_task_queue->wait_all();
    }

    template<typename Callback>
    void dispatch(uint32_t element_count, Callback &&callback) {
        const uint32_t batch_size = element_count / m_num_threads;
        for (uint32_t i = 0; i < m_num_threads; i++) {
            const uint32_t start = batch_size * i;
            const uint32_t end = start + batch_size;
            add_task([start, end, &callback]() { callback(start, end); });
        }

        if (batch_size * m_num_threads < element_count) {
            const uint32_t start = batch_size * m_num_threads;
            callback(start, element_count);
        }
        wait();
    }

private:
    uint32_t m_num_threads = 0;
    std::shared_ptr<TaskQueue> m_task_queue;
    std::vector<Worker> m_workers;
};


#endif //AUTM_THREADPOOL_H
