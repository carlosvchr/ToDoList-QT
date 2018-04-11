#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IOManager
{
public:
    IOManager();
    static vector<string*> readFile(string path);

};

#endif // IOMANAGER_H
