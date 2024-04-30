#pragma once
#include <array>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <iostream>

int const ARRSIZE = 100000;
static  std::mutex mutex;
static  std::mutex coutMutex;

class Queue
{
private:
	std::queue<std::unique_ptr<std::array<int, ARRSIZE>>> queue;
	int maxSize = 0;
	int length = 0;
	bool isFinished = false;
	
public:
	Queue(int maxSize);
	void push(std::unique_ptr<std::array<int, ARRSIZE>> array);
	std::unique_ptr<std::array<int, ARRSIZE>> pop();
	int size();
	bool isFull();
	bool isEmpty();
	void setFinished();
	bool getFinished();
	~Queue();
};
