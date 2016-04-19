#pragma once

#include <fstream>
#include <string>
#include<iostream>
#include <sstream>
#include<algorithm>
#include<vector>
#include <ctime>
#include <windows.h>
#define nullptr NULL
using namespace std;
static int counter = 0;

class WorngIndexException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Wrong index happened";
	}
};
class MyFile {
	struct  FileValue
	{
		int refCount;
		bool shareable;
		string name;
		fstream *file;
		FileValue(fstream* file, string name) :name(name), refCount(1), shareable(true) {
			this->file = file;
		}
		FileValue(string name) :refCount(1), shareable(true) {
			string realName = to_string(++counter) + ".txt";
			this->name = realName;
			this->file = new fstream();
			this->file->open(realName, fstream::out | fstream::in|fstream::beg);
			this->file->close();
		}
		~FileValue() {
			if (--refCount == 0) {
				file->close();
				delete file;
				file = nullptr;
			}

		}
	};
public:
	class CharProxy {
	public:
		CharProxy(fstream &file, fstream::pos_type pos, string name) :file_(file), pos_(pos), name(name) {
			file_.open(name, fstream::out|fstream::beg);
			if (!file_.is_open())
			{
				cout << "cant open" << endl;
			}
		}
		CharProxy& operator=(char c) {
			file_.seekp(pos_);
			file_.put(c);
			return *this;
		}
		operator char() {
			file_.seekg(pos_);
			char c = file_.peek();
			file_.close();
			return c;
		}
	private:
		string name;
		fstream& file_;
		fstream::pos_type pos_;
	};

	FileValue* fileValue;
	string name;
	MyFile(string fileName) :name(fileName) {
		fileValue = new FileValue(fileName);

	};
	MyFile(string name, FileValue* realPtr);
	MyFile(const MyFile& rhs);
	MyFile& operator=(const MyFile& rhs);
	virtual ~MyFile() { if (--fileValue->refCount == 0) delete fileValue; }
	string getName() { return name; }
	int getRefCount() { return this->fileValue->refCount; }
	const char& operator[](fstream::pos_type index)const throw (WorngIndexException);
	CharProxy operator[](fstream::pos_type i) {
		return CharProxy(*fileValue->file, i, fileValue->name);
	}
	fstream* operator->() const { return fileValue->file; }
	fstream& operator*() const { return *fileValue->file; }
	void wc();
	void touch();
	void cat();
	void copy(MyFile& taget);
};
