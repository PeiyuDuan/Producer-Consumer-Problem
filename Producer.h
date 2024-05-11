/*
*  本文件完成 Producer 的书写
*    
*    Producer 是生产者的抽象。
*   
*    Producer 的工作过程生产一个元素，并将其添加到缓冲区中。
*
*    主要方法：
*
*      - onAdded() 添加生产者时将生产者移动至制定区域
*      - work() 工作过程，生产者退出时会有消息提示
*      - setProduceNum(int produceNum) 设置每个生产者需要生产的元素数量
*
*/

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