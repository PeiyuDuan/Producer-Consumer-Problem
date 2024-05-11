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