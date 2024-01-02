#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include<iostream>
#include<vector>
#include<iomanip>
#include <string>
#include<map>
#include<fstream>
#include<cctype>
#include <regex>


using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::isalnum;
using std::isdigit;
using std::isalpha;
using std::regex;

struct zodziuinfo{
    int pasikartojimai=0;
    vector<int> indeksai;
};


void Skaitymas(map<string,zodziuinfo> &zodziai,std::stringstream &buf,vector<string> &saitai);
void Rasymas(map<string,zodziuinfo> &zodziai,vector<string> &saitai,std::sregex_iterator &it,std::sregex_iterator &end);
bool urlcheck(string zodis);
bool saito_idejimas(vector<string> &saitai,string &zodis);
bool ifremove(string &zodis,int &i);
#endif
