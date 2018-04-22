#pragma once
#include <QtWidgets/QMainWindow>
#include <string>
using namespace std;

class FileHandler {
public:
	FileHandler();
	FileHandler(QWidget* parent);
	string openFile(string name);
	bool saveFile(string name, string data);
private:
	QWidget * mainWindow;
	string fileRead(string name);
};