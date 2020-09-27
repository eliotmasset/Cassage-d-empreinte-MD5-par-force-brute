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

bool estTrouve = false;
std::string resultat="";

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

void* FindTextMD5(void* p_struct)
{
	struct paramThread_FindTextMD5 *param = (struct paramThread_FindTextMD5 *)p_struct;
	size_t pos=0;
	std::string msg="";
	msg+=param->minC;
	while(param->md5!=toMD5(msg) && !estTrouve)
	{
		if(msg[pos]=='z' && pos!=0)
		{
			msg[pos--]='a';		
		}
		else if(msg[pos]==param->maxC && pos==0)
		{
			msg[pos]=param->minC;
			pos=msg.size()-1;
			msg+='a';
		}
		else if(pos!=msg.size()-1)
		{
			msg[pos]++;
			pos=msg.size()-1;
		}
		else
			msg[pos]++;
	}
	if(!estTrouve)
		resultat=msg;
	estTrouve=true;
	return NULL;
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
		size_t nbProc = atoi(argv[2]);
		pthread_t t[nbProc];
		paramThread_FindTextMD5 param[nbProc];
		
		
		for(size_t i=0;i<nbProc;i++)
		{
			param[i].md5=md5msg;
			param[i].minC='a'+(26/nbProc)*i;
			if(i+1==nbProc)
				param[i].maxC='a'+(26/nbProc)*(i+1)-1+(26%nbProc);
			else
				param[i].maxC='a'+(26/nbProc)*(i+1)-1;
		}
		
		
		std::cout << "Recherche de l'empreinte md5 :" << std::endl;
		std::cout << "Attention cette opération peut prendre du temps" << std::endl;
		
		
		for(size_t i=0;i<nbProc;i++)
		{
			pthread_create(&t[i], NULL, FindTextMD5,(void*)&param[i]);
		}
		for(size_t i=0;i<nbProc;i++)
		{
			pthread_join(t[i],NULL);
		}
		
		
		std::cout << "L'empreinte md5 : \"" ;
		CryptoPP::StringSource(md5msg, true, new CryptoPP::Redirector(encoder));
		std::cout << "\" est associée à la chaine : \"" << resultat << "\"." << std::endl;
		
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
