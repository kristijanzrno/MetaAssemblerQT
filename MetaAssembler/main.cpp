#include "MetaAssembler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	//Run the MetaAssembler QT application
	QApplication a(argc, argv);
	MetaAssembler w;
	w.show();
	return a.exec();
}
