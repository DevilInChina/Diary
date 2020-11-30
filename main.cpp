#include <bits/stdc++.h>

using namespace std;
#define DEFAULT_PATH ".diary_config_file.conf"
#ifdef WIN32
#define FILE_SEP '\\'
#include <io.h>
#else
#define FILE_SEP '/'
#include <unistd.h>
#endif
string ReadFile(const char *filePath){
    fstream f(filePath,ios::in);
    string ret;
    if(f.is_open()) {
        string s;
        getline(f, ret, (char) EOF);
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

    if(argc==1){
        auto it = ReadFile(DEFAULT_PATH);
        if(it.empty()) {
            cout << "Start to write config file\n";
            cout << "Diary root path<<";
            getline(cin, Diary_root_path);
            WriteFile(DEFAULT_PATH, Diary_root_path);
        }else{
            stringstream sin(it);
            getline(sin,Diary_root_path);
        }
    }else if(argc==2){
        auto it = ReadFile(argv[1]);
        stringstream sin(it);
        getline(sin,Diary_root_path);
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
    current_monthPath+=to_string(day)+".md";
    if(IfFileExist(current_monthPath.c_str())){

    }else{
        string firstInfo="# "+to_string(year)+"年"+to_string(month)+"月"+to_string(day)+"日\n";
        WriteFile(current_monthPath.c_str(),firstInfo);
    }
    system(current_monthPath.c_str());
    return 0;
}
