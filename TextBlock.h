/*
*  本文件完成 TextBlock 的书写
*    
*    TextBlock 继承自 SceneElement, 不可被实例化，是可移动的文字区域
*   
*    主要方法：
*
*      - MoveTo(int x, int y) 将对应的文本框移动至 (x, y) 处
*      - NoveUp(int diff) 将对应的文本框向上移动 diff 距离
*
*/

#pragma once
#ifndef __TEXT_BLOCK_H__
#define __TEXT_BLOCK_H__

#include <string>
#include "SceneElement.h"

class TextBlock : public SceneElement {
protected:
	std::wstring text_;

	TextBlock(int x = 0, int y = 0, int width = 0, int height = 0, const std::wstring& t = L"")
		: text_(t), SceneElement(x, y, width, height) {}

public:
	virtual void Draw() const;
	void MoveTo(int x, int y);
	void MoveUp(int diff);
};

#endif