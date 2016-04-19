#include "MyFolder.h"

MyFolder::MyFolder(string name ) : name(name)
{
}
MyFolder::~MyFolder()
{
}
void MyFolder::mkdir(string name)
{
	vector<MyFolder>::iterator itFolder = folders.begin();
	for (; itFolder < folders.end(); itFolder++)
		if (itFolder->getName() == name)
		{
			cout << "This folder exist" << endl;
			return;
		}
	folders.push_back(MyFolder(name));
	return;
}
void MyFolder::rmdir(string name)
{
	vector<MyFolder>::iterator itFolder = folders.begin();
	for (; itFolder < folders.end(); itFolder++)
		if (itFolder->getName() == name) {
			folders.erase(itFolder);
			return;
		}
	cout << "The folder not exist" << endl;
}
void MyFolder::ls()
{
	vector<MyFolder>::iterator itFolder = folders.begin();
	vector<MyFile>::iterator itFiles = files.begin();
	cout << "Folders:" << endl;
	for (; itFolder < folders.end(); itFolder++)
		cout << itFolder->getName() << endl;
	cout << "Files:" << endl;
	for (; itFiles < files.end(); itFiles++)
		cout << itFiles->getName() << " "<< itFiles->getRefCount() << endl;
}
void MyFolder::lproot()
{
	vector<MyFolder>::iterator itFolder = folders.begin();
	vector<MyFile>::iterator itFiles = files.begin();
	cout << name << endl;
	for (; itFolder < folders.end(); itFolder++)
	{
		itFolder->lproot();
	}
	for (; itFiles < files.end(); itFiles++)
	{ 
		cout  << itFiles->getName()<<" " <<itFiles->getRefCount() << endl;
	}
}
void MyFolder::pwd()
{
	cout << name << endl;
}
void MyFolder::insertFile(MyFile & file)
{
	files.push_back(file);
}
//get cursor on a folder inside this folder by Name
MyFolder* MyFolder::PutCurrFolder(string name)
{
	if (this->getName() == name) {
		return this;
	}
	vector<MyFolder>::iterator itFolder = folders.begin();
	for (; itFolder < folders.end(); itFolder++)
	{
		if (itFolder->PutCurrFolder(name))
			return itFolder->PutCurrFolder(name);

	}
	return nullptr;
}
MyFile * MyFolder::findFile(string name)
{
	vector<MyFile>::iterator itFiles = files.begin();
	for (; itFiles < files.end(); itFiles++)
	{
		if (itFiles->getName() == name)
		{
			return &(*itFiles);
		}
	}
	return nullptr;
}
void MyFolder::addFile(string name)
{
	if(this->findFile(name))
		cout << "This file already exist" << endl;
	files.push_back(MyFile(name));
}
void MyFolder::removeFile(string name)
{
	vector<MyFile>::iterator itFiles = files.begin();
	for (; itFiles < files.end(); itFiles++)
	{
		if (itFiles->getName() == name)
		{
			files.erase(itFiles);
			return;
		}
	}
	cout << "The file not exist" << endl;
}
void MyFolder::readFromFile(string name, unsigned int index)
{
	vector<MyFile>::iterator itFiles = files.begin();
	for (; itFiles < files.end(); itFiles++)
	{
		if (itFiles->getName() == name)
		{
			cout << itFiles->operator[](index) << endl;
			return;
		}
	}
	cout << "The file not exist" << endl;
}
void MyFolder::writeToFile(string name, unsigned int index, char c)
{
	vector<MyFile>::iterator itFiles = files.begin();
	for (; itFiles < files.end(); itFiles++)
	{
		if (itFiles->getName() == name)
		{
			itFiles->operator[](index) = c;
			return;
		}
	}
	cout << "The file not exist" << endl;
}
