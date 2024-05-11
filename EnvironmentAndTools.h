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

const std::wstring kBufferSizePrompt{ L"����������\n�����鳬��20\n�Ƽ�������5��15" };
const std::wstring kWaitTimePrompt{ L"���еȴ�ʱ��\n��λ��s\n�Ƽ�ʱ�䣺����ʱ���10��" };
const std::wstring kConsumeTimePrompt{ L"ÿ����Ʒ����ʱ��\n��λ��ms\n�Ƽ�ʱ�䣺50��1000" };
const std::wstring kProduceTimePrompt{ L"ÿ����Ʒ����ʱ��\n��λ��ms\n�Ƽ�ʱ�䣺50��1000" };
const std::wstring kProduceNumPrompt{ L"�����߲�Ʒ����\n�����鳬��100\n�Ƽ�������15" };

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