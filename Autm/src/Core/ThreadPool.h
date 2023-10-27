#ifndef AUTM_THREADPOOL_H
#define AUTM_THREADPOOL_H

#include "autmpch.h"

class ThreadPool {
public:
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    explicit ThreadPool(uint64_t num_workers);
    ~ThreadPool();

    template<class F, class... Args>
    std::future<std::result_of_t<F(Args...)>> enqueue(F &&f, Args&&... args);
private:
    void clean_up();
    void thread_main();
private:
    using Task = std::function<void()>;

    std::vector<std::thread> m_workers;
    std::queue<Task> m_tasks;

    std::mutex m_mutex;
    std::condition_variable m_condition_var;
    bool m_should_stop;
};


#endif //AUTM_THREADPOOL_H
