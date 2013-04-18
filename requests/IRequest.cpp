#include <random>
#include "IRequest.hpp"

QString QMine::Requests::genUuidv4() {
	auto toChar = [](int i) {
		if (i >= 0x0 && i <= 0x9)
			return static_cast<char>(i + '0');
		return static_cast<char>(i + 87);
	};
	QByteArray tmp = QByteArray("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx");
	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_dist(0x0, 0xe);
	std::uniform_int_distribution<int> uniform_dist2(0x8, 0xb);

	for (int i = 0; i < tmp.size(); ++i) {
		if (tmp.at(i) == 'x') {
			tmp[i] = toChar(uniform_dist(e1));
		} else if (tmp.at(i) == 'y') {
			tmp[i] = toChar(uniform_dist2(e1));
		}
	}
	return QString(tmp);
}
