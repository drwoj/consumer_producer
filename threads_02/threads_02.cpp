#include "Queue.h"
#include "Consumer.h"
#include "Producer.h"
#include <chrono>

const int NUM_CONSUMERS = 4;
int main()
{
    std::shared_ptr<Queue> ptrQueue = std::make_shared<Queue>(2560);
    Producer producer(ptrQueue, 25600);

    std::vector<Consumer> consumers;
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumers.emplace_back(ptrQueue);
    }

    std::thread producerThread(&Producer::produce, &producer);

    auto start = std::chrono::system_clock::now();
    std::vector<std::thread> consumerThreads;
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumerThreads.emplace_back(&Consumer::consume, &consumers[i]);
    }

    producerThread.join();
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumerThreads[i].join();
    }

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Duration: " << duration << "ms" << std::endl;
}