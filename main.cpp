#include <bits/stdc++.h>

using namespace std;
#define DEFAULT_PATH ".diary_config_file.conf"
#ifdef WIN32
#define FILE_SEP '/'
#include <io.h>
#else
#define FILE_SEP '/'
#include <unistd.h>
#endif
vector<string> ReadFile(const char *filePath){
    fstream f(filePath,ios::in);
    vector<string> ret;
    if(f.is_open()) {
        string s;
        while (getline(f, s, (char) '\n')) {
            ret.push_back(s);
        }
        f.close();
    }
    return ret;
}

bool IfFileExist(const char *filePath){
    fstream f(filePath,ios::in);
    if(f.is_open()) {
        f.close();
        return true;
    }
    return false;
}

void WriteFile(const char *filePath,const string &info){
    fstream f(filePath,ios::out);
    f<<info<<endl;
    f.close();
}



int main(int argc,char **argv) {

    string Diary_root_path;
    string typora_path;
    if(argc==1){
        auto it = ReadFile(DEFAULT_PATH);
        string temp;
        switch (it.size()) {
            case 0:{
                cout << "Start to write config file\n";
                cout << "Diary root path<<";
                getline(cin, temp);
                it.push_back(temp);
            }
            case 1:{
                cout << "typora path<<";
                getline(cin, temp);
                it.push_back(temp);
            }
            default:{
                break;;
            }
        }
        WriteFile(DEFAULT_PATH, it[0]+'\n'+it[1]);
        Diary_root_path = it[0];
        typora_path = it[1];
    }
    time_t timep;
    struct tm *p;

    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year+1900;
    int month = p->tm_mon+1;
    int day = p->tm_mday;
    string path = to_string(year)+FILE_SEP+to_string(month);
    string current_monthPath = Diary_root_path+FILE_SEP+path;
    int c = access(current_monthPath.c_str(),0);
    if(c==-1) {
        system(("mkdir -p " + current_monthPath).c_str());
    }else{

    }
    current_monthPath+=FILE_SEP;
    string s_day = to_string(day);
    if(s_day.size()<2)s_day = "0"+s_day;
    current_monthPath+=s_day+".md";
    if(IfFileExist(current_monthPath.c_str())){

    }else{

        string firstInfo="# "+to_string(year)+"年"+to_string(month)+"月"+s_day+"日\n";
        WriteFile(current_monthPath.c_str(),firstInfo);
    }
    current_monthPath =typora_path +" \""+ current_monthPath+"\"";
    cout<<current_monthPath<<endl;
    system(current_monthPath.c_str());
    return 0;
}
