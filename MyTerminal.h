#pragma once
#include"MyFile.h"
#include "MyFolder.h"
class MyTerminal
{
	MyFolder rootFolder;
	MyFolder* currFolder;
	void getCommand();
	void printManual();
	void read(string name, int pos);
	void write(string name, int pos, char c);
	void touch(string name);
	void copy(string sourceName, string targetName);
	void remove(string name);
	void move(string sourceName, string targetName);
	void cat(string name);
	void wc(string fileName);
	void ln(string sourceName, string targetName);
	void mkdir(string folderName);
	void chdir(string folderName);
	void rmdir(string folderName);
	void ls(string folderName);
	void lproot();
	void pwd();

public:
	MyTerminal() {currFolder = &rootFolder;};
	virtual ~MyTerminal() {};
	void start() {printManual();	getCommand();}
};

