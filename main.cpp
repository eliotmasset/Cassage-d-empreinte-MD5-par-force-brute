#include <iostream>
#include <chrono>

typedef std::chrono::_V2::steady_clock::time_point timePoint;

void  execute(timePoint * start,timePoint * end, std::string programme)
{
    std::string param1;
    std::string nbProc;

    std::cout << "Compilation en cours... " << std::endl;

    try{
    system(("$PWD/../aide" + programme +".sh").c_str());}
    catch(std::exception const& e)
    {std::cerr << "Erreur : " << e.what() << std::endl;}

    system("clear");

    std::cout << "Veuillez renseigner une chaine de caractère : " << std::endl;
    std::cin >> param1;
    if(programme=="MultiThread")
    {
        std::cout << "Veuillez renseigner le nombre de processeurs à utiliser : " << std::endl;
        std::cin >> nbProc;
    }

    system("clear");

    *start = std::chrono::steady_clock::now();
    system(("./" + programme +" " + param1 + " " + nbProc).c_str());
    *end = std::chrono::steady_clock::now();
}

int main() {
    char selection;
    std::chrono::_V2::steady_clock::time_point start, end;
    std::cout << "Qu'elle methode voulez vous utiliser ? ( s : Sequentiel / m : MultiThread)" << std::endl;
    std::cin >> selection;

    switch (selection) {
        case 's':
            execute(&start, &end, "Sequentielle");
            break;
        case 'm':
            execute(&start, &end, "MultiThread");
            break;
        default :
            return 0;
            break;
    }

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Le programme a duré : " << elapsed_seconds.count() << " secondes" << std::endl;
    return 0;
}

