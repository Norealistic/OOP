#include <iostream>
#include "BigInt.hpp"
#include <string.h>
#include <stdexcept>

namespace NS3 {

    BigInt::BigInt() {
    for (int i = 0; i < MaxLen + 1; i++)
        num[i] = '0';
    }

    BigInt::BigInt(int n){
            num[0] = n < 0 ? '9' : '0';
            n = n < 0 ? -n : n;
            int i = 10, k = 1;
            while (n / i > 0) {
                i *= 10;
                k++;
            }
            if (k > MaxLen)
                throw std::out_of_range("Overflow");
            for (int l = 1; l <= MaxLen - k + 1; l++)
                num[l] = '0';
            for (int l = MaxLen; l >= MaxLen - k + 1; l--) {
                num[l] = (char)(((int)'0') + n % 10);
                n /= 10;
            }
        }

    BigInt::BigInt(long  n){
            num[0] = n < 0 ? '9' : '0';
            n = n < 0 ? -n : n;
            int i = 10, k = 1;
            while (n / i > 0) {
                i *= 10;
                k++;
            }
            if (k > MaxLen)
                 throw std::out_of_range("Overflow");
            for (int l = 1; l <= MaxLen - k + 1; l++)
                num[l] = '0';
            for (int l = MaxLen; l >= MaxLen - k + 1; l--) {
                num[l] = (char)(((int)'0') + n % 10);
                n /= 10;
            }
        }


    BigInt::BigInt(const char* str){
            bool zero = true;
            int length = (int)strlen(str), z = 0;
            if (length > MaxLen)
                throw std::out_of_range("Overflow");
            if (str[0] == '-') {
                num[0] = '9';
                z++;
                length--;
            }
            else num[0] = '0';
            if (length != strspn(str + (num[0] == '9' ? 1 : 0), "0123456789"))
                throw std::invalid_argument("Data error!");
            for (int k = 1; k <= MaxLen - length; k++) {
                num[k] = '0';
            }
            for (int k = MaxLen - length + 1; k <= MaxLen; k++) {
                num[k] = str[z];
                z++;
                if (zero && num[k] != '0')
                    zero = false;
            }
            if (zero)
                num[0] = '0';
    }


    const BigInt BigInt::operator~ ()const {
        if (num[0] == '0')
           return *this;
        bool pr = true;//"запас" перенос +1 в след разряд
        BigInt res;
        for (int i = MaxLen; i > 0; i--) {
                if (pr && num[i] != '0') {
                    res.num[i] = (char)10 - (num[i] - '0') + '0';
                    pr = false;
                }
                else if (!pr)
                    res.num[i] = (char)9 - (num[i] - '0') + '0';
        }
        res.num[0] = '9';
        return res;
    }

    std::istream& operator>>(std::istream& i,BigInt& the) {
            char n[the.MaxLen + 1];
            i >> n;
            bool zero = true;
            int l = (int)strlen(n), z = 0;
            if (l > the.MaxLen)
                throw std::out_of_range("Overflow");
            if ((l - (n[0] == '-' ? 1 : 0)) != strspn(n + (n[0] == '-' ? 1 : 0), "0123456789"))
                throw std::invalid_argument("Data error!");
            if (n[0] == '-') {
                the.num[0] = '9';
                z++;
                l--;
            }
            else the.num[0] = '0';
            for (int k = 1; k <= the.MaxLen - l; k++) {
                the.num[k] = '0';
            }
            for (int k = the.MaxLen - l + 1; k <= the.MaxLen; k++) {
                the.num[k] = n[z];
                z++;
                if (zero && the.num[k] != '0')
                    zero = false;
            }
            if (zero)
                the.num[0] = '0';
            return i;
    }

    std::ostream& operator <<(std::ostream& c, const BigInt& the) {
        if (the.num[0] == '9')
            c << "-";
        bool print = false;
        for (int i = 1; i <= the.MaxLen; i++) {
            if (!print && the.num[i] != '0')
                print = true;
            if (print)
                c << the.num[i];
        }
        if (!print)
            c << '0';
        c << std::endl;
        return c;
    }

    BigInt operator+(const BigInt& the, const BigInt& BSlg) {
            bool prInd = (the.num[0] == BSlg.num[0] );
            BigInt slg1(~the), slg2(~BSlg);
            int pr = 0;
            for (int i = the.MaxLen; i >= 0; i--) {
                if (slg1.num[i] - '0' + slg2.num[i] - '0' + pr < 10) {
                    slg1.num[i] = slg1.num[i] - '0' + slg2.num[i] - '0' + pr + '0';
                    pr = 0;
                }
                else {
                    slg1.num[i] = slg1.num[i] - '0' + slg2.num[i] - '0' + pr + '0' - 10;
                    pr = 1;
                }
            }
            if (pr > 0 && prInd && slg1.num[1] == '0')
                throw std::out_of_range("Overflow!");
            slg1 = ~slg1;
            return slg1;
    }

  const BigInt BigInt::operator-() const {
        BigInt res = *this;
        for (int i = 0; i <= MaxLen; i++) {
            if (num[i] != '0') {
                res.num[0] = num[0] == '0' ? '9' : '0';
                break;
            }
        }
        return res;
    }

    const BigInt BigInt:: operator*(const int& a) {
            if (a != 10)
                throw std::invalid_argument("Invalid argument");
            BigInt res;
            if (num[1] != '0')
                throw std::invalid_argument("Invalid argument");
            for (int i = 1;i < MaxLen;i++)
                res.num[i] = num[i + 1];
            res.num[MaxLen] = '0';
            res.num[0] = num[0];
            return res;
    }

    const BigInt BigInt::operator /(const int& i) {
        if (i != 10)
            throw std::invalid_argument("Invalid argument");
        BigInt res;
        bool zero = true;
        res.num[0] = num[0];
        for (int i = MaxLen; i > 1; i--) {
            res.num[i] = num[i - 1];
            if (zero && (num[i] != '0') && i < MaxLen)
                zero = false;
        }
        res.num[1] = '0';
        if (zero)
            res.num[0] = '0';
        return res;
    }
}



