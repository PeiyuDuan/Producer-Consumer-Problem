/*
*  本文件完成一系列所需的全局变量及全局函数的书写
*    
*    全局变量如下：
*
*      - 所有元素的 vector, 使用 allElements() 工厂函数获取
*      - 所有按钮的 vector, 使用 buttons() 工厂函数获取
*      - 所有输入框的 vector, 使用 inputBlocks() 工厂函数获取
*      - 关于生产时间、消费时间、队列等待时间的定义
*      - 关于进程间通信的变量的定义
*
*    主要工具：
*
*      - AddElement(SceneElement* newItem) 添加元素时必须调用
*      - DeleteElement(SceneElement* targetItem) 元素析构函数调用时调用
*      - class pcout 实现了线程安全的 cout 操作
*
*    注意事项：
*      - 与 allElements() 有关的内容时需要多线程操作的，故在对应的工具函数中添加了包含机制
*
*/

#pragma once
#ifndef __ENVIRONMENT_AND_TOOLS_H__
#define __ENVIRONMENT_AND_TOOLS_H__

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <mutex>
#include <easyx.h>

#include "SceneElement.h"

class SceneElement;
class TextBlock;
class Button;
class Production;
class InputBlock;
class Buffer;
class Producer;
class Consumer;

using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kDefaultProduceTime = 90ms;
constexpr std::chrono::milliseconds kDefaultConsumeTime = 130ms;
constexpr std::chrono::milliseconds kDefaultWaitTime = 1s;

constexpr int kDefaultWidth = 100;
constexpr int kDefaultHeight = 25;

constexpr int kSceneWidth = 750;
constexpr int kSceneHeight = 650;

constexpr int kItemWidth = 70;
constexpr int kItemHeight = 25;

const std::wstring kBufferSizePrompt{ L"缓冲区容量\n不建议超出20\n推荐数量：5到15" };
const std::wstring kWaitTimePrompt{ L"队列等待时间\n单位：s\n推荐时间：生产时间的10倍" };
const std::wstring kConsumeTimePrompt{ L"每个产品消费时间\n单位：ms\n推荐时间：50到1000" };
const std::wstring kProduceTimePrompt{ L"每个产品生产时间\n单位：ms\n推荐时间：50到1000" };
const std::wstring kProduceNumPrompt{ L"生产者产品数量\n不建议超出100\n推荐数量：15" };

inline std::vector<SceneElement*>& allElements() {
	static std::vector<SceneElement*> validVector;
	return validVector;
}
extern std::mutex elementsMutex;

void AddElement(SceneElement* newItem);

void DeleteElement(SceneElement* targetItem);

void DrawAllThings();

inline std::vector<InputBlock*>& inputBlocks() {
	static std::vector<InputBlock*> validVector;
	return validVector;
}

inline std::vector<Button*>& buttons() {
	static std::vector<Button*> validVector;
	return validVector;
}

extern std::chrono::milliseconds produceTime;
extern std::chrono::milliseconds consumeTime;
extern std::chrono::milliseconds waitTime;

void SetProduceTime(std::chrono::milliseconds t);

void SetConsumeTime(std::chrono::milliseconds t);

void SetWaitTime(std::chrono::milliseconds t);

extern bool projectBegun;
extern bool productionStopped;
extern bool consumptionStopped;

struct pcout : public std::stringstream {
	static inline std::mutex out_mutex;
	~pcout() {
		std::lock_guard<std::mutex> l{ out_mutex };
		std::cout << rdbuf();
	}
};

#endif