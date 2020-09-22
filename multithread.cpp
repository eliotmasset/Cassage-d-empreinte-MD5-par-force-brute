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

struct paramThread_FindTextMD5
{
	std::string md5;
	char minC;
	char maxC;
};

std::string toMD5(std::string &_msg)
{
	std::string digest;
	CryptoPP::Weak::MD5 hash;
	hash.Update((const CryptoPP::byte*)_msg.data(), _msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);
	
	return digest;
}

std::string FindTextMD5(void* p_struct)
{
	struct paramThread_FindTextMD5 *param = (struct paramThread_FindTextMD5 *)p_struct;
	size_t pos=0;
	std::string msg="";
	msg+=param->minC;
	while(param->md5!=toMD5(msg))
	{
		if(msg[pos]==param->maxC)
		{
			if(pos==0)
			{
				msg[pos]=param->minC;
				pos=msg.size()-1;
				msg+=param->minC;
			}
			else
				msg[pos--]=param->minC;
					
		}
		else if(pos!=msg.size()-1)
		{
			msg[pos]++;
			pos=msg.size()-1;
		}
		else
			msg[pos]++;
	}
	return msg;
}

int main(int argc, char *argv[]){
	if(argc==3)
	{
		try
		{
			if(atoi(argv[2])<=0)
			{
				std::cerr << "Erreur : nombre de processeurs invalide " << std::endl;
				return 0;
			}
		}
		catch(std::exception const& e)
		{
			std::cerr << "Erreur : " << e.what() << std::endl;
		}
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);
		
		paramThread_FindTextMD5 param;
		param.md5=md5msg;
		param.minC='a';
		param.maxC='z';
		
		std::cout << "Recherche de l'empreinte md5 :" << std::endl;
		std::cout << "Attention cette opération peut prendre du temps" << std::endl;
		
		std::string findMsg = FindTextMD5((void*)&param);
		
		
		std::cout << "L'empreinte md5 : \"" ;
		CryptoPP::StringSource(md5msg, true, new CryptoPP::Redirector(encoder));
		std::cout << "\" est associée à la chaine : \"" << findMsg << "\"." << std::endl;
		
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
