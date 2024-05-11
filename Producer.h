#pragma once
#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "TextBlock.h"
#include "EnvironmentAndTools.h"

class Producer final : public TextBlock {
private:
	int id_;
	static int produceNum_;

	void onAdded();
public:
	Producer(int id, int x = 180, int y = kSceneHeight, int produceNum = 15, int width = kDefaultWidth, int height = kDefaultHeight);

	static void setProduceNum(int produceNum);

	void work() const;

	virtual ~Producer();
};

#endif