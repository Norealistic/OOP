#include <iostream>
#include "BigInt.hpp"
using namespace NS3;
using namespace std;
    int main(){
        int n = 1;
        cout << "0.Exit\n1.Addition\n2.Subtraction\n3.Negative number\n4.Multiply by 10\n5.Divide by 10"<<std::endl;
        while (n != 0) {
            cout << "Choose the option:\n";
            cin >> n;
            switch (n)
            {
                case    1: {
                    BigInt* A = new BigInt;
                    BigInt* B = new BigInt;
                    cout << "Enter the 1 number:" << endl;
                    cin >> *A;
                    cout << "Enter the 2 number:" << endl;
                    cin >> *B;
                    cout << "The result:" << endl;
                    cout << *A + *B;
                    delete A;
                    delete B;
                    break;
                }
                case 2: {
                    BigInt* A = new BigInt;
                    BigInt* B = new BigInt;
                    cout << "Enter the 1 number:" << endl;
                    cin >> *A;
                    cout << "Enter the 2 number:" << endl;
                    cin >> *B;
                    cout << "The result:" << endl;
                    cout << *A - *B;
                    delete A;
                    delete B;
                    break;
                }
                case 3: {
                    BigInt* A = new BigInt;
                    cout << "Enter the number:" << endl;
                    cin >> *A;
                    cout << "The result:" << endl;
                    cout << -*A;
                    delete A;
                    break;
                }
                case 4: {
                    BigInt* A = new BigInt;
                    cout << "Enter the number:" << endl;
                    cin >> *A;
                    cout << "The result:" << endl;
                    cout << *A * 10;
                    delete A;
                    break;
                }
                case 5: {
                    BigInt* A = new BigInt;
                    cout << "Enter the number:" << endl;
                    cin >> *A;
                    cout << "The result:" << endl;
                    cout << *A / 10;
                    delete A;
                    break;
                }
            }
        }


}
