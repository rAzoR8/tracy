#include "Tracy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Tracy w;
	w.show();
	return a.exec();
}
