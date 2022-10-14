#include "Year.h"

int main()
{
    // set up console to be able to use ANSI escape codes (control cursor location/change colour) //

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    setlocale(LC_ALL, "Russian");

    Year year;
    year.IfPossibleProposeToLoad();
    year.SetSeed();
    while (year.GetNumber() <= year.GetNumberMAX())
    {
        year.AboutTheYear();
        year.SetOrder();
        year.YearPasses();
        year.ActIfGameOver();
        if (year.GetGameOverState())
            if (HearYesOrNo("Вы бы хотели начать новую игру? д/н "))
            {
                std::remove("game.save");
                year.~Year();
                new (&year) Year();
                year.SetSeed();
            }
            else
            {
                std::remove("game.save");
                break;
            }
        else if (year.ProposeToSave())
            break;
    }
}
