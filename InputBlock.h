/*
*  本文件完成 InputBlock 的书写
*
*    InputBlock 是使用 easyx 库书写的简单的输入框
*    实现了光标、选中时高亮等效果，最大输入长度 20 位，只能输入数字
*
*    主要方法：
*
*      - Draw() 绘制输入框及其内容
*      - Clicked(int mouseX, int mouseY): 处理鼠标点击事件
*      - keyInput(wchar_t ch): 处理键盘输入事件
*
*/

#pragma once
#ifndef __INPUTBLOCK_H__
#define __INPUTBLOCK_H__

#include <functional>
#include <string>
#include <chrono>

#include "SceneElement.h"
#include "EnvironmentAndTools.h"

class InputBlock final : public SceneElement {
private:
	int& relatedVariable_;
	int defaultValue_;
	std::function<void()> onChanged_;

	const std::wstring prompt_;
	std::wstring text_;
	bool isSelected_;
	mutable bool showCursor_;
	int cursorPos_;
	mutable std::chrono::steady_clock::time_point lastTick_;

	bool mouseIsOver(int mouseX, int mouseY) const;

	void updateCursor() const;

	void setText(const std::wstring& newText);

	void updateRelatedVariable();

public:
	InputBlock(int x, int y, int& relatedVariable, int defaultValue, const std::function<void()>& auxToReal = nullptr,
		const std::wstring& prompt = L"", int width = kDefaultWidth, int height = kDefaultHeight);

	virtual ~InputBlock();

	bool isSelected() const;

	const std::wstring& getText() const;

	void Draw() const;

	void Clicked(int mouseX, int mouseY);

	void keyInput(wchar_t ch);
};

#endif