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

void FindMD5(std::string md5,std::string msg="a",  size_t pos=0)
{
	
	while(md5!=toMD5(msg) && pos!=10)
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
				msg[pos--]='a';
				std::cout << " 2: " << msg << " " << pos << std::endl;
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
			std::cout << " 1a: " << msg << " " << pos << std::endl;
		}
	}
}

int main(int argc, char *argv[]){
	
	if(argc==2)
	{
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);
		
		FindMD5(md5msg);
		
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
