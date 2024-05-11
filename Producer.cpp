#include "Producer.h"
#include "Production.h"
#include "Buffer.h"

using namespace std;
using namespace chrono_literals;

int Producer::produceNum_;

Producer::Producer(int id, int x, int y, int produceNum, int width, int height)
	: TextBlock(x, y, width, height, L"Producer "), id_(id) {
	text_ += to_wstring(id_);
	AddElement(this);
	onAdded();
}

Producer::~Producer() {
	DeleteElement(this);
}

void Producer::onAdded() {
	MoveTo(x_, id_ * 30 + 20);
}

void Producer::setProduceNum(int produceNum) {
	produceNum_ = produceNum;
}

void Producer::work() const {
	for (int i = 0; i < produceNum_; i++) {
		Production* item = new Production(id_ * 100 + i, x_ + 120, y_);

		item->produced();
		pcout{} << " Producer " << id_ << " --> Item " << setw(3) << item->id_ << '\n';

		buf.push(item);
	}

	pcout{} << "EXIT: Producer " << id_ << '\n';
}