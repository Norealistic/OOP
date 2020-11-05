#include "LottoClass.h"

namespace LottoSpace {
    std::ostream& operator <<(std::ostream& c, const Lotto& l) {
        for (int i = 0; i < l.ln; i++) {
            c << "----------------------------------------------" << std::endl << "|";
            for (int j = 0; j < 9; j++) {
                if (!l.card[i][j].status) {
                    c << "    |";
                    continue;
                }
                if (l.card[i][j].status == 1) {
                    if (l.card[i][j].num / 10 > 0)
                        c << " " << l.card[i][j].num << " |";
                    else
                        c << " 0" << l.card[i][j].num << " |";
                }
                else {
                    if (l.card[i][j].num / 10 > 0)
                        c << ">" << l.card[i][j].num << "<|";
                    else
                        c << ">0" << l.card[i][j].num << "<|";
                }
            }
            c << std::endl;
        }
        c << "----------------------------------------------" << std::endl;
        return c;
    }

    std::istream& operator >>(std::istream& c, const Lotto& l) {
        int number;
        c >> number;
        if (!c.good()) {
            c.clear();
            c.ignore(INT_MAX, '\n');
            throw std::invalid_argument("Invalid input");
        }
        if (number < 1 || number > 90)
            throw std::invalid_argument("Invalid number");
        std::cout << "Found " << l.quantity(number) << std::endl;
        return c;
    }

    Lotto::Lotto(int n) {
        if (n < 1 || n > 10)
            throw std::invalid_argument("Invalid number of lines");
        ln = n;
        card = new square * [ln];
        for (int i = 0; i < ln; i++)
            card[i] = new square[9];
        int k;
        int n1, n2;
        for (int i = 0; i < ln; i++) {
            k = 5;
            while (k > 0) {
                n1 = std::rand() % 9;
                n2 = std::rand() % 10;
                if (n1 == 0)
                    n2 = std::rand() % 9 + 1;
                if (n1 == 8)
                    n2 = std::rand() % 11;
                if (card[i][n1].status == 0) {
                    card[i][n1].num = n1 * 10 + n2;
                    card[i][n1].status = 1;
                    k--;
                }
            }
        }
    }

    Lotto::~Lotto() {
        for (int i = 0; i < ln; i++)
            delete[] card[i];
        delete[] card;
    }

    int Lotto::quantity(int a) const {
        int k;
        int n = 0;
        if (a == 90)
            k = 8;
        else
            k = a / 10;
        for (int i = 0; i < ln; i++) {
            if (Lotto::card[i][k].num == a)
                n++;
        }
        return n;
    }

    std::string Lotto::operator()(int x, int y) const {
        if (x < 0 || x >= ln || y < 0 || y >= 9)
            throw std::invalid_argument("Invalid coordinates");
        std::stringstream ss("");
        if (card[x][y].status < 2)
            ss << "This square is empty" << std::endl;
        else
            ss << "This square is busy" << std::endl;
        return ss.str();
    }

    Lotto& Lotto::operator ()(int a) {
        if (a < 1 || a > 90)
            throw std::invalid_argument("Invalid number");
        int k;
        //int count = 0;
        if (a == 90)
            k = 8;
        else
            k = a / 10;
        for (int i = 0; i < Lotto::ln; i++) {
            if (Lotto::card[i][k].num == a) {
                if (Lotto::card[i][k].status == 2) {
                    //std::cout << "This number is already busy: " << a << std::endl;
                    return *this;
                }
                else {
                    Lotto::card[i][k].status = 2;
                    //count = 1;
                }
            }
        }
        /*if (!count) {
            //std::cout << "Number not found: " << a << std::endl;
            return *this;
        }
        std::cout << "This number is now busy: " << a << std::endl;
        */
        return *this;
    }

    int Lotto::busyline() const {
        int f;
        for (int i = 0; i < ln; i++) {
            f = 1;
            for (int j = 0; j < 9; j++) {
                if (card[i][j].status == 1) {
                    f = 0;
                    break;
                }
            }
            if (f)
                return i;
        }
        return -1;
    }

    const int Lotto::operator --(int) {
        int busy = busyline();
        while (busy != -1) {
            for (int i = busy; i < ln - 1; i++) {
                for (int j = 0; j < 9; j++) {
                    card[i][j] = card[i + 1][j];
                }
            }
            for (int j = 0; j < 9; j++) {
                card[ln - 1][j] = { 0, 0 };
            }
            ln--;
            delete[] card[ln];
            busy = busyline();
        }
        if (!ln)
            return 0;
        return 1;
    }

    int Lotto::getln() const {
        return ln;
    }

    std::vector<square> Lotto::unselected() const {
        std::vector<square> arr;
        int f;
        for (int i = 0; i < ln; i++) {
            for (int j = 0; j < 9; j++) {
                if (card[i][j].status == 1) {
                    f = 1;
                    for (int k = 0; k < (signed)arr.size(); k++)
                        if (arr[k].num == card[i][j].num)
                            f = 0;
                    if (f)
                        arr.push_back(card[i][j]);
                }
            }
        }
        if (arr.size() == 0)
            throw std::invalid_argument("No empty numbers");
        return arr;
    }


    Lotto::Lotto(const Lotto& copy) : ln(copy.ln), card(nullptr) {
        if (ln) {
            card = new square * [ln];
            for (int i = 0; i < ln; i++) {
                card[i] = new square[9];
                for (int j = 0; j < 9; j++)
                    card[i][j] = copy.card[i][j];
            }
        }
    }

    Lotto& Lotto::operator =(const Lotto& copy) {
        int f = 0;
        if (ln == copy.ln) {
            for (int i = 0; i < ln; i++) {
                for (int j = 0; j < 9; j++)
                    if (card[i][j].num != copy.card[i][j].num || card[i][j].status != copy.card[i][j].status) {
                        f = 1;
                        break;
                    }
                if (f)
                    break;
            }
        }
        else
            f = 1;

        if (f) {
            for (int i = 0; i < ln; i++)
                delete[] card[i];
            delete[] card;
            ln = copy.ln;
            card = new square * [ln];
            for (int i = 0; i < ln; i++) {
                card[i] = new square[9];
                for (int j = 0; j < 9; j++)
                    card[i][j] = copy.card[i][j];
            }
        }
        return *this;
    }
}
