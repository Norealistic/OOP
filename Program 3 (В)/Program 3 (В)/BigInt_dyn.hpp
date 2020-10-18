#pragma once
#include <iostream>

namespace NS3 {
    class BigInt {
        
    private:
        static const int MaxLen = 47;
        int len;
        char* num;
        BigInt(const char*, int&);
        BigInt(const BigInt& orig, int);
        BigInt(int, int);
        void correction();

    public:
        BigInt();
        BigInt(std::istream& i) :BigInt(){
            i >> *this;
        };
        explicit BigInt(long a);
        BigInt(int a);
        BigInt(const char* str);
        BigInt(BigInt&& orig): len(orig.len), num(orig.num){   //перемещающий конструктор
            orig.num = nullptr;
        }
        BigInt(const BigInt&); //копирующий конструктор
        
        const BigInt operator ~ () const;

        friend std::istream& operator >> (std::istream& i, BigInt&);
        friend std::ostream& operator << (std::ostream& c, const BigInt&);
        friend BigInt operator + (const BigInt&, const BigInt&);
        const BigInt operator - () const;
        friend BigInt operator - (const BigInt& a, const BigInt& b){
            return a + (-b);
        };
        const BigInt operator * (const int&);
        const BigInt operator / (const int&);

        BigInt& operator = (const BigInt&); //перегруж оператор присваивания
        BigInt& operator = (BigInt&&); //перемещающий оператор присваивания
        explicit operator int() const;
        ~BigInt() {
            delete[]num;
        }
        
    };
}
