#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
#define DEFAULT_PATH ".diary_config_file.conf"
#ifdef LINUX
#define FILE_SEP '/'

#else
#define FILE_SEP '/'
#define FAIL_SEP '\\'
#endif

//C:/Users/DevilInChina/Documents/Dairy/Diary
class Diary{

    string Diary_root_path;
    string Editor_path;
    struct tm *local_time = nullptr;

    void init_time(){
        time_t timep;
        time(&timep);
        local_time = gmtime(&timep);
    }

public:

    static void Format(string&s){
        for(auto &c:s){
            if(c==FAIL_SEP){
                c=FILE_SEP;
            }
        }
    }

    static void Format_Add_Quotes(string &s){
        s = "\""+s+"\"";
    }

    static void Execute(string cmd){
        Format(cmd);
        system(cmd.c_str());
    }

    static vector<string> ReadFile(const char *filePath){
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

    static bool IfFileExist(const char *filePath){
        fstream f(filePath,ios::in);
        if(f.is_open()) {
            f.close();
            return true;
        }
        return false;
    }

    static void WriteFile(const char *filePath,const string &info){
        fstream f(filePath,ios::out);
        f<<info<<endl;
        f.close();
    }
    static void WriteFile(const char *filePath,const vector<string> &info){
        fstream f(filePath,ios::out);
        for(auto &it:info) {
            f << it << endl;
        }
        f.close();
    }


    void CreateDay(int year,int month,int day){

        string path = to_string(year)+FILE_SEP+to_string(month);
        string current_monthPath = Diary_root_path+FILE_SEP+path;
        int c = access(current_monthPath.c_str(),0);
        if(c==-1) {
            Execute("mkdir -p " + current_monthPath);
        }else{

        }
        current_monthPath+=FILE_SEP;
        string s_day = to_string(day);
        if(s_day.size()<2)s_day = "0"+s_day;
        current_monthPath+=s_day+".md";
        Format_Add_Quotes(current_monthPath);//// add quotes

        if(IfFileExist(current_monthPath.c_str())){

        }else{
            string firstInfo="# "+to_string(year)+"年"+to_string(month)+"月"+s_day+"日\n";
            WriteFile(current_monthPath.c_str(),firstInfo);
        }

        Format_Add_Quotes(Editor_path);


        current_monthPath =Editor_path +" "+ current_monthPath;


        Execute(current_monthPath);
    }

    void CreateDay(){
        int year = local_time->tm_year+1900;
        int month = local_time->tm_mon+1;
        int day = local_time->tm_mday;
        CreateDay(year,month,day);
    }

    void GetALine(string &temp){
        getline(cin, temp);
    }

    void Init(){
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
                cout << "Editor path<<";
                getline(cin, temp);
                it.push_back(temp);
            }
            default:{
                break;;
            }
        }
        WriteFile(DEFAULT_PATH, it);
        Diary_root_path = it[0];
        Editor_path = it[1];
        init_time();
    }

    void Circulation(){
        CreateDay();
        while (true){
            string cmd;
            cout<<"<<";
            GetALine(cmd);
            if(cmd=="exit")break;
        }
    }
};
int main(int argc,char **argv) {
    Diary this_diary;
    this_diary.Init();
    this_diary.Circulation();
    return 0;
}