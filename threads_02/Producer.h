#pragma once
#include <array>
#include <cstdlib>
#include <time.h>
#include "Queue.h"

class Producer
{
private:
	std::shared_ptr<Queue> ptrQueue;
	int numberOfArrays;
	std::unique_ptr<std::array<int, ARRSIZE>> createPtrArray();
public:
	Producer(std::shared_ptr<Queue> ptrQueue, int numberOfArrays);
	void produce();
};
