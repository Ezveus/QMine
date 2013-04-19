#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFileDialog>
#include "Window.hpp"
#include "ui_Window.h"
#include "requests/LoadRequest.hpp"
#include "requests/FileUploader.hpp"

QMine::Window::Window(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Window) {
  socket = new QTcpSocket(this);
  cDialog = new ConnectionDialog(this);
  isConnected = false;
  isAuthenticated = false;
  hasFile = false;
  self = nullptr;
  requests = new QHash<QString, Requests::ARequest*>();
  requestsmethods = new QHash<Requests::RequestType, std::function<void()>>();

  ui->setupUi(this);

  menuFileConnections();
  menuEditConnections();
  menuServerConnections();
  networkConnections();
  requestsMethodsFilling();
}

QMine::Window::~Window() {
  if (self != nullptr)
	delete self;
  delete requests;
  delete requestsmethods;
  delete socket;
  delete cDialog;
  delete ui;
}

void QMine::Window::menuFileConnections() {
  connect(ui->actionFindFile, &QAction::triggered, [=]() {
	if (isConnected && isAuthenticated && !hasFile) {
	  QString pass = QFileDialog::getOpenFileName(this, "Find local file", QDir::homePath());
	  if (pass != "") {
		Requests::LoadRequest *fr = new Requests::LoadRequest(pass, Requests::LoadRequest::Up);
		fr->startUpload();
		requests->insert(fr->getId(), fr);
		socket->write(fr->toByteArray());
	  } else if (!isConnected) {
		ui->statusLabel->setText("Disconnected");
	  } else if (!isAuthenticated) {
		ui->statusLabel->setText("Not authenticated");
	  } else if (hasFile) {
		ui->statusLabel->setText("Kill file before open a new one");
	  }
	}
  });
  connect(ui->actionFindFileOnServer, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Find file on Server !!!");
  });
  connect(ui->actionSaveFile, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Save file !!!");
  });
  connect(ui->actionSaveFileAs, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Save file as !!!");
  });
  connect(ui->actionSaveFileOnServer, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Save file on Server !!!");
  });
  connect(ui->actionSaveFileOnServerAs, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Save file on Server as !!!");
  });
  connect(ui->actionKillBuffer, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Kill buffer !!!");
  });
  connect(ui->actionQuit, &QAction::triggered, [=]() {
	if (isConnected) {
	  socket->abort();
	  socket->close();
	}
	hasFile = false; // TODO : Close the file if hasFile is true
	isAuthenticated = false;
	isConnected = false;
	qApp->quit();
  });
}

void QMine::Window::menuEditConnections() {
  connect(ui->actionOverwriteMode, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Overwrite Mode");
  });
  connect(ui->actionUndoRedo, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Undo Redo !!!");
  });
  connect(ui->actionKillLine, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Kill line !!!");
  });
  connect(ui->actionYank, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Yank !!!");
  });
  connect(ui->actionYankPop, &QAction::triggered, [=]() {
	QMessageBox::information(this, "QMine", "Yank pop !!!");
  });
}

void QMine::Window::menuServerConnections() {
  connect(ui->actionAuthenticate, &QAction::triggered, [=]() {
	if (isConnected && !isAuthenticated) {
	  self = new Requests::AuthenticateRequest("root", "toor");
	  socket->write(self->toString());
	  requests->insert(self->getId(), self);
	} else if (!isConnected) {
	  ui->statusLabel->setText("Disconnected");
	} else if (isAuthenticated) {
	  ui->statusLabel->setText("Already authenticated");
	}
  });
  /*
   * TODO : Implement the signup
   * connect(ui->actionSignup, &QAction::triggered, [=]() {
   * QMessageBox::information(this, "QMine", "Signup isn't implemented for now");
   * });
   *
   */
  connect(ui->actionConnect, &QAction::triggered, [=](){
	if (!isConnected)
	  cDialog->show();
	else
	  ui->statusLabel->setText("Already connected");
  });
  connect(cDialog, &ConnectionDialog::validated, [=](QString hostname, int port) {
	if (!isConnected) {
	  socket->abort();
	  socket->connectToHost(hostname, port);
	}
  });
}

void QMine::Window::dataReceived() {
  char data[MAX_RQST_SZ] = "";

  socket->read(data, MAX_RQST_SZ);
  QString rep(data);
  QStringList tokens = rep.split('=');
  QString rqst = tokens.at(0);
  QString json = tokens.at(1);

  if (rqst == "RESPONSE") {
	ui->statusLabel->setText(QString("Received RESPONSE : ") + json);
	QJsonParseError jsonerror = QJsonParseError();
	QJsonDocument jsondoc = QJsonDocument::fromJson(json.toLatin1(), &jsonerror);
	if (jsonerror.error != QJsonParseError::NoError) {
	  // TODO : what is the error ?
	  return ;
	} else if (!jsondoc.isObject()) {
	  return ;
	}
	QJsonObject o = jsondoc.object();
	QString id = o["id"].toString();
	Requests::ARequest *rqst = requests->value(id);
	rqst->response(&o, requestsmethods->value(rqst->getType()));
  } else if (rqst == "SYNC") {
	ui->statusLabel->setText(QString("Received SYNC : ") + json);
  } else if (rqst == "QUIT") {
	socket->abort();
	hasFile = false; // TODO : Close the file if hasFile is true
	isAuthenticated = false;
	isConnected = false;
	ui->statusLabel->setText("Disconnected");
  }
}

void QMine::Window::errorReceived(QAbstractSocket::SocketError e) {
  switch (e) {
  case QAbstractSocket::HostNotFoundError:
	QMessageBox::critical(this, "QMine", "Host not found");
	break;
  default:
	QMessageBox::critical(this, "QMine", "Error occured");
  }
}

void QMine::Window::networkConnections(){
  connect(socket, &QTcpSocket::connected, [=]() {
	isConnected = true;
	ui->statusLabel->setText("Connected");
  });
  connect(socket, &QTcpSocket::disconnected, [=]() {
	hasFile = false;
	isAuthenticated = false;
	isConnected = false;
	ui->statusLabel->setText("Disconnected");
  });
  connect(socket, &QTcpSocket::readyRead, this, &QMine::Window::dataReceived);
  connect(socket, SIGNAL(error), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
}

void QMine::Window::requestsMethodsFilling() {
  requestsmethods->insert(Requests::Authenticate, [&]() {
	isAuthenticated = true;
	ui->statusLabel->setText("Authenticated");
  });
  requestsmethods->insert(Requests::Load, [&]() {
	ui->fileName->setText("Plop");
	hasFile = true;
	ui->plainTextEdit->setPlainText("Here should be some (usefull) text");
  });
}
