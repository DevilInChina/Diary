#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
#define DEFAULT_PATH ".diary_config_file.conf"
#ifdef LINUX
#define FILE_SEP '/'
#define FAIL_SEP '\\'
#else
#define FILE_SEP '/'
#define FAIL_SEP '\\'
#endif

//C:/Users/DevilInChina/Documents/Dairy/Diary
class Diary{
    enum SITUATION{
        IDLE,EXIT
    };
    enum SINGLE_FILE_OPT{
        ADD,DEL,MOVE
    };
    string Diary_root_path;
    string Editor_path;
    struct tm *local_time = nullptr;

    void init_time(){
        time_t timep;
        time(&timep);
        local_time = gmtime(&timep);
    }

public:

    static void Format(string&s,char originChar = FAIL_SEP,char newChar = FILE_SEP){
        for(auto &c:s){
            if(c==originChar){
                c=newChar;
            }
        }
    }

    static void Format_Add_Quotes(string &s){
        s = "\""+s+"\"";
    }

    static int Execute(string cmd,bool format = true,bool showFinalCommand = false){
        if(format)
            Format(cmd);
        if(showFinalCommand) {
            cout << cmd << endl;
        }
        return system(cmd.c_str());
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
        if(f.is_open()) {
            f << info << endl;
            f.close();
        }else{
            cout<<"File "<<filePath<<" cannot be write please check if file path is right.\n";
        }
    }
    static void WriteFile(const char *filePath,const vector<string> &info){
        fstream f(filePath,ios::out);
        for(auto &it:info) {
            f << it << endl;
        }
        f.close();
    }

    static int MK_dir(const string&filePath,bool showFinalCommand = false){
#ifdef LINUX
        return Execute("mkdir -p " + filePath);
#else
        string cpy=filePath;
        Format(cpy,FILE_SEP,FAIL_SEP);
        Format_Add_Quotes(cpy);
        return Execute(("mkdir -p "+cpy), false,showFinalCommand);
#endif
    }
    void CreateDay(int year,int month,int day,SINGLE_FILE_OPT opt= ADD) {

        string path = to_string(year) + FILE_SEP + to_string(month);
        string current_monthPath = Diary_root_path + FILE_SEP + path;
        switch (opt) {
            case ADD: {

                int c = access(current_monthPath.c_str(), 0);
                if (c == -1) {
                    int k = MK_dir(current_monthPath, false);
                    if (k != 0) {
                        cout << "Error in mkdir\n" << endl;
                        MK_dir(current_monthPath, true);
                        return;
                    }
                } else {

                }
                current_monthPath += FILE_SEP;
                string s_day = to_string(day);
                if (s_day.size() < 2)s_day = "0" + s_day;
                current_monthPath += s_day + ".md";

                if (IfFileExist(current_monthPath.c_str())) {

                } else {
                    string firstInfo = "# " + to_string(year) + "年" + to_string(month) + "月" + s_day + "日\n";

                    WriteFile(current_monthPath.c_str(), firstInfo);
                }

                //Format_Add_Quotes(current_monthPath);//// add quotes
                Format_Add_Quotes(Editor_path);


                current_monthPath = Editor_path + " " + current_monthPath;


                Execute(current_monthPath);

            }
                break;
            case DEL:{

            }break;
            case MOVE:{

            }break;
        }
    }

    void CreateDay(){
        int year = local_time->tm_year+1900;
        int month = local_time->tm_mon+1;
        int day = local_time->tm_mday;
        CreateDay(year,month,day);
    }
    static bool cmp_no_Cap(const string &a,const string &b){
        string A(a),B(b);
        for(auto &i:A){
            i = isalpha(i)?tolower(i):i;
        }
        for(auto &i:B){
            i = isalpha(i)?tolower(i):i;
        }
        return A==B;
    }

    static vector<string>SepToVector(const string&str){
        stringstream sin(str);
        vector<string>ret;
        string temp;
        while (sin>>temp){
            ret.push_back(temp);
        }
        return ret;
    }
    string buffer;
    SITUATION GetALine(string &temp){
        getline(cin, temp);
        if(!temp.empty()) {
            auto it = SepToVector(temp);
            if (cmp_no_Cap(it[0], "exit"))return EXIT;
            buffer = string();
            if(cmp_no_Cap(it[0],"open")||cmp_no_Cap(it[0],"touch")) {

            }else if(cmp_no_Cap(it[0],"rm") || cmp_no_Cap(it[0],"del") ){

            }
        }else{
            return IDLE;
        }
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
        SITUATION current = IDLE;
        while (true){
            string cmd;
            switch (current) {
                case EXIT:{
                    exit(0);
                }break;
                case IDLE:{
                    cout<<"<<";
                }break;
                default:{

                }break;
            }
            auto it = GetALine(cmd);

            switch (current) {
                case IDLE:{
                    current = it;
                }break;
                case EXIT:{
                    cout<<"Error situation MID-EXIT\n";
                }break;
            }
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