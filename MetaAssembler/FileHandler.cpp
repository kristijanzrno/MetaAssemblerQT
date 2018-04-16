#include "FileHandler.h"
#include <QtWidgets/qfiledialog.h>
#include <sstream>
#include <fstream>
using namespace std;

QWidget *parent;

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(QWidget *parent)
{
	mainWindow = parent;
}

string FileHandler::openFile(string name)
{
	string content;
	if (name == "") {
		QString filename = QFileDialog::getOpenFileName(mainWindow, QFileDialog::tr("Open File"), "", QFileDialog::tr("MetaAssembler Project (*.MASP);;Text file (*.txt)"));
		if (filename != "" && filename != NULL)
		{
			content = fileRead(filename.toUtf8().constData());
		}
	}
	else {
		content = fileRead(name);
	}
	return content;
}

bool FileHandler::saveFile(string name, string data)
{
	if (name == "") {
		QString filename = QFileDialog::getSaveFileName(mainWindow, QFileDialog::tr("Save File"), "", QFileDialog::tr("Cedar Memory file (*.cdm);;MetaAssembler Project (*.MASP);;Text file (*.txt)"));
	}
	else {
		fileWrite(name, data);
	}
	return false;
}

string FileHandler::fileRead(string name)
{
	string content;
	ifstream readFile;
	readFile.open(name);
	if (readFile.is_open())
	{
		stringstream stream;
		stream << readFile.rdbuf();
		content = stream.str();
		readFile.close();
	}
	return content;

}

bool FileHandler::fileWrite(string name, string data)
{
	ofstream saveFile;
	saveFile.open(name);
	if (saveFile.is_open()) {
		if (saveFile << data) {
			saveFile.close();
			return true;
		}
		saveFile.close();
	}
	return false;
}
