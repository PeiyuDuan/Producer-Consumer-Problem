/*
*  本文件完成 Production 的书写
*    
*    Production 时产品的抽象。
*   
*    Production 通过 Producer 在 heap 上生成，通过 Consumer 清理内存，不会造成内存泄漏。
*
*    主要方法：
*
*      - changeValidWidth(std::chrono::milliseconds t, bool inProducing) 模拟生产和消费的过程，具体表现为 validWidth_ 的更改
*      - produced() 被生产时展示过程
*      - consumed() 被消费时展示过程
*
*/

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