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
std::string FindTextMD5(std::string md5)
{
	//Créer une position et une chaine de caractère :
	size_t pos=0;
	std::string msg="a";
	
	while(md5!=toMD5(msg))              //Tant que l'empreinte md5 ne correspond pas à la chaine :
	{
		if(msg[pos]=='z')                   // Si le caractère à la position pos est égale à z :
		{
			if(pos==0)                          // Si la position est égale à 0 :
			{
				//réinitialise la chaine et rajoute un caractère :
				msg[pos]='a';
				msg+='a';
                pos=msg.size()-1;
			}
			else                                // Sinon :
			{
				//on change la lettre à la position actuelle par un a et désincrémente ensuite la position :
				msg[pos--]='a';
			}
					
		}
		else if(pos!=msg.size()-1)          // Sinon Si la position n'est pas à la fin de la chaine : 
		{
			//incrémente la lettre à la position actuelle et met la position à la fin de la chaine :
			msg[pos]++;
			pos=msg.size()-1;
		}
		else                                // Sinon :
		{ 
			//incrémente la lettre à la position :
			msg[pos]++;
		}
	}
	//retourne le message :
	return msg;
}

//Fonction principal
int main(int argc, char *argv[]){
	
	if(argc==2)                        // Si le nombre de paramètres est de 1 :
	{
		//création d'un encoder, de la chaine à trouver et de son empreinte md5 : 
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);

		std::cout << "Recherche de l'empreinte md5 :" << std::endl;
		std::cout << "Attention cette opération peut prendre du temps" << std::endl;
		
		//cherche la chaine associé à l'empreinte md5 :
		std::string findMsg = FindTextMD5(md5msg);
		
		std::cout << "L'empreinte md5 : \"" ;
		//affiche la chaine trouvé :
		CryptoPP::StringSource(md5msg, true, new CryptoPP::Redirector(encoder));
		std::cout << "\" est associée à la chaine : \"" << findMsg << "\"." << std::endl;
		
	}
	else                               // Sinon, le nombre d'arguments est invalide :
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	//fin du programme :
	return 0;
}
