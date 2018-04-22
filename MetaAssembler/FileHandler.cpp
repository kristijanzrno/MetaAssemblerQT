#include "FileHandler.h"
#include <sstream>
#include <fstream>
#include <QtWidgets/qfiledialog.h>

using namespace std;

QWidget *parent;

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(QWidget *parent)
{
	//This class is used to handle files
	//All file handling from any part of the program will be processed through this class
	mainWindow = parent;
}

string FileHandler::openFile(string name)
{
	//Opening file and returning a file data string if it's successfully opened
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
	//Saving given data string to a file with given name string
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

string FileHandler::fileRead(string name)
{
	//Reading file contents to a string
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


