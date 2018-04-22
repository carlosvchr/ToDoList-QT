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
    static void createFile(string path);
    static void writeFile(string path, string);
    static string* split(string l, char regex);
    static bool exists(string path);
};


#endif // IOMANAGER_H
