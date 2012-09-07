#include "snake.h"
#include "SelettoreImmagini.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Snake w;
	SelettoreImmagini w;
	w.show();
	return a.exec();
}
