#pragma once
#include <array>
#include <algorithm>
#include <numeric>
#include "Queue.h"

class Consumer
{
private:
	std::shared_ptr<Queue> ptrQueue;
	int numSortedArrays = 0;

public:
	Consumer(std::shared_ptr<Queue> ptrQueue);
	void consume();
};
