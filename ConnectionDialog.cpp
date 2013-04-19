#include "ConnectionDialog.hpp"
#include "ui_ConnectionDialog.h"

QMine::ConnectionDialog::ConnectionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectionDialog) {
  ui->setupUi(this);

  connections();
}

QMine::ConnectionDialog& QMine::ConnectionDialog::operator=(ConnectionDialog const& cd) {
  ui = cd.ui;

  connections();
  return *this;
}

QMine::ConnectionDialog *QMine::ConnectionDialog::operator=(ConnectionDialog const* cd) {
  ui = cd->ui;

  connections();
  return this;
}

QMine::ConnectionDialog::~ConnectionDialog() {
  delete ui;
}

void QMine::ConnectionDialog::connections() {
  connect(ui->connectBt, &QPushButton::clicked, [=]() {
      emit validated(ui->hostname->text(), ui->port->value());
      this->close();
    });
  connect(ui->cancelBt, &QPushButton::clicked, [=]() {
      this->close();
    });
}
