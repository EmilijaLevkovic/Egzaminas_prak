#include "lib.h"


void Skaitymas(map<string,zodziuinfo> &zodziai,std::stringstream &buf,vector<string> &saitai){
    string zodis,zodis2;
    int indeksas=0;

    while(!buf.eof()){
        buf>>zodis;
        vector<int> to_remove;
        if(zodis==" "&&zodis==""){
            zodis.clear();
            buf>>zodis;
        }
        transform(zodis.begin(), zodis.end(), zodis.begin(), ::tolower);

        for(int i=0;i<zodis.length();i++){
            if(ifremove(zodis,i)){
                to_remove.push_back(i);
            }
        }
        int change=0;
        for(auto &i:to_remove){
            zodis.erase(i-change,1);
            change++;
        }
        if(zodziai.count(zodis)==0){
            zodziuinfo temp;
            temp.indeksai.push_back(indeksas);
            temp.pasikartojimai++;
            zodziai.insert(std::pair<string,zodziuinfo>(zodis,temp));
        }
        else{
            auto it=zodziai.find(zodis);
            it->second.pasikartojimai++;
            it->second.indeksai.push_back(indeksas);
        }
        zodis.clear();
        to_remove.clear();
        indeksas++;
    }
    zodziai.erase("");
}

bool ifremove(string &zodis,int &i){

    if((!isalnum(zodis[i])&&!isalnum(zodis[i+1]))) return true;
    if((!isalnum(zodis[i-1])&&!isalnum(zodis[i])))return true;
    if((zodis[i]=='(')||(zodis[i]==')'))return true;
    if((!isalpha(zodis[i])&&!isalpha(zodis[i+1]))||(!isalpha(zodis[i])&&!isalpha(zodis[i-1])))return true;
    return false;
}

void Rasymas(map<string,zodziuinfo> &zodziai,vector<string> &saitai,std::sregex_iterator &it,std::sregex_iterator &end){
    ofstream fout("o.txt");
    for(auto &it:zodziai){
        fout<<it.first<<" "<<it.second.pasikartojimai<<endl;
    }
    fout<<"\nSaitai: \n\n";
    for(;it!=end;it++){
        fout<<it->str()<<endl;
    }
    ofstream fout2("table.txt");
    fout2<<"Zodziu indeksai: \n";
    for(auto &it:zodziai){
        if(it.second.indeksai.size()>1){
            // cout<<it.second.indeksai.size()<<"\n";
            fout2<<it.first<<": ";
            for(int i=0;i<it.second.indeksai.size();i++){
                fout2<<it.second.indeksai.at(i);
                if(i!=it.second.indeksai.size()-1)fout2<<" ";
                else fout2<<",";
            }
            fout2<<endl;
        }
    }
}


int main(){
    map<string,zodziuinfo> zodziai;
    vector<string> saitai;
    ifstream fin;
    string failas;
    cout<<"Iveskite failo pavadinima: \n";
    cin>>failas;
      try{
        fin.open(failas);
        if(!fin){
          throw std::runtime_error("Failo nera.");
        }
        cout<<"Failas atidarytas."<<endl;
      }
      catch(const std::exception &e){
        std::cerr<<e.what()<<endl;
        return 0;
      }
    std::stringstream buf;
    buf<<fin.rdbuf();
    fin.close();
    string url_check=buf.str();
    std::regex url_regex(R"((?:https?://)?(?:www\.)?([a-zA-Z0-9]+\.)+[a-zA-Z]{2,3}(?:\.[a-zA-Z]{2})?)");
    std::sregex_iterator it(url_check.begin(), url_check.end(), url_regex);
    std::sregex_iterator end;
    Skaitymas(zodziai,buf,saitai);
    Rasymas(zodziai,saitai,it,end);


}
