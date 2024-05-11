#include <easyx.h>

#include "ThreadController.h"
#include "Producer.h"
#include "Consumer.h"
#include "Buffer.h"
#include "EnvironmentAndTools.h"

using namespace std;
using namespace chrono_literals;

void ThreadController::setProduceNum() const {
	Producer::setProduceNum(produceNum_);
}

void ThreadController::setProduceTimeByIntAux() const {
	chrono::milliseconds result = chrono::milliseconds(produceTimeAux_);
	SetProduceTime(result);
}

void ThreadController::SetBufferSize() const {
	buf.setCapacity(bufferSize_);
}

void ThreadController::setWaitTimeByIntAux() const {
	chrono::seconds result = chrono::seconds(waitTimeAux_);
	SetWaitTime(result);
}

void ThreadController::setConsumeTimeByIntAux() const {
	chrono::milliseconds result = chrono::milliseconds(consumeTimeAux_);
	SetConsumeTime(result);
}

void ThreadController::beginwork() {
	projectBegun = true;
	thread w([this]() {this->workingThread(); });
	w.join();
}
void ThreadController::addProducer() {
	int nowNum = static_cast<int>(producers_.size());
	producers_.emplace_back(new Producer(nowNum + 1));
}
void ThreadController::addConsumer() {
	int nowNum = static_cast<int>(consumers_.size());
	consumers_.emplace_back(new Consumer(nowNum + 1));
}

void ThreadController::keyInput(wchar_t ch) {
	for (auto inputBlock : inputBlocks()) {
		if (inputBlock->isSelected()) {
			inputBlock->keyInput(ch);
		}
	}
}

void ThreadController::mouseClick(int mouseX, int mouseY) {
	for (auto button : buttons()) {
		if (button->Clicked(mouseX, mouseY)) {
			break;
		}
	}

	for (auto inputBlock : inputBlocks()) {
		inputBlock->Clicked(mouseX, mouseY);
	}
}

void ThreadController::mouseMove(int mouseX, int mouseY) {
	for (auto button : buttons()) {
		button->checkMouseOver(mouseX, mouseY);
	}
}

void ThreadController::workingThread() {
	vector<thread> p;
	vector<thread> c;

	for (auto pro : producers_) {
		p.emplace_back(&Producer::work, pro);
	}
	for (auto con : consumers_) {
		c.emplace_back(&Consumer::work, con);
	}

	for (auto& t : p) {
		t.join();
	}
	productionStopped = true;
	for (auto& t : c) {
		t.join();
	}
	consumptionStopped = true;
}

void ThreadController::settingThread() {
	ExMessage msg;
	while (!projectBegun) {
		if (peekmessage(&msg)) {
			int mouseX = msg.x;
			int mouseY = msg.y;
			switch (msg.message) {
				case WM_LBUTTONDOWN:
					mouseClick(mouseX, mouseY);
					break;
				case WM_MOUSEMOVE:
					mouseMove(mouseX, mouseY);
					break;
				case WM_CHAR:
					keyInput(msg.ch);
					break;
			}
		}
		this_thread::sleep_for(10ms);
	}
}

void ThreadController::graphThread() {

	initgraph(kSceneWidth, kSceneHeight, 1);
	setbkcolor(WHITE);
	cleardevice();
	while (!productionStopped || !consumptionStopped) {
		DrawAllThings();
		this_thread::sleep_for(1ms);
	}
	closegraph();
}

void ThreadController::mainThread() {
	SetProduceTime(kDefaultProduceTime);
	SetConsumeTime(kDefaultConsumeTime);
	SetWaitTime(kDefaultWaitTime);
	thread g([this]() {this->graphThread(); });
	addProducer();
	addConsumer();
	thread s([this]() {this->settingThread(); });
	s.join();
	g.join();
}