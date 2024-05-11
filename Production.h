#pragma once
#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

#include "EnvironmentAndTools.h"
#include "TextBlock.h"

class Production final : public TextBlock {

	friend class Producer;
	friend class Consumer;

private:
	int id_;
	int validWidth_;

	void changeValidWidth(std::chrono::milliseconds t, bool inProducing);

public:
	Production(int id, int x, int y, int width = kItemWidth, int height = kItemHeight);

	void Draw() const;

	void produced();
	void consumed();

	virtual ~Production();
};

#endif