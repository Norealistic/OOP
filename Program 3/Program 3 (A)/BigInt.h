#pragma once
#include <iostream>

namespace NS3 {
    class BigInt {
        
    private:
        static const int MaxLen = 3;
        char num[MaxLen+1];
        char* Inverce(char*, int) const;
        char* Inverce(char*) const;
        
    public:
        BigInt();
        BigInt(std::istream&);
        BigInt(long num);
        BigInt(int num);
        BigInt(const char* );
        BigInt(const BigInt&);
        std::istream& Input(std::istream& i = std::cin);
        std::ostream& Output(std::ostream& c = std::cout) const;
        BigInt& Add(const BigInt&, int sgn = 0);
        BigInt& Sub(const BigInt& num){
            return Add(num, 1);
        };
        BigInt& Mult10();
        BigInt& Dev10();
    };

}
