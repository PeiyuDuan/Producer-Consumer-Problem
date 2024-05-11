#include <easyx.h>
#include "Button.h"

using namespace std;
using namespace chrono_literals;

Button::Button(int x, int y, int width, int height, const wstring& text, const function<void()>& onclick)
	:SceneElement(x, y, width, height), isMouseOver_(false), scale_(1.0f), text_(text), onclick_(onclick) {
	buttons().push_back(this);
	AddElement(this);
}

Button::~Button() {
	DeleteElement(this);
	buttons().erase(find(buttons().begin(), buttons().end(), this));
}

bool Button::mouseIsOver(int mouseX, int mouseY) const {
	return (mouseX >= x_ && mouseX <= x_ + width_ && mouseY >= y_ && mouseY <= y_ + height_);
}

void Button::checkMouseOver(int mouseX, int mouseY) {
	isMouseOver_ = mouseIsOver(mouseX, mouseY);

	if (isMouseOver_) {
		scale_ = 0.9f;
	}
	else {
		scale_ = 1.0f;
	}
}

bool Button::Clicked(int mouseX, int mouseY) {
	if (mouseIsOver(mouseX, mouseY)) {
		if (onclick_) {
			onclick_();
		}
		isMouseOver_ = false;
		scale_ = 1.0f;
		return true;
	}
	return false;
}

void Button::Draw() const {
	int scaledWidth = static_cast<int>(width_ * scale_);
	int scaledHeight = static_cast<int>(height_ * scale_);
	int scaledX = x_ + (width_ - scaledWidth) / 2;
	int scaledY = y_ + (height_ - scaledHeight) / 2;

	if (isMouseOver_) {
		setlinecolor(RGB(0, 120, 215));
		setfillcolor(RGB(229, 241, 251));
	}
	else {
		setlinecolor(RGB(173, 173, 173));
		setfillcolor(RGB(225, 225, 225));
	}

	fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight);
	settextcolor(BLACK);
	settextstyle(static_cast<int>(20 * scale_), 0, L"Î¢ÈíÑÅºÚ");
	int textX = scaledX + (scaledWidth - textwidth(text_.c_str())) / 2;
	int textY = scaledY + (scaledHeight - textheight(L"Î¢ÈíÑÅºÚ")) / 2;
	outtextxy(textX, textY, text_.c_str());
}