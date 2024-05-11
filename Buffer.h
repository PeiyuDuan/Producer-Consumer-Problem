#pragma once
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <queue>
#include "TextBlock.h"
#include "EnvironmentAndTools.h"

class Buffer final : public TextBlock {
private:
	std::queue<Production*> q_;
	mutable std::mutex qMutex_;

	int capacity_;

	std::condition_variable notFull_;
	std::condition_variable notEmpty_;

public:
	Buffer(int x, int y, int width = kDefaultWidth, int height = kDefaultHeight * 30, int capacity = 15);

	void push(Production* item);

	Production* pop();

	bool empty() const;

	void setCapacity(int capacity);

	virtual ~Buffer();

};

extern Buffer buf;

#endif