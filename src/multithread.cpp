#include <iostream>
#include <cstddef>
#include <unistd.h>

#ifndef CRYPTOPP_ENABLE_NAMESPACE_WEAK
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif
#include "../cryptopp/dll.h"
#include "../cryptopp/default.h"
#include "../cryptopp/md5.h"
#include "../cryptopp/hex.h"

bool estTrouve = false;
std::string resultat="";

struct paramThread_FindTextMD5 //structure qui stocke les paramètre de thread
{
	std::string md5;
	char minC;
	char maxC;
};

//Fonction qui renvoie l'empreinte md5 d'un string
std::string toMD5(std::string &_msg)
{
	//Créer une empreinte MD5 grâce à crypto++ :
	std::string digest;
	CryptoPP::Weak::MD5 hash;
	hash.Update((const CryptoPP::byte*)_msg.data(), _msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);
	
	//retourne l'empreinte MD5 :
	return digest;
}

//Fonction qui renvoie la chaine de caractère associé à l'empreinte md5
void* FindTextMD5(void* p_struct)
{
	//Créer un pointeur sur une structure de paramètre, une position et une chaine de caractère :
	struct paramThread_FindTextMD5 *param = (struct paramThread_FindTextMD5 *)p_struct;
	size_t pos=0;
	std::string msg="";
	//la chaine de caractère commence au caractère minC
	msg+=param->minC;
	while(param->md5!=toMD5(msg) && estTrouve==false)              //Tant que l'empreinte md5 ne correspond pas à la chaine et que aucun thread n'a trouvé la chaine :
	{
		if(msg[pos]=='z' && pos!=0)                                    //Si le caractère à la position est un 'z' et que la position n'est pas 0 :
		{
			//le caractère à la position devient un 'a' et la position se désincrémente
			msg[pos--]='a';		
		}
		else if(msg[pos]==param->maxC && pos==0)                       //Sinon Si le caractère à la position atteint le caractère max et que cette position est 0 :
		{
			//on passe le caractère à minC, on rajoute un 'a' à la chaine et on met la position à la fin
			msg[pos]=param->minC;
			msg+='a';
            pos=msg.size()-1;
		}
		else if(pos!=msg.size()-1)                                     //Sinon Si la position n'est pas à la fin :
		{
			//on incrémente le caractère à la position et on met la position à la fin
			msg[pos]++;
			pos=msg.size()-1;
		}
		else                                                           //Sinon, on incrémente le caractère à la position :
			msg[pos]++;
	}
	if(estTrouve==false) //Si, une fois la sortie de la boucle, le boolean est Trouve est égale à false, alors on met la chaine de caractère dans le resultat :
	{
		resultat=msg;
		estTrouve=true; //estTrouve devient true
	}
	//on ne retourne rien
	return NULL;
}

//Fonction principal
int main(int argc, char *argv[]){
	if(argc==3)                          // Si le nombre de paramètres est de 2 :
	{
		try                                  //on essaye :
		{
			if(atoi(argv[2])<=0)                 // Si l'argument 2 est plus petit ou égale à 0 : 
			{
				std::cerr << "Erreur : nombre de processeurs invalide " << std::endl;
				return 0;
			}
		}
		catch(std::exception const& e)       // Si sa ne réussis pas :
		{
			std::cerr << "Erreur : " << e.what() << std::endl;
		}
		
		//création d'un encoder, de la chaine à trouver, de son empreinte md5 et du nombre de processus : 
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);
		size_t nbProc = atoi(argv[2]);

		//création d'un tableau de nbProc thread, et d'un tableau de structure param
		pthread_t t[nbProc];
		paramThread_FindTextMD5 param[nbProc];
		
		
		for(size_t i=0;i<nbProc;i++)                //Pour i allant de 0 à nbProc :
		{
			// on initialise les paramètres :
			param[i].md5=md5msg;
			param[i].minC='a'+(26/nbProc)*i;
			if(i+1==nbProc)                             // Si on arrive à la dernière boucle :
				param[i].maxC='a'+(26/nbProc)*(i+1)-1+(26%nbProc);           // on rajoute le reste de la division de 26 par nbProc
			else                                        // Sinon
				param[i].maxC='a'+(26/nbProc)*(i+1)-1;                       // on initialise le caractère max
		}
		
		
		std::cout << "Recherche de l'empreinte md5 :" << std::endl;
		std::cout << "Attention cette opération peut prendre du temps" << std::endl;
		
		
		for(size_t i=0;i<nbProc;i++) // Pour i allant de 0 à nbProc :
		{
			pthread_create(&t[i], NULL, FindTextMD5,(void*)&param[i]); // On crée des thread :
		}
		for(size_t i=0;i<nbProc;i++) // Pour i allant de 0 à nbProc :
		{
			pthread_join(t[i],NULL);                                   // On join des thread
		}
		
		//affiche la chaine trouvé :
		std::cout << "L'empreinte md5 : \"" ;
		CryptoPP::StringSource(md5msg, true, new CryptoPP::Redirector(encoder));
		std::cout << "\" est associée à la chaine : \"" << resultat << "\"." << std::endl;
		
	}
	else                               // Sinon, le nombre d'arguments est invalide :
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	//fin du programme :
	return 0;
}
