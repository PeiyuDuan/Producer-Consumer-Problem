/*
*  本文件完成 Button 的书写
*    
*    Button 是使用 easyx 库实现的简单的按钮类
*    实现了鼠标悬浮在按钮上方时的变色以及点击时进行某种工作的功能
*
*    主要方法：
*
*      - mouseIsOver(int mouseX, int mouseY) 判断当前鼠标位置是否在按钮上
*      - Clicked() 鼠标点击时的行为。如果鼠标点击的是这个按钮，则进行一系列行动
*      - Draw() 继承的虚函数，将按钮画在界面上
*
*/

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