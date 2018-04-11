#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class IOManager
{
public:
    IOManager();
    static vector<string*> readFile(string path);

private:
    static string* split(string l, char regex);
};

#endif // IOMANAGER_H
