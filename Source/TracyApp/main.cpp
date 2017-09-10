#include "TracyApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TracyApp w;
	w.show();
	return a.exec();
}
