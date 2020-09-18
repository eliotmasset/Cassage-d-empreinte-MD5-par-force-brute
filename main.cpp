#include <iostream>
#include <cstddef>

#ifndef CRYPTOPP_ENABLE_NAMESPACE_WEAK
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif
#include "cryptopp/dll.h"
#include "cryptopp/default.h"
#include "cryptopp/md5.h"
#include "cryptopp/hex.h"

int main(int argc, char *argv[]){
	std::cout << "Allocation failed: ";
	CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
	
	if(argc==2)
	{
		std::cout << "Allocation failed: ";
		using namespace CryptoPP;
		typedef unsigned char byte;
		HexEncoder encoder(new FileSink(std::cout));
		std::string md5=argv[1];
	}
	else
		std::cerr << "Erreur : nombre d'arguments non valide " << std::endl;
	
	return 0;
}
