#include <iostream>

#include "Strophoid.h"
#include "Dialog.h"
#include "util.h"

using namespace NS2;

int main() {
    try {
        Strophoid strophoid;
        Dialog(strophoid);
    }
    catch (std::bad_alloc &ba) {
        std::cout << "Error in allocating memory: " << ba.what() << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << "Exception detected: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error occured!" << std::endl;
    }
    return 0;
}
