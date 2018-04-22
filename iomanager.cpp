#include "iomanager.h"

IOManager::IOManager()
{

}

bool IOManager::exists(string path){
    ifstream infile;
    infile.exceptions ( ifstream::failbit | ifstream::badbit );

    try{
        infile.open(path);
        infile.close();
        return true;
    }catch (const ifstream::failure& e) {
        return false;
    }
}

vector<string*> IOManager::readFile(string path)
{
    vector <string*> data;
    string str;
    ifstream infile;
    infile.exceptions ( ifstream::failbit | ifstream::badbit );

    try{
        infile.open(path);
        while(!infile.eof()){
            getline(infile, str);
            if(str.length()>0){
                data.push_back(IOManager::split(str, ';'));
            }
        }
        infile.close();
    }catch (const ifstream::failure& e) {

    }

    return data;
}

void IOManager::writeFile(string path, string file)
{
    ofstream outfile(path);
    outfile << file;
    outfile.close();
}


void IOManager::createFile(string path){
    ofstream{path};
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
