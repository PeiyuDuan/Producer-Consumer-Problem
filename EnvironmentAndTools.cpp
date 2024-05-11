#include "EnvironmentAndTools.h"

using namespace std::chrono_literals;

std::mutex elementsMutex;

void AddElement(SceneElement* newItem) {
	std::unique_lock<std::mutex> lock(elementsMutex);
	allElements().push_back(newItem);
}

void DeleteElement(SceneElement* targetItem) {
	std::unique_lock<std::mutex> lock(elementsMutex);
	allElements().erase(find(allElements().begin(), allElements().end(), targetItem));
}

void DrawAllThings() {
	BeginBatchDraw();
	cleardevice();
	std::unique_lock<std::mutex> lock(elementsMutex);
	for (auto s : allElements()) {
		s->Draw();
	}
	lock.unlock();
	FlushBatchDraw();
	std::this_thread::sleep_for(10ms);
}

std::chrono::milliseconds produceTime;
std::chrono::milliseconds consumeTime;
std::chrono::milliseconds waitTime;

void SetProduceTime(std::chrono::milliseconds t) {
	produceTime = t;
}

void SetConsumeTime(std::chrono::milliseconds t) {
	consumeTime = t;
}

void SetWaitTime(std::chrono::milliseconds t) {
	waitTime = t;
}

bool projectBegun = false;
bool productionStopped = false;
bool consumptionStopped = false;