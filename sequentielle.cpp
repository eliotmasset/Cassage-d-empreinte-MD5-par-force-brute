#include <iostream>
#include <cstddef>
#include <unistd.h>

#ifndef CRYPTOPP_ENABLE_NAMESPACE_WEAK
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif
#include "cryptopp/dll.h"
#include "cryptopp/default.h"
#include "cryptopp/md5.h"
#include "cryptopp/hex.h"

std::string toMD5(std::string &_msg)
{
	std::string digest;
	CryptoPP::Weak::MD5 hash;
	hash.Update((const CryptoPP::byte*)_msg.data(), _msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);
	
	return digest;
}

std::string FindTextMD5(std::string md5)
{
	std::cout << "Recherche de l'empreinte md5 :" << std::endl;
	std::cout << "Attention cette opération peut prendre du temps" << std::endl;
	size_t pos=0;
	std::string msg="a";
	while(md5!=toMD5(msg))
	{
		if(msg[pos]=='a')
		{
			if(pos==0)
			{
				msg[pos]='a';
				pos=msg.size()-1;
				msg+='a';
			}
			else
			{
				msg[pos--]='a';
			}
					
		}
		else if(pos!=msg.size()-1)
		{
			msg[pos]++;
			pos=msg.size()-1;
		}
		else
		{
			msg[pos]++;
		}
	}
	return msg;
}

int main(int argc, char *argv[]){
	
	if(argc==2)
	{
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);
		std::string findMsg = FindTextMD5(md5msg);
		
		std::cout << "L'empreinte md5 : \"" ;
		CryptoPP::StringSource(md5msg, true, new CryptoPP::Redirector(encoder));
		std::cout << "\" est associée à la chaine : \"" << findMsg << "\"." << std::endl;
		
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
