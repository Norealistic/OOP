#include <iostream>
#include"BigInt.h"
#include <stdio.h>

using namespace NS3;
int main()
{
        char* str = new char[228];
        std::cout << "Enter 1 number (string)\n";
        std::cin >> str;
        BigInt num(str);
        num.Output();
        num.Dev10();
        num.Output();
        num.Mult10();
        num.Output();
        std::cout << "Enter 2 number (stream)\n";
        std::istream& i = std::cin;
        BigInt b(i);
        b.Output();
        int ff;
        std::cout << "Enter number to add to the 2 one\n";
        std::cin >> ff;
        b.Add(ff);
        b.Output();
        std::cout << "Enter number to sub from the previous one\n";
        std::cin >> ff;
        b.Sub(ff);
        b.Output();
        delete[] str;
    }
