#include "Producer.h"

Producer::Producer(std::shared_ptr<Queue> ptrQueue, int numberOfArrays) {
	this->ptrQueue = ptrQueue;
	this->numberOfArrays = numberOfArrays;
}

std::unique_ptr<std::array<int, ARRSIZE>> Producer::createPtrArray() {
	std::unique_ptr<std::array<int, ARRSIZE>> ptrArray = std::make_unique<std::array<int, ARRSIZE>>();
	for (int i = 0; i < ARRSIZE; i++) {
		(*ptrArray)[i] = rand() % 2115;
	}
	return ptrArray;
}

void Producer::produce() {
	std::unique_ptr<std::array<int, ARRSIZE>> ptrArray;
	for (int i = 0; i < numberOfArrays; i++) {
		while (ptrQueue->isFull()) {
			std::this_thread::yield();
		}

		{
			std::scoped_lock lock(mutex);
			ptrArray = createPtrArray();
			ptrQueue->push(std::move(ptrArray));
		}
	}
	ptrQueue->setFinished();
}

Producer::~Producer() {
	std::cout << "Producer destructor" << std::endl;
}
