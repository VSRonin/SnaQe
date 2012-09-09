#include "snake.h"
#include "SelettoreImmagini.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Snake w;
	w.show();
	return a.exec();
}
