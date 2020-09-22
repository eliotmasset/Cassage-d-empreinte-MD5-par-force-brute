#include <iostream>
#include <cstddef>
#include <unistd.h>

int main() {
    char selection;
    std::cout << "Qu'elle methode voulez vous utiliser ? (Sequentiel / MultiThread)";
    std::cin >> selection;
    switch (selection) {
        case 's':
            break;
        case 'm':
            break;
    }
}

