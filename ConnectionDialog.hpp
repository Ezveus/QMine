#ifndef CONNECTIONDIALOG_HPP
#define CONNECTIONDIALOG_HPP

#include <QDialog>
#include <QPair>

namespace Ui {
  class ConnectionDialog;
}

namespace QMine {
  /*
   ** This class allows the user to select his server
   ** Default is localhost:8080
   */
  class ConnectionDialog : public QDialog {
	Q_OBJECT

  public:
	explicit ConnectionDialog(QWidget *parent = 0);
	ConnectionDialog& operator=(ConnectionDialog const&);
	ConnectionDialog* operator=(ConnectionDialog const*);
	~ConnectionDialog();

  signals:
	void validated(QString hostname, int port);

  private:
	ConnectionDialog(ConnectionDialog const&);
	void connections();

	Ui::ConnectionDialog *ui;
  };
}

#endif // CONNECTIONDIALOG_HPP
