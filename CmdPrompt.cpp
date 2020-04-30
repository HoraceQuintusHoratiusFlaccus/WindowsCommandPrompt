#include <iostream>
#include <string>
#include "Cmd.hpp"

using namespace std;

int main()
{
    string Command;
    Cmd CmdPrompt;

    while (true)
    {
        cout << ">> ";
        getline(cin, Command);

        if (Command == "exit")
            return 0;

        CmdPrompt.InputCommand(Command);
    }
}