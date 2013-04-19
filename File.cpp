#include <QList>
#include <QByteArray>
#include <algorithm>
#include "File.hpp"

QMine::File::File(QString path) {
  this->path = path;
  internFile = new QFile(path);
  internFile->open(QIODevice::ReadWrite);
  title = internFile->fileName();
  file = QStringList();

  QByteArray b = internFile->readAll();
  for (int i = 0; i < b.count('\n'); ++i) {
	file << "";
  }
  int j = 0;
  for (int i = 0; i < internFile->size(); ++i) {
	if (b.at(i) == '\n') {
	  ++j;
	} else {
	  file[j].push_back(b.at(i));
	}
  }
}

QMine::File::~File() {
  delete internFile;
}

QString QMine::File::getTitle() {
  return title;
}

QString QMine::File::getPath() {
  return path;
}

QString QMine::File::getFile() {
  return file.join('\n');
}
