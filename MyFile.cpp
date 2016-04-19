#include "MyFile.h"

 const char& MyFile::operator[](fstream::pos_type index)const throw (WorngIndexException) {
	char sign;
	fileValue->file->open(fileValue->name, fstream::in);
	fileValue->file->seekg(index, ios::beg);
	if (!fileValue->file->is_open())
	{
		cout << "cant open" << endl;
	}
	if (fileValue->file->eofbit)
		throw new WorngIndexException();
	char c = fileValue->file->peek();
	fileValue->file->close();
	return c;
}
MyFile& MyFile::operator =(const MyFile& rhs) {
	if (this == &rhs)
		return *this;
	if (--fileValue->refCount == 0) {
		delete fileValue;
	}
	if (fileValue->shareable) {
		fileValue = rhs.fileValue;
		this->fileValue->refCount++;
	}
	else
	{
		fileValue = new FileValue(rhs.fileValue->name);
	}
	return *this;
}
void MyFile::wc() {
	int countC = 0, countW = 0, countL = 0;
	fileValue->file->seekg(0, ios::beg);
	countL = count(std::istreambuf_iterator<char>(*fileValue->file), std::istreambuf_iterator<char>(), '\n');
	while (!fileValue->file->peek() == std::ifstream::traits_type::eof())
	{
		string word;
		*fileValue->file >> word;
		countC += word.length();
		countW++;
	}
	cout << "Number of chars in file are " << countC << endl;
	cout << "Number of words in file are " << countW << endl;
	cout << "Number of lines in file are " << countL << endl;
}

void MyFile::touch() {
	fileValue->file->open(fileValue->name,fstream::out);
	if (!fileValue->file->is_open())
	{
		cout << "cant open" << endl;
	}
	fileValue->file->flush();
	fileValue->file->close();
}
void MyFile::cat()
{
	fileValue->file->open(fileValue->name, fstream::in);
	if (!fileValue->file->is_open())
	{
		cout << "cant open" << endl;
	}
	fileValue->file->seekg(0, ios::beg);
	while (fileValue->file->peek() != std::ifstream::traits_type::eof())
	{
		cout << fileValue->file->tellg();
	}
	cout << endl;
	fileValue->file->close();
}

void MyFile::copy(MyFile & taget)
{
	while (this->fileValue->file->eof())  // Though perhaps this condition is wrong
	{
		taget.fileValue->file->put(this->fileValue->file->get());
	}

}

MyFile::MyFile( string name,FileValue * realPtr ):fileValue(new FileValue(realPtr->file, name))
{	
	realPtr->refCount++;

}
MyFile::MyFile(const MyFile & rhs) : name(rhs.name)
{
	if (rhs.fileValue->shareable) {
		fileValue = rhs.fileValue;
		this->fileValue->refCount++;
	}
	else
	{
		fileValue = new FileValue(rhs.name);
	}
}
