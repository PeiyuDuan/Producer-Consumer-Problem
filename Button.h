#pragma once
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <string>
#include <functional>
#include"EnvironmentAndTools.h"
#include "SceneElement.h"

class Button final : public SceneElement {
private:
	bool isMouseOver_;
	float scale_;
	std::wstring text_;
	std::function<void()> onclick_;

	bool mouseIsOver(int mouseX, int mouseY) const;

public:
	void checkMouseOver(int mouseX, int mouseY);

	bool Clicked(int mouseX, int mouseY);

	void Draw() const;

	Button(int x, int y, int width = kDefaultWidth, int height = kDefaultHeight, const std::wstring& text = L"", const std::function<void()>& onclick = nullptr);

	virtual ~Button();
};

#endif