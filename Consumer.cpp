#include "Consumer.h"
#include "Buffer.h"
#include "Production.h"

using namespace std;
using namespace chrono_literals;

Consumer::Consumer(int id, int x, int y, int width, int height)
	: TextBlock(x, y, width, height, L"Consumer "), id_(id) {
	text_ += to_wstring(id_);
	AddElement(this);
	onAdded();
}

Consumer::~Consumer() {
	DeleteElement(this);
}

void Consumer::onAdded() {
	MoveTo(x_, id_ * 30 + 20);
}

void Consumer::work() const {
	while (!productionStopped || !buf.empty()) {
		if (Production* item = buf.pop()) {
			item->MoveTo(530, y_);
			pcout{} << " Item " << setw(3) << item->id_ << " --> Consumer " << id_ << '\n';

			item->consumed();
			delete item;
		}
	}

	pcout{} << "EXIT: Consumer " << id_ << '\n';
}