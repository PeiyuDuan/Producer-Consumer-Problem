#include <easyx.h>
#include <thread>
#include "TextBlock.h"

using namespace std;

void TextBlock::Draw() const {
	setlinecolor(BLUE);
	rectangle(x_, y_, x_ + width_, y_ + height_);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, L"Î¢ÈíÑÅºÚ");

	int textWidth = textwidth(text_.c_str());
	int textHeight = textheight(text_.c_str());
	int textX = x_ + (width_ - textWidth) / 2;
	int textY = y_ + (height_ - textHeight) / 2;

	outtextxy(textX, textY, text_.c_str());
}

void TextBlock::MoveTo(int x, int y) {
	int dx = x - x_;
	int dy = y - y_;
	double distance = sqrt(dx * dx + dy * dy);

	while (x_ - x >= 5 || x_ - x <= -5 || y_ - y >= 5 || y_ - y <= -5) {
		if (x_ != x) {
			x_ = (x_ + x) / 2;
		}

		if (y_ != y) {
			y_ = (y_ + y) / 2;
		}

		this_thread::sleep_for(50ms);
	}

	x_ = x;
	y_ = y;
}

void TextBlock::MoveUp(int diff) {
	MoveTo(x_, y_ - diff);
}