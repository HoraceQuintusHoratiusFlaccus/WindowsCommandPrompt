#include <iostream>
#include <windows.h>

using namespace std;

class Cmd
{
private:
    string Cmd_command;
    char CurPath[MAX_PATH], CurPath2[MAX_PATH];

public:
    int PathCase(const string&);
    int PathCase2(const string&, const string&);
    void InputCommand(const string&);
    void Cmd_ls();
    void Cmd_cd();
    void Cmd_pwd();
    void Cmd_cp();
    void Cmd_mv();
    void Cmd_rm();
    void Cmd_touch();
    void Cmd_mkdir();
    void Cmd_rmdir();
    void Cmd_cat();
};