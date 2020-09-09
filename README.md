# Cassage-d-empreinte-MD5-par-force-brute
Cassage d'empreinte MD5 par force brute de Eliot Masset et Matteo Munoz.

Sujet :

Le hashage est un bon moyen de stocker une clé (mot de passe, empreinte d'un fichier ou d'un répertoire...). On utilisera la bibliothèque cryptocpp, mise à jour régulièrement, multi-algorithmes et multi-plateformes (https://www.cryptopp.com/). Le hashage n'est pas réversible et le moyen de retrouver la chaîne initiale ayant créée le hashage est de tester les unes après les autres des combinaisons de lettres, chiffres, symboles - c'est l'attaque brute-force (https://fr.wikipedia.org/wiki/Attaque_par_force_brute). À partir d'une empreinte connue (chaîne plus ou moins complexe obtenue par la même bibliothèque), on lancera plusieurs tâches d'attaque en force-brute.
