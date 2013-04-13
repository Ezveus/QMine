#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>

namespace Ui {
	class Window;
}

namespace QMine {
	class Window : public QMainWindow {
	Q_OBJECT
	
	public:
		explicit Window(QWidget *parent = 0);
		~Window();
	
	private:
		void menuFileConnections();
		void menuEditConnections();
		void menuServerConnections();

		Ui::Window *ui;
	};
}
#endif // WINDOW_HPP
