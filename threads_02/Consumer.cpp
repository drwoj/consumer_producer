#include "Consumer.h"

Consumer::Consumer(std::shared_ptr<Queue> ptrQueue) {
	this->ptrQueue = ptrQueue;
}

void Consumer::consume() {
	int checksum = 0;
	std::unique_ptr<std::array<int, ARRSIZE>> array;
	while ( (!ptrQueue->getFinished()) || (!ptrQueue->isEmpty()) ) {

		while (!ptrQueue->getFinished() && ptrQueue->isEmpty()) {
			std::this_thread::yield();
		}

		array = ptrQueue->pop();

		if (array == nullptr) {
			continue;
		}

		std::sort(array->begin(), array->end());
		numSortedArrays++;
		checksum = std::accumulate(array->begin(), array->end(), 0);
	}

	{
		std::scoped_lock lock(coutMutex);
		std::cout << "number of sorted arrays: " << numSortedArrays << std::endl;
	}
}
