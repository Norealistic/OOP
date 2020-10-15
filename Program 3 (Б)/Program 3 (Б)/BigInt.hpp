#pragma once
#include <iostream>

namespace NS3 {
    class BigInt {
    private:
        static const int MaxLen = 47;
        char num[MaxLen + 1];
    public:
        BigInt();
        BigInt(std::istream& i) :BigInt(){
            i >> *this;
        };
        BigInt(long a);
        BigInt(int a);
        BigInt(const char* str);
        const BigInt operator ~ () const;
        friend std::istream& operator >> (std::istream& i,BigInt&);
        friend std::ostream& operator << (std::ostream& c, const BigInt&);
        friend BigInt operator +(const BigInt&, const BigInt&);
        const BigInt operator - () const;
        friend BigInt operator - (const BigInt& a, const BigInt& b){
            return a + (-b);
        };
        const BigInt operator * (const int&);
        const BigInt operator / (const int&);
    };
}
