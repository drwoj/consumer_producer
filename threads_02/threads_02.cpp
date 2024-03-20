#include "Queue.h"
#include "Consumer.h"
#include "Producer.h"
#include <chrono>

int main()
{
	std::shared_ptr<Queue> ptrQueue = std::make_shared<Queue>(10);
	
	Producer producer(ptrQueue, 100);
	Consumer consumer01(ptrQueue);
	Consumer consumer02(ptrQueue);
	Consumer consumer03(ptrQueue);
	Consumer consumer04(ptrQueue);

	std::thread producerThread(&Producer::produce, &producer);

	auto start = std::chrono::system_clock::now();
	std::thread consumerThread01(&Consumer::consume, &consumer01);
	std::thread consumerThread02(&Consumer::consume, &consumer02);
	std::thread consumerThread03(&Consumer::consume, &consumer03);
	std::thread consumerThread04(&Consumer::consume, &consumer04);
	
	producerThread.join();
	consumerThread01.join();
	consumerThread02.join();
	consumerThread03.join();
	consumerThread04.join();
	auto end = std::chrono::system_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Duration: " << duration << "ms" << std::endl;
}
