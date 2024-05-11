#include <easyx.h>
#include "InputBlock.h"

using namespace std;
using namespace chrono_literals;

InputBlock::InputBlock(int x, int y, int& relatedVariable, int defaultValue, const function<void()>& auxToReal,
	const wstring& prompt, int width, int height)
	:SceneElement(x, y, width, height), isSelected_(false), showCursor_(false), cursorPos_(0),
	relatedVariable_(relatedVariable), defaultValue_(defaultValue), onChanged_(auxToReal), prompt_(prompt) {
	inputBlocks().push_back(this);
	AddElement(this);

	lastTick_ = chrono::steady_clock::now();
	setText(to_wstring(defaultValue_));
	relatedVariable_ = defaultValue_;
	if (onChanged_) {
		onChanged_();
	}
}

InputBlock::~InputBlock() {
	DeleteElement(this);
	inputBlocks().erase(find(inputBlocks().begin(), inputBlocks().end(), this));
}

bool InputBlock::mouseIsOver(int mouseX, int mouseY) const {
	return (mouseX >= x_ && mouseX <= x_ + width_ && mouseY >= y_ && mouseY <= y_ + height_);
}

void InputBlock::updateCursor() const {
	auto currentTick = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(currentTick - lastTick_).count();

	if (elapsed >= 500) {
		showCursor_ = !showCursor_;
		lastTick_ = currentTick;
	}
}

void InputBlock::setText(const wstring& newText) {
	text_ = newText;
	cursorPos_ = static_cast<int>(text_.length());
}

void InputBlock::updateRelatedVariable() {
	try {
		relatedVariable_ = stoi(text_);
		if (onChanged_) {
			onChanged_();
		}
	}
	catch (invalid_argument&) {
		relatedVariable_ = defaultValue_;
		setText(to_wstring(defaultValue_));
		if (onChanged_) {
			onChanged_();
		}
	}
}

bool InputBlock::isSelected() const {
	return isSelected_;
}

const wstring& InputBlock::getText() const {
	return text_;
}

void InputBlock::Draw() const {
	setfillcolor(WHITE);
	if (isSelected_) {
		setlinecolor(RGB(0, 120, 215));
	}
	else {
		setlinecolor(RGB(122, 122, 122));
	}

	fillrectangle(x_, y_, x_ + width_, y_ + height_);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, L"微软雅黑");
	// 分割提示信息，以处理换行符
	vector<wstring> lines;
	wistringstream iss(prompt_);
	wstring nowLine;
	while (getline(iss, nowLine, L'\n')) {
		lines.push_back(nowLine);
	}

	int yPos = y_ - 70; // 初始 y 坐标为按钮上方 100
	for (const auto& line : lines) {
		outtextxy(x_ + 5, yPos, line.c_str());
		yPos += textheight(L"微软雅黑") + 5; // 下一行的 y 坐标
	}

	settextstyle(height_ * 3 / 4, 0, L"微软雅黑");
	outtextxy(x_ + 5, y_ + (height_ - textheight(L"微软雅黑")) / 2, text_.c_str());
	setlinecolor(BLACK);

	updateCursor();
	if (isSelected_ && showCursor_) {
		int cursorX = x_ + 5 + textwidth(text_.substr(0, cursorPos_).c_str());
		line(cursorX, y_ + 2 + height_ / 8, cursorX, y_ + height_ * 7 / 8 - 2);
	}
}

void InputBlock::Clicked(int mouseX, int mouseY) {
	if (mouseIsOver(mouseX, mouseY)) {
		isSelected_ = true;
		return;
	}

	isSelected_ = false;
	cursorPos_ = static_cast<int>(text_.length());
}

void InputBlock::keyInput(wchar_t ch) {
	if (isSelected_) {
		switch (ch) {
			case '\b':
				if (!text_.empty() && cursorPos_ > 0) {
					text_.erase(cursorPos_ - 1, 1);
					cursorPos_--;
				}
				break;
			case '\r':
			case '\n':
				cursorPos_ = static_cast<int>(text_.length());
				isSelected_ = false;
				updateRelatedVariable();
				break;
			default:
				if (text_.length() < 20 && iswdigit(ch)) {
					text_.insert(cursorPos_, 1, ch);
					cursorPos_++;
					updateRelatedVariable();
				}
				break;
		}
	}
}