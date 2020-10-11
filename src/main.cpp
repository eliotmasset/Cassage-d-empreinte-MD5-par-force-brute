#include <iostream>
#include <chrono>

//remplace  std::chrono::_V2::steady_clock::time_point par timePoint
typedef std::chrono::_V2::steady_clock::time_point timePoint;

//Fonction qui execute un programme
void  execute(timePoint * start,timePoint * end, std::string programme)
{
    // Créer 2 chaine de caractère (le parmaètre et le nombre de processus) :
    std::string param1;
    std::string nbProc;

    //efface l'écran de la console
    system("clear");

    std::cout << "Veuillez renseigner une chaine de caractère : " << std::endl;
    std::cin >> param1;
    if(programme=="MultiThread")           // Si la chaine de caractère programme est MultiThread :
    {
        std::cout << "Veuillez renseigner le nombre de processeurs à utiliser : " << std::endl;
        std::cin >> nbProc;
    }

    //efface l'écran de la console
    system("clear");

    // On donne une valeur temporelle aux deux points temporels et on lance le programme souhaité
    *start = std::chrono::steady_clock::now();
    system(("./" + programme +" " + param1 + " " + nbProc).c_str());
    *end = std::chrono::steady_clock::now();
}

//Fonction principal
int main() {
    // créer un caractère et deux points temporels :
    char selection;
    std::chrono::_V2::steady_clock::time_point start, end;
    std::cout << "Quelle methode voulez-vous utiliser ? ( s : Sequentiel / m : MultiThread)" << std::endl;
    std::cin >> selection;

    switch (selection) { // Celon le caractère de selection :
        case 's':             // Si il est égale à 's' :
            execute(&start, &end, "Sequentielle");    //on execture le sequantielle.cpp
            break;
        case 'm':             // Si il est égale à 'm' :
            execute(&start, &end, "MultiThread");     //on execture le multithread.cpp
            break;
        default :             // Si il est égale à un autre caractère :
            return 0;                                 //on finis le programme
            break;
    }

    // Calcul et affichage de la duree entre les deux points temporels :
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Le programme a duré : " << elapsed_seconds.count() << " secondes" << std::endl;
    // fin du programme
    return 0;
}

