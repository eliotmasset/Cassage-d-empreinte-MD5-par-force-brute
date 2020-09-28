#!/bin/bash
crypt="cryptopp"

if [ -e "${crypt}/libcryptopp.a" ]
then 
	echo "Cryptocpp est déja compilée"
else
	echo "Verification de la connexion internet"
	wget -q --spider http://google.com

	if [ $? -eq 0 ]; then
    		echo "Online"
	else
   	 echo "Offline"
	fi
	echo "Extraction librairie"
fi	
