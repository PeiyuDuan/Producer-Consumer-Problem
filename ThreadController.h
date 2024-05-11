/*
*  本文件完成 ThreadController 的书写
*  ThreadController 是控制所有进程的文件
*    
*    文件中定义了所有需要的按钮、工具函数的元素。
*
*    主要线程：
*
*      - settingThread 完成开始工作前的控制内容
*      - workingThread 完成添加生产者消费者、等待生产者消费者结束的主要工作进程
*      - graphThread 画图进程，独立于所有进程之外，每隔一段时间就画一遍所有的元素
*      - mainThread 外部使用的主线程
*
*/

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

	Button startButton_{ 30, 20, 100, 25, L"开始工作", [this]() { this->beginwork(); } };
	Button addProducerButton_{ 180, 20, 100, 25, L"加入生产者", [this]() { this->addProducer(); } };
	Button addConsumerButton_{ 620, 20, 100, 25, L"加入消费者", [this]() { this->addConsumer(); } };

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