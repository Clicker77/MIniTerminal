#include "MyTerminal.h"

string SplitLastFoldername(const string& str) {
	unsigned int index = str.find_last_of("/", str.length() - 2);
	return str.substr(0, index + 1);
}
void MyTerminal::read(string name, int pos)
{
	string pathSource = SplitLastFoldername(name);
	currFolder = rootFolder.PutCurrFolder(pathSource);
	if (!currFolder) {
		cout << "The source folder  not exist" << endl;
		return;
	}
	MyFile* sourceFile = currFolder->findFile(name);
	if (!sourceFile) {
		cout << "The source file  not exist" << endl;
		return;
	}
	cout << &sourceFile[pos] << endl;
}
void MyTerminal::write(string name, int pos, char c)
{
	string path = SplitLastFoldername(name);
	currFolder = rootFolder.PutCurrFolder(path);
	if (currFolder) {
		currFolder->writeToFile(name, pos, c);
	}
	else {
		cout << "The folder not exist" << endl;
	}

}
void MyTerminal::copy(string sourceName, string targetName)
{
	string pathSource = SplitLastFoldername(sourceName);
	currFolder = rootFolder.PutCurrFolder(pathSource);
	if (!currFolder) {
		cout << "The source folder  not exist" << endl;
		return;
	}
	string pathTarget = SplitLastFoldername(targetName);
	MyFolder* targetFolder = rootFolder.PutCurrFolder(pathTarget);
	if (!targetFolder) {
		cout << "The target folder  not exist" << endl;
		return;
	}
	MyFile* sourceFile = currFolder->findFile(sourceName);
	if (!sourceFile) {
		cout << "The source file  not exist" << endl;
		return;
	}
	else {
		MyFile* targetFile = currFolder->findFile(targetName);
		if (targetFile) {
			targetFile->copy(*sourceFile);
		}
		else {
			targetFolder->addFile(targetName);
			sourceFile = currFolder->findFile(sourceName);
			targetFile = currFolder->findFile(targetName);
			sourceFile->copy(*targetFile);
		}
	}
}
void MyTerminal::remove(string name)
{
	string path = SplitLastFoldername(name);
	currFolder = rootFolder.PutCurrFolder(path);
	if (!currFolder) {
		cout << "The Folder not exist" << endl;
		return;
	}
	else {
		currFolder->removeFile(name);
	}
}
void MyTerminal::move(string sourceName, string targetName)
{
	string pathSource = SplitLastFoldername(sourceName);
	currFolder = rootFolder.PutCurrFolder(pathSource);
	if (!currFolder) {
		cout << "The source folder  not exist" << endl;
		return;
	}
	string pathTarget = SplitLastFoldername(targetName);
	MyFolder* targetFolder = rootFolder.PutCurrFolder(pathTarget);
	if (!targetFolder) {
		cout << "The target folder  not exist" << endl;
		return;
	}
	MyFile* sourceFile = currFolder->findFile(sourceName);
	if (!sourceFile) {
		cout << "The source file  not exist" << endl;
		return;
	}
	else {
		MyFile* targetFile = currFolder->findFile(targetName);
		if (targetFile) {
			cout << "The target file are exist already" << endl;
		}
		else {
			targetFolder->addFile(targetName);
			targetFile = currFolder->findFile(targetName);
			targetFile->copy(*sourceFile);
			currFolder->removeFile(sourceName);
		}
	}
}
void MyTerminal::touch(string name)
{
	string path = SplitLastFoldername(name);
	currFolder = rootFolder.PutCurrFolder(path);
	if (!currFolder) {
		cout << "The Folder not exist" << endl;
		return;
	}
	MyFile* currFile = currFolder->findFile(name);
	if (currFile)
	{
		currFile->touch();
	}
	else
	{
		currFolder->addFile(name);
		currFile = currFolder->findFile(name);
		currFile->touch();
	}

}
void MyTerminal::cat(string name)
{
	string path = SplitLastFoldername(name);
	currFolder = rootFolder.PutCurrFolder(path);
	if (!currFolder) {
		cout << "The folder not exist" << endl;
		return;
	}
	MyFile* currFile = currFolder->findFile(name);
	if (currFile) {
		currFile->cat();
	}
	else
	{
		cout << "The file not exist" << endl;
	}
}
void MyTerminal::wc(string fileName)
{
	string path = SplitLastFoldername(fileName);
	currFolder = rootFolder.PutCurrFolder(path);
	if (!currFolder) {
		cout << "The folder not exist" << endl;
		return;
	}
	MyFile* currFile = currFolder->findFile(fileName);
	if (currFile) {
		currFile->wc();
	}
	else
	{
		cout << "The file not exist" << endl;
	}
}
void MyTerminal::ln(string sourceName, string targetName)
{
	string pathSource = SplitLastFoldername(sourceName);
	currFolder = rootFolder.PutCurrFolder(pathSource);
	if (!currFolder) {
		cout << "The source folder  not exist" << endl;
		return;
	}
	string pathTarget = SplitLastFoldername(targetName);
	MyFolder* targetFolder = rootFolder.PutCurrFolder(pathTarget);
	if (!targetFolder) {
		cout << "The target folder  not exist" << endl;
		return;
	}
	MyFile* sourceFile = currFolder->findFile(sourceName);
	if (!sourceFile) {
		cout << "The source file  not exist" << endl;
		return;
	}
	MyFile* targetFile = currFolder->findFile(targetName);

	if (targetFile)
	{
		cout << "The target file already exist" << endl;
	}
	else
	{
		targetFile = new MyFile(targetName, sourceFile->fileValue);
		targetFolder->insertFile(*targetFile);

	}
}
void MyTerminal::mkdir(string folderName)
{
	if (folderName[folderName.length() - 1] == '/') {
		string path = SplitLastFoldername(folderName);
		currFolder = rootFolder.PutCurrFolder(path);
		if (currFolder) {
			currFolder->mkdir(folderName);
		}
		else
		{
			cout << "Your Path was not found" << endl;
		}
	}
	else
	{
		cout << "Your Path was is not legal" << endl;
	}
}
void MyTerminal::chdir(string folderName)
{
	currFolder = rootFolder.PutCurrFolder(folderName);
	if (!currFolder) {
		cout << "there is not folder like u give" << endl;
	}
}
void MyTerminal::rmdir(string folderName)
{
	string path = SplitLastFoldername(folderName);
	currFolder = rootFolder.PutCurrFolder(path);
	if (currFolder) {
		currFolder->rmdir(folderName);
	}
	else {
		cout << "Folder not exist" << endl;
	}
}
void MyTerminal::ls(string folderName)
{
	currFolder = rootFolder.PutCurrFolder(folderName);
	if (currFolder) {
		currFolder->ls();
	}
	else
	{
		cout << "Folder not exist" << endl;
	}
}
void MyTerminal::lproot()
{
	rootFolder.lproot();
}
void MyTerminal::pwd()
{
	currFolder->pwd();
}
void MyTerminal::getCommand()
{
	currFolder = &rootFolder;
	while (true)
	{
		string allcommand, command, arg1, arg2, arg3, arg4;
		getline(cin, allcommand);
		istringstream iss(allcommand);
		iss >> command;
		for (unsigned int i = 0; i < command.length(); i++)
			command[i] = tolower(command[i]);
		/*switch case by if &else*/
		if (command == "") {
			cout << "There is no command" << endl;
		}
		else {
			iss >> arg1;
			if (arg1 != "") {
				iss >> arg2;
				if (arg2 != "") {
					iss >> arg3;
					if (arg3 != "") {
						iss >> arg4;
						if (arg4 != "") {
							cout << "Too many args" << endl;
						}
						else {/*all the command with 3 args*/
							if (command == "write")
							{
								try {
									write(arg1, atoi(arg2.c_str()), arg3[0]);
								} catch (WorngIndexException & e) {
									cout << e.what();
								}

							}
							else {
								cout << "Wrong command" << endl;
							}

						}
					}
					else {
						if (command == "read") {
							try {
								read(arg1, atoi(arg1.c_str()));

							} catch (WorngIndexException & e) {
							cout << e.what();
							continue;
							}
						}
						else if (command == "copy") {
							copy(arg1, arg2);

						}
						else if (command == "move") {
							move(arg1, arg2);

						}
						else if (command == "ln") {
							ln(arg1, arg2);

						}
						else {
							cout << "Wrong command" << endl;
						}
					}
				}
				else /*all the commands with 1 args*/
				{
					if (command == "touch")
					{
						touch(arg1);
					}
					else if (command == "remove")
					{
						remove(arg1);
					}
					else if (command == "cat")
					{
						cat(arg1);
					}
					else if (command == "wc")
					{
						wc(arg1);
					}
					else if (command == "mkdir")
					{
						mkdir(arg1);
					}
					else if (command == "chdir")
					{
						chdir(arg1);
					}
					else if (command == "rmdir")
					{
						rmdir(arg1);
					}
					else if (command == "ls")
					{
						ls(arg1);
					}
					else {
						cout << "Wrong command" << endl;
					}
				}
			}
			else /*all the command with 0 args*/
			{
				if (command == "lproot")
				{
					lproot();
				}
				else if (command == "ls")
				{
					currFolder->ls();
				}
				else if (command == "pwd")
				{
					pwd();
				}
				else if (command == "exit")
				{
					cout << "Thanks for using my terminal" << endl;
					return;
				}
				else {
					cout << "Wrong command" << endl;
				}
			}
		}
	}
}
void MyTerminal::printManual()
{
	cout << "[1]\tread FILENAME POSITION" << endl;
	cout << "[2]\twrite FILENAME POSITION CHARACTER" << endl;
	cout << "[3]\ttouch FILENAME" << endl;
	cout << "[4]\tcopy SOURCE_FILENAME TARGET_FILENAME" << endl;
	cout << "[5]\tremove FILENAME" << endl;
	cout << "[6]\tmove SOURCE_FILENAME TARGET_FILENAME" << endl;
	cout << "[7]\tcat FILENAME" << endl;
	cout << "[8]\twc FILENAME" << endl;
	cout << "[9]\tln TARGET_FILENAME LINK_NAME" << endl;
	cout << "[10]\tmkdir FOLDERNAME" << endl;
	cout << "[11]\tchdir FOLDERNAME" << endl;
	cout << "[12]\trmdir FOLDERNAME" << endl;
	cout << "[13]\tls FOLDERNAME" << endl;
	cout << "[14]\tlproot" << endl;
	cout << "[15]\tpwd" << endl;
	cout << "[16]\texit" << endl;
}

