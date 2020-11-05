#include <iostream>
#include "BigInt_dyn.hpp"
#include <string.h>
#include <stdexcept>

namespace NS3 {
    using BigInt = BigInt;

    BigInt::BigInt() {
        num = new char[2];
        len = 1;
        num[0] = '0';
        num[1] = '0';
    }

    BigInt::BigInt(int k, int) {
        len = k;
        if (k == 0)
            len++;
        num = new char[len + 1];
        for (int i = 0; i <= len; i++)
            num[i] = '0';
    }

    BigInt::BigInt(int a) :BigInt() {
        char sgn = a < 0 ? '9' : '0';
        a = a < 0 ? -a : a;
        int i = 10, k = 1;
        while (a / i > 0) {
            i *= 10;
            k++;
        }
        delete[]num;
        num = new char[k + 1];
        len = k;
        num[0] = sgn;
        for (int l = k; l >= 1; l--) {
            num[l] = (char)(((int)'0') + a % 10);
            a/= 10;
        }
    }

    BigInt::BigInt(long a) :BigInt() {
        num[0] = a < 0 ? '9' : '0';
        a = a < 0 ? -a : a;
        int i = 10, k = 1;
        while (a / i > 0) {
            i *= 10;
            k++;
        }
        delete[]num;
        num = new char[k + 1];
        len = k;
        for (int l = k; l >= 1; l--) {
            num[l] = (char)(((int)'0') + a % 10);
            a /= 10;
        }
    }

    BigInt::BigInt(const char* str) :BigInt() {
        if (str == nullptr)
            throw std::invalid_argument("Nullptr");
        bool zero = true;
        char sgn;
        int l = (int)strlen(str), z = 0;
        if (str[0] == '-') {
            sgn = '9';
            z++;
            l--;
        }
        else sgn = '0';
        if (l != strspn(str + (sgn == '9' ? 1 : 0), "0123456789"))
            throw std::invalid_argument("Data error!");
        while (zero && l > 0) {
            if (str[z] == '0') {
                z++;
                l--;
            }
            else zero = false;
        }
        if (!zero) {
            delete[]num;
            num = new char[l + 1];
            len = l;
            num[0] = sgn;
            for (int i =1; i <= l; i++) {
                num[i] = str[z];
                z++;
            }
        }
    }

    BigInt::BigInt(const BigInt& orig, int m){
        num = new char[orig.len + m+1];
        num[0] = orig.num[0];
        int i = 1;
        for (; i <= m; i++)
            num[i] = '0';
        for (; i <= orig.len+m; i++)
            num[i] = orig.num[i - m];
        len = orig.len + m;
    }

    BigInt::BigInt(const BigInt& orig) {
        try {
            len = orig.len;
            num = new char[len + 1];
            for (int i = 0; i < len + 1; i++)
                num[i] = orig.num[i];
        }
        catch (...) {
            std::cout << "Empty initialization!";
            len = 1;
            num = new char[2];
            num[0] = num[1] = '0';
        }
    }

    const BigInt BigInt::operator~ ()const {
        if (num[0] == '0')
            return *this;
        bool pr = true;//"запас" перенос +1 в след разряд
        BigInt res(len,1);
        for (int i = len; i > 0; i--) {
            if (pr && num[i] != '0') {
                res.num[i] = (char)10 - (num[i] - '0') + '0';
                pr = false;
            }
            else {
                if (!pr)
                    res.num[i] = (char)9 - (num[i] - '0') + '0';
                else res.num[i] = '0';
            }
            
        }
        res.num[0] = '9';
        return res;
    }

    std::istream& operator>>(std::istream& i, BigInt& the) {
        char* n = new char[255];
        i >> n;
        bool zero = true;
        char sgn;
        int l = (int)strlen(n), z = 0;
        if (n[0] == '-') {
            sgn = '9';
            z++;
            l--;
        }
        else sgn = '0';
        if (l != strspn(n + (sgn == '9' ? 1 : 0), "0123456789"))
            throw std::invalid_argument("Data error!");
        while (zero && l > 0) {
            if (n[z] == '0') {
                z++;
                l--;
            }
            else zero = false;
        }
        if (zero) {
            delete[]the.num;
            the.len = 1;
            the.num = new char[2];
            the.num[0] = the.num[1] = '0';
        }
        else {
            delete[]the.num;
            the.num = new char[l + 1];
            the.len = l;
            the.num[0] = sgn;
            for (int i = 1; i <= l && z <= l; i++) {
                the.num[i] = n[z];
                z++;
            }
        }
        delete[]n;
        return i;
    }

    std::ostream& operator <<(std::ostream& c, const BigInt& the) {
        if (the.num[0] == '9')
            c << "-";
        for (int i = 1; i <= the.len; i++)
                c << the.num[i];
        return c;
    }

    BigInt operator + (const BigInt& the, const BigInt& BSlg) {
            BigInt slg1(the, the.len > BSlg.len ? 1 : BSlg.len-the.len+1), slg2(~BSlg);
            slg1 = ~slg1;
            int  pr = 0;
            for (int i = slg1.len;i > slg1.len-slg2.len;i--) {
                if (slg1.num[i] - '0' + slg2.num[i + slg2.len-slg1.len] - '0' + pr < 10) {
                    slg1.num[i] = slg1.num[i] - '0' + slg2.num[i + slg2.len - slg1.len] - '0' + pr + '0';
                    pr = 0;
                }
                else {
                    slg1.num[i] = slg1.num[i] - '0' + slg2.num[i + slg2.len - slg1.len] - '0' + pr + '0' - 10;
                    pr = 1;
                }
            }
            char dop = slg2.num[0] == '0' ? '0' : '9';
            for (int i = slg1.len - slg2.len ;i >= 0;i--) {
                if (slg1.num[i] - '0'+dop-'0'  + pr < 10) {
                    slg1.num[i] = slg1.num[i] + pr+dop-'0';
                    pr = 0;
                }
                else {
                    slg1.num[i] = slg1.num[i] - '0' + dop - '0' + pr + '0' - 10;;
                    pr = 1;
                }
            }
            slg1 = ~slg1;
            slg1.correction();
            return slg1;
    }

    const BigInt BigInt::operator - () const {
        BigInt res = *this;
        for (int i = 0; i <= len; i++) {
            if (num[i] != '0') {
                res.num[0] = num[0] == '0' ? '9' : '0';
                break;
            }
        }
        return res;
    }

    const BigInt BigInt:: operator * (const int& a) {
        if (a != 10)
            throw std::invalid_argument("Unprovided operation!");
        if (len > 1 || num[1] != '0') {
            BigInt res(len + 1, 1);
            for (int i = 0;i <= len;i++)
                res.num[i] = num[i];
            res.num[len + 1] = '0';
            return res;
        }
        else {
            return *this;
        }
    }

    const BigInt BigInt::operator / (const int& i) {
        if (i != 10)
            throw std::invalid_argument("Unprovided operation!");
        bool zero = true;
        BigInt res(len - 1, 1);
        for (int i = 0; i <len; i++) {
            res.num[i] = num[i];
            if (zero && i>0 && num[i] != '0')
                zero = false;
        }
        if (zero) {
            res.num[0] = '0';
            res.len = 1;
            return res;
        }
        return res;
    }

    BigInt& BigInt::operator = (const BigInt & ob) {
        if (this->num != ob.num) {
            if (num!= nullptr)
            delete[]num;
            if (ob.len != 0) {
                len = ob.len;
                num = new char[ob.len+1];
                for (int i = 0;i <= len;i++)
                    num[i] = ob.num[i];
            }
        }
        return *this;
    }

    BigInt& BigInt::operator=(BigInt&& ob)  {
     //   if (num != nullptr) {
            delete[]num;
            num = ob.num;
            len = ob.len;
            ob.num = nullptr;
        
        return *this;
    }

    void BigInt::correction() {
        if (num[1] == '0') {
            num[0] = (num[0] == '9' ? '-' : '0');
            for (int i = 1;i < len;i++)
                num[i] = num[i + 1];
            num[len] = '\0';
            *this = num;
        }
    }

    BigInt::operator int() const {
        int i=0;
        int pow = 1;
        if (len > 8)
            throw std::invalid_argument("Error");
        for (int k = len; k >= 1; k--) {
            i += (num[k] - '0') * pow;
            pow *= 10;
        }
        i = num[0] == '0' ? i:-i;
        return i;
    }

}
