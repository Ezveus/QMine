#ifndef FILEUPLOADER_HPP
#define FILEUPLOADER_HPP

#include <QThread>
#include <QTcpServer>

namespace QMine {
  namespace Requests {
	/*
	 ** FileUploader : A thread which goal is to upload a local file to the server
	 */
	class FileUploader : public QThread {
	public:
	  FileUploader(int port, QByteArray msg); // Ctor
	  ~FileUploader(); // Dtor

	  void run() override;

	private:
	  FileUploader();

	  QTcpServer *server;
	  int port;
	  QByteArray msg;
	  QTcpSocket *socket;
	};
  }
}

#endif // FILEUPLOADER_HPP
