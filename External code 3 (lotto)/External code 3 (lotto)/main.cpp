#include "LPFHeader.h"

using namespace LottoSpace;
using namespace LPF;

int main() {
    int (*dp[5])(std::vector<Lotto>&) = { P_Exit, P_NewCard, P_Show, P_Place, play };
    std::vector<Lotto> cards;
    cards.resize(1);
    int a;
    do {
        while (1) {
            std::cout << dialog();
            std::cin >> a;
            if (!std::cin.good() || a < 0 || a > 4) {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout << "Incorrect input!" << std::endl;
                sleep(5);
            }
            else
                break;
        }
    } while (dp[a](cards));
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
