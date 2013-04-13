#include <QMessageBox>
#include "Window.hpp"
#include "ui_Window.h"

QMine::Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window) {
	ui->setupUi(this);

	menuFileConnections();
	menuEditConnections();
	menuServerConnections();
}

QMine::Window::~Window() {
	delete ui;
}

void QMine::Window::menuFileConnections() {
	connect(ui->actionFindFile, &QAction::triggered, [=]() {
		QMessageBox::information(this, "QMine", "Find file !!!");
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
		this->close();
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
		QMessageBox::information(this, "QMine", "Authenticate !!!");
	});
	connect(ui->actionSignup, &QAction::triggered, [=]() {
		QMessageBox::information(this, "QMine", "Signup !!!");
	});
}
