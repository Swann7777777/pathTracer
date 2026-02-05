class threadPoolClass {
    public:

    std::vector<std::thread> threadsVector;
    int threadsCount;
    std::mutex queueMutex;
    std::condition_variable conditionVariable;
    std::queue<std::function<void()>> tasks;
    bool stop;

    threadPoolClass() {
        threadsCount = std::thread::hardware_concurrency();
        stop = false;

        for (int i = 0; i < threadsCount; i++) {
            threadsVector.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        conditionVariable.wait(lock, [this] {
                            return !tasks.empty() || stop;
                        });

                        if (stop && tasks.empty()) {
                            return;
                        }

                        task = move(tasks.front());
                        tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    ~threadPoolClass() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        conditionVariable.notify_all();

        for (auto& thread : threadsVector) {
            thread.join();
        }
    }

    void enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::move(task));
        }

        conditionVariable.notify_one();
    }
};