#include <QMainWindow>
#include <QTcpSocket>
#include "requests/AuthenticateRequest.hpp"
#include "ConnectionDialog.hpp"
#include "File.hpp"

#ifndef WINDOW_HPP
#define WINDOW_HPP

namespace Ui {
  class Window;
}

namespace QMine {
  /*
   ** The main window of the program
   */
  class Window : public QMainWindow {
	Q_OBJECT

  public:
	explicit Window(QWidget *parent = 0);
	~Window();

  public slots:
	void dataReceived();
	void errorReceived(QAbstractSocket::SocketError);

  private:
	void menuFileConnections();
	void menuEditConnections();
	void menuServerConnections();
	void networkConnections();
	void requestsMethodsFilling();

	Ui::Window *ui;
	ConnectionDialog *cDialog;
	QTcpSocket *socket;
	bool isConnected;
	bool isAuthenticated;
	bool hasFile;
	Requests::AuthenticateRequest *self;
	QHash<QString, Requests::ARequest*> *requests;
	QHash<Requests::RequestType, std::function<void(const QJsonObject*)>> *requestsmethods;
	File *file;
  };
}
#endif // WINDOW_HPP
