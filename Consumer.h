#pragma once
#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "EnvironmentAndTools.h"
#include "TextBlock.h"

class Consumer final : public TextBlock {
private:
	int id_;

	void onAdded();
public:
	Consumer(int id, int x = 620, int y = kSceneHeight, int width = kDefaultWidth, int height = kDefaultHeight);

	void work() const;

	virtual ~Consumer();
};

#endif