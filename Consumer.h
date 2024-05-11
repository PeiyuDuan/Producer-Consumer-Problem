/*
*  本文件完成 Consumer 的书写
*    
*    Consumer 是消费者的抽象。
*   
*    Consumer 的工作过程为尝试从缓冲区中获取一个元素，并将其消费。
*
*    主要方法：
*
*      - onAdded() 添加新消费者时将消费者者移动至制定区域
*      - work() 工作过程，消费者退出时会有消息提示
*
*/

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