#pragma once
#include <QtWidgets/QMainWindow>
#include <string>

class FileHandler {
public:
	FileHandler();
	FileHandler(QWidget *parent);
	std::string openFile(std::string name);
	bool saveFile(std::string name, std::string data);
private:
	QWidget *mainWindow;
	std::string fileRead(std::string name);
	bool fileWrite(std::string name, std::string data);
};