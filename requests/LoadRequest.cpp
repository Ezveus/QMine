#ifdef WINDOWS_SYSTEM
# include <windows.h>
# define sleep(x) Sleep(x * 1000)
#else
# include <unistd.h>
#endif
#include <random>
#include "LoadRequest.hpp"

QMine::Requests::LoadRequest::LoadRequest(QString path, LoadType type) {
  id = genUuidv4();
  this->type = Load;
  this->path = path;
  this->loadType = type;
  fileToUpload = new QFile(path);
  fileToUpload->open(QIODevice::ReadOnly);
  size = fileToUpload->size();
  line = 0;
  std::random_device rd;
  std::default_random_engine e1(rd());
  std::uniform_int_distribution<int> uniform_dist(1024, 65536);
  port = uniform_dist(e1);
  request = QString("LOAD={\"id\":\"") + id + QString("\",\"path\":\"") + this->path + QString("\",\"size\":");
  request += QString::number(this->size) + QString(",\"line\":");
  request += QString::number(this->line) + QString(",\"type\":\"");
  request += typeToString() + QString("\",\"port\":");
  request += QString::number(this->port) + QString("}");
  uploader = new Requests::FileUploader(port, getFile());
  if (request.length() > 4096) {
	// TODO : raise an exception
  }
}

QMine::Requests::LoadRequest::~LoadRequest() {
  delete fileToUpload;
  delete uploader;
}

int QMine::Requests::LoadRequest::getPort() {
  return port;
}

QByteArray QMine::Requests::LoadRequest::getFile() {
  return fileToUpload->readAll();
}

void QMine::Requests::LoadRequest::setUploader(FileUploader *fu) {
  uploader = fu;
}

void QMine::Requests::LoadRequest::startUpload() {
  uploader->start();
  sleep(2);
}

/*
 ** Converts the LOAD type to a QString
 */
QString QMine::Requests::LoadRequest::typeToString() {
  if (loadType == Up)
	return QString("up");
  return QString("down");
}

QString QMine::Requests::LoadRequest::getPath() {
  return path;
}
