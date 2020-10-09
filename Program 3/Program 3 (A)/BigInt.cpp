#include <iostream>
#include "BigInt.h"
#include <string.h>


namespace NS3 {

    BigInt::BigInt() {
        for (int i = 0; i < MaxLen + 1; i++)
            num[i] = '0';
    }
    
    BigInt::BigInt(int n){
        try {
            num[0] = n < 0 ? '9' : '0';
            n = n < 0 ? -n : n;
            int i = 10, k = 1;
            while (n / i > 0) {
                i *= 10;
                k++;
            }
            if (k > MaxLen)
                throw "Overflow";
            for (int l = 1; l <= MaxLen - k + 1; l++)
                num[l] = '0';
            for (int l = MaxLen; l >= MaxLen - k + 1; l--) {
                num[l] = (char)(((int)'0') + n % 10);
                n /= 10;
            }
        }
        catch (...) {
            std::cout << "Your value is bigger then MaxSize." << std::endl;
        }
    }
    BigInt::BigInt(long  n){
        try {
            num[0] = n < 0 ? '9' : '0';
            n = n < 0 ? -n : n;
            int i = 10, k = 1;
            while (n / i > 0) {
                i *= 10;
                k++;
            }
            if (k > MaxLen)
                throw "Overflow";
            for (int l = 1; l <= MaxLen - k + 1; l++)
                num[l] = '0';
            for (int l = MaxLen; l >= MaxLen - k + 1; l--) {
                num[l] = (char)(((int)'0') + n % 10);
                n /= 10;
            }
        }
        catch (...) {
            std::cout << "Your value is bigger then MaxSize." << std::endl;
        }
    }
    

    BigInt::BigInt(const char* str){
        try {
            bool zero = true;
            int length = (int)strlen(str), z = 0;
            if (length > MaxLen)
                throw "Overflow";
            if (str[0] == '-') {
                num[0] = '9';
                z++;
                length--;
            }
            else num[0] = '0';
            if (length != strspn(str+ (num[0] == '9' ? 1 : 0), "0123456789"))
                throw "Data error!";
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
        catch (const char* n) {
          if (strcmp(n, "Overflow"))
                std::cout << "Too big number!" << std::endl;
            if (strcmp(n, "Data error!")) {
                std::cout << "The number should include only '-'at the begin and '0-9' chars." << std::endl;
                num[0] = '0';
            }
        }
        catch (...) {
            std::cout << "Nullptr" << std::endl;
        }
    }

    BigInt::BigInt(std::istream& i){
        Input(i);
    }

    BigInt::BigInt(const BigInt& orig) {
        for (int i = 0; i < MaxLen + 1; i++)
            num[i] = orig.num[i];
    }

    char* BigInt::Inverce(char* obr)const {
        bool sgn = num[0] == '0' ? false : true;
        bool pr = true;
        bool zero = true;
        obr[0] = num[0];
        for (int i = MaxLen;i > 0 ; i--) {
            if (sgn) {
                    if (pr) {
                        if (num[i] == '0') {
                            obr[i] = num[i];
                        }
                        else {
                            obr[i] = (char)10 - (num[i] - '0') + '0';
                            pr = false;
                            zero = false;
                        }
                    }
                    else
                    obr[i] = (char)9 - (num[i] - '0') + '0';
            }
            else obr[i] = num[i];
        }
        if (zero) obr[0] = '0';
        return obr;
    }

    char* BigInt::Inverce(char* num,int p)const {
        bool sgn = num[0] == '0' ? false : true;
        bool pr = true;
        bool zero = true;
        for (int i = MaxLen ; i > 0; i--) {
            if (sgn) {
                    if (pr&&num[i] != '0') {
                        num[i] = (char)10 - (num[i] - '0') + '0';
                        pr = false;
                        zero = false;
                    }
                    else if(!pr)
                        num[i] = (char)9 - (num[i] - '0') + '0';
            }
        }
        if (zero) num[0] = '0';
        return num;
    }

    std::istream& BigInt::Input(std::istream& i) {
        try {
            char n[MaxLen + 1];
            i >> n;
            bool zero = true;
            int length = (int)strlen(n), z = 0;
            if (length > MaxLen)
                throw "Overflow";
            if ((length - (n[0] == '-' ? 1 : 0)) != strspn(n + (n[0] == '-' ? 1 : 0), "0123456789"))
                throw "Data error!";
            if (n[0] == '-') {
                num[0] = '9';
                z++;
                length--;
            }
            else num[0] = '0';
            for (int k = 1;k <= MaxLen - length; k++) {
                num[k] = '0';
            }
            for (int k = MaxLen - length + 1;k <= MaxLen; k++) {
                num[k] = n[z];
                z++;
                if (zero && num[k] != '0')
                    zero = false;
            }
            if (zero)
                num[0] = '0';
        }
        catch (const char* n) {
            if (strcmp(n, "Overflow"))
                std::cout << "Too big number!" << std::endl;
            if (strcmp(n, "Data error!")) {
                std::cout << "The number should include only '-'at the begin and '0-9' chars." << std::endl;
            }
        }
        catch (...) {
            std::cout << "Nullptr" << std::endl;
        }
        return i;
    }

    std::ostream& BigInt::Output(std::ostream& c) const {
        if (num[0] == '9')
            c << "-";
        bool print = false;
        for (int i = 1; i <= MaxLen; i++) {
            if (!print && num[i] != '0')
                print = true;
            if (print)
                c << num[i];
        }
        if (!print)
            c << '0';
        c << std::endl;
        return c;
    }

    BigInt& BigInt::Add(const BigInt& BSlg,int sgn) {
        try {
            char slg1[MaxLen+1];
            bool prInd = ((num[0] == BSlg.num[0] && sgn == 0) || (num[0] != BSlg.num[0] && sgn != 0));
            Inverce(slg1);
            char slg2[MaxLen + 1];
            BSlg.Inverce(slg2);
            if (sgn != 0) {
                if (slg2[0] == '9') {
                    Inverce(slg2,0);
                    slg2[0] = '0';
                }
                else {
                    slg2[0] = '9';
                    Inverce(slg2,0);
                }
            }
            int pr = 0;
            for (int i = MaxLen; i >= 0; i--) {
                if (slg1[i] - '0' + slg2[i] - '0' + pr < 10) {
                    slg1[i] = (char)slg1[i] - '0' + slg2[i] - '0' + pr + '0';
                    pr = 0;
                }
                else {
                    slg1[i] = (char)slg1[i] - '0' + slg2[i] - '0' + pr + '0' - 10;
                    pr = 1;
                }
            }
            if (pr > 0 && prInd && slg1[1] == '0')
                throw - 1;
            Inverce(slg1,0);
            for (int i = 0;i <= MaxLen;i++)
                num[i] = slg1[i];
            return *this;
        }
        catch (...) {
            std::cout << "Overflow!!!" << std::endl;
            return *this;
        }
    }

    BigInt& BigInt::Mult10() {
        try {
            if (num[1] != '0')
                throw - 1;
            for (int i = 2; i < MaxLen; i++)
                num[i] = num[i + 1];
            num[MaxLen] = '0';
            return *this;
        }
        catch (...) {
            std::cout << "Overflow!!!!" << std::endl;
            return *this;
        }
    }

    BigInt& BigInt::Dev10() {
        bool zero = true;
        for (int i = MaxLen; i > 1; i--) {
            num[i] = num[i - 1];
            if(zero&&(num[i] != '0'|| num[i-1] != '0'))
                zero =false;
        }
        num[1] = '0';
        if (zero)
            num[0] = '0';
        return *this;
    }

}
