#include <QTcpSocket>
#include <QMessageBox>
#include "FileUploader.hpp"

/*
 ** FileUploader ctor
 */
QMine::Requests::FileUploader::FileUploader(int port, QByteArray msg) {
  server = new QTcpServer(this);
  this->port = port;
  this->msg = msg;
}

/*
 ** FileUploader dtor
 */
QMine::Requests::FileUploader::~FileUploader() {
  delete socket;
  delete server;
}

/*
 ** FileUploader main loop : reimplemented from QThread::run()
 */
void QMine::Requests::FileUploader::run() {
  if (server->listen(QHostAddress::Any, port)) {
	if (server->waitForNewConnection(-1)) {
	  socket = server->nextPendingConnection();
	  if (socket != nullptr) {
		int ret = socket->write(msg);
		if (ret == -1) {
		  QMessageBox::critical(nullptr, "QMine", "Error while uploading file");
		} else {
		  socket->flush();
		}
	  }
	}
  }
}
