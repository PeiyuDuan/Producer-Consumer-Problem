#pragma once
#ifndef __THREAD_CONTROLLER_H__
#define __THREAD_CONTROLLER_H__

#include <vector>
#include "EnvironmentAndTools.h"
#include "Button.h"
#include "InputBlock.h"

class ThreadController {
private:
	std::vector<Producer*> producers_;
	std::vector<Consumer*> consumers_;

	Button startButton_{ 30, 20, 100, 25, L"��ʼ����", [this]() { this->beginwork(); } };
	Button addProducerButton_{ 180, 20, 100, 25, L"����������", [this]() { this->addProducer(); } };
	Button addConsumerButton_{ 620, 20, 100, 25, L"����������", [this]() { this->addConsumer(); } };

	int produceNum_;
	int produceTimeAux_;
	int consumeTimeAux_;
	int waitTimeAux_;
	int bufferSize_;

	InputBlock maxProduceNumBlock{ 30, 150, produceNum_, 15, [this]() { this->setProduceNum(); }, kProduceNumPrompt };
	InputBlock produceTimeBlock{ 30, 250, produceTimeAux_, 90, [this]() { this->setProduceTimeByIntAux(); }, kProduceTimePrompt };
	InputBlock consumeTimeBlock{ 30, 350, consumeTimeAux_, 130, [this]() { this->setConsumeTimeByIntAux(); }, kConsumeTimePrompt };
	InputBlock waitTimeBlock{ 30, 450, waitTimeAux_, 1, [this]() { this->setWaitTimeByIntAux(); }, kWaitTimePrompt };
	InputBlock bufferSizeBlock{ 30, 550, bufferSize_, 15, [this]() { this->SetBufferSize(); }, kBufferSizePrompt };

private:
	void setProduceNum() const;
	void setProduceTimeByIntAux() const;
	void SetBufferSize() const;
	void setWaitTimeByIntAux() const;
	void setConsumeTimeByIntAux() const;

	void beginwork();
	void addProducer();
	void addConsumer();

	void keyInput(wchar_t ch);
	void mouseClick(int mouseX, int mouseY);
	void mouseMove(int mouseX, int mouseY);

	void settingThread();
	void workingThread();
	void graphThread();

public:

	void mainThread();
};

#endif