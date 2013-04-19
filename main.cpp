#include "Window.hpp"
#include <QApplication>

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  QMine::Window w;
  w.show();
	
  return a.exec();
}
