#include "Queue.h"

Queue::Queue(int maxSize) {
	this->maxSize = maxSize;
	this->queue = std::queue<std::unique_ptr<std::array<int, ARRSIZE>>>();
	this->length = 0;
	this->isFinished = false;
}

void Queue::push(std::unique_ptr<std::array<int, ARRSIZE>> array) {
	if (isFull()) {
		return;
	}
	queue.push(std::move(array));
	length++;
}	

std::unique_ptr<std::array<int, ARRSIZE>> Queue::pop() {
	if (isEmpty()) {
		return nullptr;
	}
	auto array = std::move(queue.front());
	queue.pop();
	length--;
	return array;
}

int Queue::size() {
	return length;
}

bool Queue::isFull() {
	return length == maxSize;
}

bool Queue::isEmpty() {
	return length == 0;
}

void Queue::setFinished() {
	isFinished = true;
}

bool Queue::getFinished() {
	return isFinished;
}

Queue::~Queue() {
	std::cout<<"Queue destructor, stored elements: "<<size()<<std::endl;
}
