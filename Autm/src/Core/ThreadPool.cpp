#include "ThreadPool.h"

ThreadPool::ThreadPool(uint64_t num_workers) : m_should_stop(false) {
    m_workers.reserve(num_workers);
    try {
        for (uint32_t i = 0 ;i < num_workers; i++) {
            m_workers.emplace_back(&ThreadPool::thread_main, this);
        }
    } catch (...) {
        clean_up();
        throw;
    }
}

ThreadPool::~ThreadPool() {
    clean_up();
}

void ThreadPool::clean_up() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_should_stop = true;
    }
    m_condition_var.notify_all();
    for (auto& worker : m_workers) {
        if (worker.joinable())
            worker.join();
    }
}

void ThreadPool::thread_main() {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            // Loop so a false thread wakeup is handled
            while (m_tasks.empty()) {
                if (m_should_stop)
                    return;
                m_condition_var.wait(lock);
            }
            task = std::move(m_tasks.front());
            m_tasks.pop();
        }
        task();
    }
}

template<class F, class... Args>
std::future<std::result_of_t<F(Args...)>> ThreadPool::enqueue(F &&f, Args&&... args) {
    return nullptr;
}
