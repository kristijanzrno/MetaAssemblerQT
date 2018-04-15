#include "MetaAssembler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MetaAssembler w;
	w.show();
	return a.exec();
}
