#include <direct.h>
#include "Cmd.hpp"

int Cmd::PathCase(const string& Path)
{
    if (Path[0] == 'C' && Path[1] == ':' && Path[2] == '\\')
        return 0;

    else
    {
        getcwd(CurPath, MAX_PATH);
        strcat(CurPath, "\\");
        strcat(CurPath, Path.data());

        return 1;
    }
}

int Cmd::PathCase2(const string& SrcPath, const string& DstPath)
{
    if (SrcPath[0] == 'C' && SrcPath[1] == ':' && SrcPath[2] == '\\')
    {
        if (DstPath[0] == 'C' && DstPath[1] == ':' && DstPath[2] == '\\')
            return 0;

        else
        {
            getcwd(CurPath, MAX_PATH);
            strcat(CurPath, "\\");
            strcat(CurPath, DstPath.data());

            return 1;
        }
    }

    else
    {
        getcwd(CurPath, MAX_PATH);
        strcat(CurPath, "\\");
        strcat(CurPath, SrcPath.data());

        if (DstPath[0] == 'C' && DstPath[1] == ':' && DstPath[2] == '\\')
            return 2;

        else
        {
            getcwd(CurPath2, MAX_PATH);
            strcat(CurPath2, "\\");
            strcat(CurPath2, DstPath.data());

            return 3;
        }
    }
}

void Cmd::InputCommand(const string& Command)
{
    Cmd_command = Command;

    if (Cmd_command == "ls")
        Cmd_ls();

    else if (Cmd_command[0] == 'c' && Cmd_command[1] == 'd')
        Cmd_cd();

    else if (Cmd_command == "pwd")
        Cmd_pwd();

    else if (Cmd_command[0] == 'c' && Cmd_command[1] == 'p')
        Cmd_cp();

    else if (Cmd_command[0] == 'm' && Cmd_command[1] == 'v')
        Cmd_mv();

    else if (Cmd_command[0] == 'r' && Cmd_command[1] == 'm' && Cmd_command[2] == 'd' && Cmd_command[3] == 'i' && Cmd_command[4] == 'r')
        Cmd_rmdir();

    else if (Cmd_command[0] == 't' && Cmd_command[1] == 'o' && Cmd_command[2] == 'u' && Cmd_command[3] == 'c' && Cmd_command[4] == 'h')
        Cmd_touch();

    else if (Cmd_command[0] == 'm' && Cmd_command[1] == 'k' && Cmd_command[2] == 'd' && Cmd_command[3] == 'i' && Cmd_command[4] == 'r')
        Cmd_mkdir();

    else if (Cmd_command[0] == 'r' && Cmd_command[1] == 'm')
        Cmd_rm();

    else if (Cmd_command[0] == 'c' && Cmd_command[1] == 'a' && Cmd_command[2] == 't')
        Cmd_cat();

    else
        cout << Cmd_command << " is an unknown command." << endl;

    return;
}

void Cmd::Cmd_ls()
{
    WIN32_FIND_DATA FileData;

    getcwd(CurPath, MAX_PATH);
    strcat(CurPath, "\\*");

    HANDLE Handle = FindFirstFile((LPCWSTR)CurPath, &FileData);

    cout << FileData.cFileName << endl;

    while (FindNextFile(Handle, &FileData) != 0)
        cout << FileData.cFileName << endl;

    FindClose(Handle);
}

void Cmd::Cmd_cd()
{
    string Path = Cmd_command.substr(3);
    int flag = PathCase(Path);

    switch (flag)
    {
    case 0:
        chdir((const char*)Path.data());
        break;
    case 1:
        chdir((const char*)CurPath);
        break;
    }
}

void Cmd::Cmd_pwd()
{
    getcwd(CurPath, MAX_PATH);
    cout << CurPath << endl;
}

void Cmd::Cmd_cp()
{
    Cmd_command = Cmd_command.substr(3);

    int idx;
    for (idx = 0; Cmd_command[idx] != ' '; ++idx) {}

    string SrcPath = Cmd_command.substr(0, idx);
    string DstPath = Cmd_command.substr(idx + 1);

    int flag = PathCase2(SrcPath, DstPath);

    switch (flag)
    {
    case 0:
        CopyFile((LPCTSTR)SrcPath.data(), (LPCTSTR)DstPath.data(), true);
        break;
    case 1:
        CopyFile((LPCTSTR)SrcPath.data(), (LPCTSTR)CurPath, true);
        break;
    case 2:
        CopyFile((LPCTSTR)CurPath, (LPCTSTR)DstPath.data(), true);
        break;
    case 3:
        CopyFile((LPCTSTR)CurPath, (LPCTSTR)CurPath2, true);
        break;
    }
}

void Cmd::Cmd_mv()
{
    Cmd_cp();

    int idx;
    for (idx = 0; Cmd_command[idx] != ' '; ++idx) {}

    string SrcPath = Cmd_command.substr(0, idx);

    int flag = PathCase(SrcPath);

    switch (flag)
    {
    case 0:
        remove((const char*)SrcPath.data());
        break;
    case 1:
        remove((const char*)CurPath);
        break;
    }
}

void Cmd::Cmd_rm()
{
    string Path = Cmd_command.substr(3);

    int flag = PathCase(Path);

    switch (flag)
    {
    case 0:
        remove((const char*)Path.data());
        break;
    case 1:
        remove((const char*)CurPath);
        break;
    }
}

void Cmd::Cmd_touch()
{
    HANDLE Handle;

    string Path = Cmd_command.substr(6);

    int flag = PathCase(Path);

    switch (flag)
    {
    case 0:
        Handle = CreateFile((LPCTSTR)Cmd_command.data(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        break;
    case 1:
        Handle = CreateFile((LPCTSTR)CurPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        break;
    }

    CloseHandle(Handle);
}

void Cmd::Cmd_mkdir()
{
    string Path = Cmd_command.substr(6);

    int flag = PathCase(Path);

    switch (flag)
    {
    case 0:
        CreateDirectory((LPCTSTR)Cmd_command.data(), NULL);
        break;
    case 1:
        CreateDirectory((LPCTSTR)CurPath, NULL);
        break;
    }
}

void Cmd::Cmd_rmdir()
{
    string Path = Cmd_command.substr(6);

    int flag = PathCase(Path);

    switch (flag)
    {
    case 0:
        RemoveDirectory((LPCTSTR)Cmd_command.data());
        break;
    case 1:
        RemoveDirectory((LPCTSTR)CurPath);
        break;
    }
}

void Cmd::Cmd_cat()
{
    FILE* pFile = NULL;
    char FileData[1024] = { 0 };

    string Path = Cmd_command.substr(4);

    int flag = PathCase(Path);

    switch (flag)
    {
    case 0:
        pFile = fopen((const char*)Path.data(), "r");
        break;
    case 1:
        pFile = fopen((const char*)CurPath, "r");
        break;
    }

    while (!feof(pFile))
    {
        fgets(FileData, sizeof(FileData), pFile);

        cout << FileData;
    }

    fclose(pFile);
}