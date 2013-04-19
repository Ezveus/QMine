#ifndef FILEUPLOADER_HPP
#define FILEUPLOADER_HPP

#include <QThread>
#include <QTcpServer>

namespace QMine {
  namespace Requests {
	class FileUploader : public QThread {
	public:
	  FileUploader(int port, QByteArray msg);
	  ~FileUploader();

	  void run() override;

	private:
	  QTcpServer *server;
	  int port;
	  QByteArray msg;
	  QTcpSocket *socket;
	};
  }
}

#endif // FILEUPLOADER_HPP
