#include <random>
#include "LoadRequest.hpp"

QMine::Requests::LoadRequest::LoadRequest(QString path, LoadType type) {
  id = genUuidv4();
  this->type = Load;
  this->path = path;
  this->loadType = type;
  fileToUpload = new QFile(path);
  size = fileToUpload->size();
  line = 0;
  std::random_device rd;
  std::default_random_engine e1(rd());
  std::uniform_int_distribution<int> uniform_dist(1024, 65536);
  port = uniform_dist(e1);
  request = QString("LOAD={\"id\":\"") + id + QString("\",\"path\":\"") + this->path + QString("\",\"size\":\"") +
	  QString(this->size) + QString("\",\"line\":\"") +
	  QString(this->line) + QString("\",\"type\":\"") +
	  typeToString() + QString("\",\"port\":\"") +
	  QString(this->port) + QString("\"}");
  if (request.length() > 4096) {
	// TODO : raise an exception
  }
}

QMine::Requests::LoadRequest::~LoadRequest() {
  delete fileToUpload;
}

QString QMine::Requests::LoadRequest::typeToString() {
  if (loadType == Up)
	return QString("Up");
  return QString("Down");
}
