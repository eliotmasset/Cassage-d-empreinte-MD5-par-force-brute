#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>

typedef std::chrono::_V2::steady_clock::time_point timePoint;

void sequentielle(timePoint * start,timePoint * end)
{
    std::string param1;

    std::cout << "Compilation en cours... " << std::endl;

    try{
    system("$PWD/aideSequentielle.sh");}
    catch(std::exception const& e)
    {std::cerr << "Erreur : " << e.what() << std::endl;}

    system("clear");

    std::cout << "Veuillez renseigner une chaine de caractère : " << std::endl;
    std::cin >> param1;

    system("clear");

    *start = std::chrono::steady_clock::now();
    system(("./sequentielle " + param1).c_str());
    *end = std::chrono::steady_clock::now();
}

void  multiThread(timePoint * start,timePoint * end)
{
    std::string param1;
    std::string nbProc;

    std::cout << "Compilation en cours... " << std::endl;

    try{
    system("$PWD/aideMultiThread.sh");}
    catch(std::exception const& e)
    {std::cerr << "Erreur : " << e.what() << std::endl;}

    system("clear");

    std::cout << "Veuillez renseigner une chaine de caractère : " << std::endl;
    std::cin >> param1;
    std::cout << "Veuillez renseigner le nombre de processeurs à utiliser : " << std::endl;
    std::cin >> nbProc;

    system("clear");

    *start = std::chrono::steady_clock::now();
    system(("./multithread " + param1 + " " + nbProc).c_str());
    *end = std::chrono::steady_clock::now();
}

int main() {
    char selection;
    std::chrono::_V2::steady_clock::time_point start, end;
    std::cout << "Qu'elle methode voulez vous utiliser ? (Sequentiel / MultiThread)" << std::endl;
    std::cin >> selection;

    switch (selection) {
        case 's':
            sequentielle(&start, &end);
            break;
        case 'm':
            multiThread(&start, &end);
            break;
        default :
            return 0;
            break;
    }
    
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Le programme a duré : " << elapsed_seconds.count() << " secondes" << std::endl;
    return 0;
}

