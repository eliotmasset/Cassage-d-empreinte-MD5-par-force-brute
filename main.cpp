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

void FindMD5Recursive(std::string md5,std::string msg="a",  size_t pos=0)
{
	if(md5==toMD5(msg) || pos==10)
	{
		std::cout << " 111: " << msg << std::endl;
		sleep(2);
		return;
	}
	else
	{
			if(msg[pos]=='z')
			{
				if(pos==0)
				{
					msg[pos]='a';
					pos=msg.size();
					msg+='a';
					std::cout << " 1: " << msg << " " << pos << std::endl;
				}
				else
				{
					msg[pos]='a';
					std::cout << " 2: " << msg << " " << pos << std::endl;
					pos--;
				}
					
			}
			else if(pos!=msg.size()-1)
			{
				msg[pos]++;
				pos++;
			}
			else
			{
				msg[pos]++;
				std::cout << " 1a: " << msg << " " << pos << std::endl;
			}
	}
	FindMD5Recursive(md5,msg, pos);
}

int main(int argc, char *argv[]){
	
	if(argc==2)
	{
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);
		
		//Facultatif :
		std::cout << "Message: " << msg << std::endl;
		std::cout << "Digest: " ;
		CryptoPP::StringSource(md5msg, true, new CryptoPP::Redirector(encoder));
		std::cout << std::endl;
		//;
		
		FindMD5Recursive(md5msg);
		
		std::cout << "Trouvé ! "; 
		
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
