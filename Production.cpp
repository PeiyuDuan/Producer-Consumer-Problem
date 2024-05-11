#include <easyx.h>
#include "Production.h"

using namespace std;
using namespace chrono_literals;

Production::Production(int id, int x, int y, int width, int height)
	:id_(id), validWidth_(0), TextBlock(x, y, width, height, L"Item ") {
	text_ += to_wstring(id_);
	AddElement(this);
}

Production::~Production() {
	DeleteElement(this);
}

void Production::changeValidWidth(chrono::milliseconds t, bool inProducing) {
	int target_width = inProducing ? kItemWidth : 0;
	int increment = inProducing ? 1 : -1;
	int change_amount = abs(target_width - validWidth_);

	int change_interval = static_cast<int>(t.count() / change_amount);

	while (validWidth_ != target_width) {
		validWidth_ += increment;
		validWidth_ = max(0, min(kItemWidth, validWidth_));

		this_thread::sleep_for(chrono::milliseconds(change_interval));
	}
}

void Production::Draw() const {
	setfillcolor(LIGHTBLUE);
	solidrectangle(x_, y_, x_ + validWidth_, y_ + height_);
	TextBlock::Draw();
}

void Production::produced() {
	changeValidWidth(produceTime, true);
}

void Production::consumed() {
	changeValidWidth(consumeTime, false);
}