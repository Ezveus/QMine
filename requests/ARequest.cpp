#include <random>
#include "ARequest.hpp"

QMine::Requests::ARequest::ARequest() {
}

QString QMine::Requests::ARequest::genUuidv4() {
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

QString QMine::Requests::ARequest::toQString() {
  return request;
}

const char *QMine::Requests::ARequest::toString() {
  return request.toStdString().c_str();
}

QByteArray QMine::Requests::ARequest::toByteArray() {
  return request.toLatin1();
}

int QMine::Requests::ARequest::length() {
  return request.length();
}

QString QMine::Requests::ARequest::getId() {
  return id;
}

QMine::Requests::RequestType QMine::Requests::ARequest::getType() {
  return type;
}

/*
 ** This method is called after receiving a RESPONSE request
 ** It checks the status of the response and calls the given function if
 ** the status is success
 */
void QMine::Requests::ARequest::response(const QJsonObject *o, std::function<void(const QJsonObject *)> f) {
  if (!o->contains("status") && !o->value("status").isDouble()) {
	// TODO : raise an exception
	return ;
  }
  if (o->value("status").toDouble() != SUCCESSFULL_REQUEST) {
	// TODO : raise an exception
	return ;
  }
  f(o);
}
