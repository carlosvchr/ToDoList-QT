#include "iomanager.h"

IOManager::IOManager()
{

}


vector<string*> IOManager::readFile(string path)
{
    vector <string*> data;

    string *s = new string[4];
    s[0] = "hola";
    s[1] = "hasdas";
    s[2] = "100";
    s[3] = "huaskjhdah8a";
    data.push_back(s);
    string *s2 = new string[4];
    s2[0] = "ALLLL";
    s2[1] = "hacsdcs";
    s2[2] = "80";
    s2[3] = "MUAJAJA";
    data.push_back(s2);



    string str;
    ifstream infile;
    infile.open(path);
    while(!infile.eof()){
        getline(infile, str);
    }
    infile.close();

    return data;
}
