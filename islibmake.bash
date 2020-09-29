#!/bin/bash
crypt="cryptopp"

if [ -e "${crypt}/libcryptopp.a" ]
then 
	echo "Cryptocpp est déja compilée"
else
	echo "Verification de la connexion internet"
	wget -q --spider http://google.com

	if [ $? -eq 0 ]; then
    		read -p "Voulez vous télécharger la librairie (besoin de git) (y/n)?" CONT
		if [ "$CONT" = "y" ]; then
 			
			dpkg -s git &> /dev/null
			if [ $? -eq 0 ]; then
			  echo "Téléchargement et compilation de la librairie"
    				git clone https://github.com/weidai11/cryptopp.git && cd cryptopp && make
			else
    				echo "Vous devez avoir le package git"
			fi
		else
 			 echo "Pour télécharger la librairie sans git référez vous à la doc";
		fi

	else
   	 echo "Offline"
	fi
	echo "Extraction librairie"
fi	
