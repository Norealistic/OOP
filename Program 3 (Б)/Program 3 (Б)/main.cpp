#include <iostream>
#include "BigInt.hpp"
#include <util.h>

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
                    try{
                    cout << "Enter the 1 number:" << endl;
                    cin >> *A;
                    cout << "Enter the 2 number:" << endl;
                    cin >> *B;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    cout << "The result:" << endl;
                    try{
                    cout << *A + *B;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    delete A;
                    delete B;
                    break;
                }
                case 2: {
                    BigInt* A = new BigInt;
                    BigInt* B = new BigInt;
                    try{
                    cout << "Enter the 1 number:" << endl;
                    cin >> *A;
                    cout << "Enter the 2 number:" << endl;
                    cin >> *B;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    cout << "The result:" << endl;
                    try{
                    cout << *A - *B;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    delete A;
                    delete B;
                    break;
                }
                case 3: {
                    BigInt* A = new BigInt;
                    try{
                    cout << "Enter the number:" << endl;
                    cin >> *A;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    cout << "The result:" << endl;
                    try{
                    cout << -*A;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    delete A;
                    break;
                }
                case 4: {
                    BigInt* A = new BigInt;
                    try{
                    cout << "Enter the number:" << endl;
                    cin >> *A;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    cout << "The result:" << endl;
                    try{
                    cout << *A * 10;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    delete A;
                    break;
                }
                case 5: {
                    BigInt* A = new BigInt;
                    try{
                    cout << "Enter the number:" << endl;
                    cin >> *A;
                    }
                    catch (const std::out_of_range& err) {
                        std::cout << err.what() << std::endl;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    cout << "The result:" << endl;
                    try{
                    cout << *A / 10;
                    }
                    catch (const std::invalid_argument& err){
                        std::cout << err.what() << std::endl;
                    }
                    delete A;
                    break;
                }
            }
        }
}
