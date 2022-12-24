#include "Dice.h"
#include <iostream>
#include <fstream>

int main()
{
    std::srand(time(NULL));

    int data_1d6 [6] = {};
    int data_2d6 [12] = {};
    int data_3d6 [18] = {};
    int data_1d10 [10] = {};
    int data_2d10 [20] = {};
    int data_3d10 [30] = {};

    for (int i = 0; i < 100000; i++)
    {
        std::cout << i+1 << " of 100000\n";
        data_1d6[ThrowDice(1, "1d6").at(0)-1]++;
        data_2d6[ThrowDice(1, "2d6").at(0)-1]++;
        data_3d6[ThrowDice(1, "3d6").at(0)-1]++;
        data_1d10[ThrowDice(1, "1d10").at(0)-1]++;
        data_2d10[ThrowDice(1, "2d10").at(0)-1]++;
        data_3d10[ThrowDice(1, "3d10").at(0)-1]++;
    }

    std::cout << "Writing to file\n";

    std::ofstream os("stats.txt");
    for (int i = 0; i < 6; i++)
        os << data_1d6[i] << "\t";
    os << "\n";
    for (int i = 0; i < 12; i++)
        os << data_2d6[i] << "\t";
    os << "\n";
    for (int i = 0; i < 18; i++)
        os << data_3d6[i] << "\t";
    os << "\n";
    for (int i = 0; i < 10; i++)
        os << data_1d10[i] << "\t";
    os << "\n";
    for (int i = 0; i < 20; i++)
        os << data_2d10[i] << "\t";
    os << "\n";
    for (int i = 0; i < 30; i++)
        os << data_3d10[i] << "\t";
    os << "\n";

    os.close();
}
