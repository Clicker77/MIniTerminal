#include "MyTerminal.h"

int main() {

	//MyTerminal ter = MyTerminal();
	//ter.start();
	MyFile f("a");
	f[6] = 'c';
	f[1] = 'a';
	f[5] = 'r';
	f.cat();

	char c;
	cin >> c;
	//fstream* file = new fstream();
	//file->open("alex.txt",fstream::in|fstream::out);
	////file->open(name.data(), fstream::in | fstream::out);
	//if (file->is_open())
	//{
	//	cout << "open";
	//}

}
