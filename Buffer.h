/*
*  本文件完成 Buffer 的书写
*    
*    Buffer 是生产者和消费者共同可读内存的抽象。
*    多线程共同读写的控制实现在 push() 和 pop() 中。
*   
*    本项目中 Buffer 的底层使用了简单的队列实现，可以使用无锁队列等内容来提高效率。
*
*    主要方法：
*
*      - push(Production* item) 将产品加入队列
*      - pop() 将队首的产品取出
*      - empty() 线程安全地判断队列是否为空
*      - setCapacity(int capacity) 设置缓冲区最大容量
*
*    注意事项：
*      - 本文件声明了一个全局变量 buf 供 Producer 和 Consumer 使用
*      - 由于可以确保在使用前被正确初始化完成，故不采用工厂函数的方式定义
*      - 生产结束后缓冲区空置 waitTime 后，才允许消费者退出
*
*/

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