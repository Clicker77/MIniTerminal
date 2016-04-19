#pragma once
#include"MyFile.h"
class MyFolder
{
	string name;
	vector<MyFile> files;
	vector<MyFolder> folders;

public:

	MyFolder(string name = "V/");
	~MyFolder();
	string getName() { return name; }
	void setName(string name) { this->name = name; }
	void mkdir(string name);
	void rmdir(string name);
	void ls();
	void lproot();
	void pwd();
	void insertFile(MyFile& file);
	void readFromFile(string name, unsigned int index);
	void writeToFile(string name, unsigned int index, char c);
	MyFolder* PutCurrFolder(string name);
	MyFile* findFile(string name);
	void addFile(string name);
	void removeFile(string name);

};

