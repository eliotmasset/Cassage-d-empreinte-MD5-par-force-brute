#include <iostream>
#include <cstddef>

#ifndef CRYPTOPP_ENABLE_NAMESPACE_WEAK
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif
#include "cryptopp/dll.h"
#include "cryptopp/default.h"
#include "cryptopp/md5.h"
#include "cryptopp/hex.h"


std::string toMD5(std::string _msg)
{
	CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
	std::string digest;
	CryptoPP::Weak::MD5 hash;
	hash.Update((const CryptoPP::byte*)_msg.data(), _msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);
	
	std::cout << "Digest: " << digest << std::endl;
	
	return digest;
}

int main(int argc, char *argv[]){
	
	if(argc==2)
	{
		
		std::string msg = argv[1];
		std::string md5msg = toMD5(msg);

		std::cout << "Message: " << msg << std::endl;
		std::cout << "Digest: " << md5msg << std::endl;
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
