#pragma once

#include <iostream>
#include <sstream>
#include <ctime>
#include <sstream>
#include <vector>
#include "unistd.h"


namespace LottoSpace {
    struct square {
        int num;
        int status;
        square(int a = 0, int b = 0) : num(a), status(b) {};    //0 - пустая, 1 - свободная с числом, 2 - занятая с числом
    };

    class Lotto {
    private:
        square** card;
        int ln;
    public:
        int getln() const;
        Lotto(int n = 10);
        int quantity(int a) const;
        std::string operator ()(int x, int y) const;
        Lotto& operator ()(int a);
        int busyline() const;
        const int operator --(int);
        std::vector<square> unselected() const;
        Lotto(const Lotto& a);
        Lotto& operator =(const Lotto& copy);
        ~Lotto();
        friend std::ostream& operator <<(std::ostream&, const Lotto&);
        friend std::istream& operator >>(std::istream&, const Lotto&);
    };
}

