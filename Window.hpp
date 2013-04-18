#include <QMainWindow>
#include <QTcpSocket>
#include <requests/AuthenticateRequest.hpp>
#include "ConnectionDialog.hpp"

#ifndef WINDOW_HPP
#define WINDOW_HPP

namespace Ui {
	class Window;
}

namespace QMine {
	class Window : public QMainWindow {
		Q_OBJECT

	public:
		explicit Window(QWidget *parent = 0);
		~Window();
		void authenticate();

	public slots:
		void dataReceived();
		void errorReceived(QAbstractSocket::SocketError);

	private:
		void menuFileConnections();
		void menuEditConnections();
		void menuServerConnections();
		void networkConnections();

		Ui::Window *ui;
		ConnectionDialog *cDialog;
		QTcpSocket *socket;
		bool isConnected;
		bool isAuthenticated;
		bool hasFile;
		Requests::AuthenticateRequest *self;
		QHash<QString, Requests::IRequest*> *requests;
	};
}
#endif // WINDOW_HPP
