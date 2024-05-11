#include "Buffer.h"
#include "Production.h"
#include "EnvironmentAndTools.h"

using namespace std;
using namespace chrono_literals;

Buffer::Buffer(int x, int y, int width, int height, int capacity) 
	: TextBlock(x, y, width, height), capacity_(capacity) {
	AddElement(this);
}

void Buffer::push(Production* item) {
	unique_lock<mutex> lock(qMutex_);
	notFull_.wait(lock, [this] { return q_.size() < capacity_; });
	q_.push(item);
	item->MoveTo(x_ + 15, y_ + 30 * static_cast<int>(q_.size()));
	notEmpty_.notify_all();
}

Production* Buffer::pop() {
	unique_lock<mutex> lock(qMutex_);
	if (notEmpty_.wait_for(lock, waitTime, [this] {return !q_.empty(); })) {
		Production* item = q_.front();

		queue<Production*> tempQueue;
		while (!q_.empty()) {
			tempQueue.push(q_.front());
			q_.pop();
		}
		while (!tempQueue.empty()) {
			Production* item = tempQueue.front();
			item->MoveUp(30);
			q_.push(item);
			tempQueue.pop();
		}

		q_.pop();
		notFull_.notify_all();
		return item;
	}

	return nullptr;
}

bool Buffer::empty() const {
	unique_lock<mutex> lock(qMutex_);
	return q_.empty();
}

void Buffer::setCapacity(int capacity) {
	capacity_ = capacity;
}

Buffer::~Buffer() {
	DeleteElement(this);
}

Buffer buf(400, 15);