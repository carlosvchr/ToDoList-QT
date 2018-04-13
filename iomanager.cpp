#include "iomanager.h"

IOManager::IOManager()
{

}


vector<string*> IOManager::readFile(string path)
{
    vector <string*> data;
    string str;
    ifstream infile;
    infile.open(path);
    while(!infile.eof()){
        getline(infile, str);
        if(str.length()>0){
            data.push_back(IOManager::split(str, ';'));
        }
    }
    infile.close();

    return data;
}

void IOManager::writeFile(string path, string file)
{
    ofstream outfile(path);
    outfile << file;
    outfile.close();
}


string* IOManager::split(string l, char regex)
{
    vector<string> vect;
    stringstream ss(l);
    string token;

    while (getline(ss,token, regex))
    {
        vect.push_back(token);
    }

    unsigned int i;
    string *r = new string[vect.size()];
    for(i=0; i<vect.size(); i++){
        r[i] = vect.at(i);
    }

    return r;
}
