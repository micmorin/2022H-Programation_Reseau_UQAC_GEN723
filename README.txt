


Laboratoire Final :
Projet de Conception sur la communication réseau 

Michael Munger - MUNM07039500
Departement d'Informatique et Mathématique
Université du Québec à Chicoutimi
6GEN723 : Réseau d'Ordinateur
Professeur : Louis-André Guérin
22 Avril 2021








Projet de Conception sur la communication réseau 

Débuter le Programme
 1.	Le programme utilise Visual Studio (2022) et c++20. Le projet devrait déjà être prêt à 
utiliser en utilisant 'Déboguer'. 
 a)	Pour vérifier que la version c++20 est utilisée, clic droit sur le projet > Proprietes > 
General > norme du language c++. Pour cette verification, il faut l'effectuer, au 
besoin, sur les deux projets :Final Reseau Client et Final Reseau Serveur.
 b)	Pour verifier le sous-systeme du projet Final Reseau Serveur, clic droit sur le projet 
> Proprietes > Editeur dde liens > Systeme > Sous-Systeme.
 c)	Pour verifier que tous le Serveur ET le client ouvrent en même temps, clic droit sur 
la SOLUTION > Proprietes > Plusieurs Projet de Démarage > les deux projets sont 
à Démarré.
 2.	L'addresse du serveur se trouve dans le fichier Socket.h dnas la definition 
IPSERVEUR. Par default, elle est a 127.0.0.1.

Instructions
*	DIR, MD, RD, DEL, COPY, SHUTDOWN : syntaxe d'origine pour les commandes
*	CD: cd (destination relative ou absolue)
*	FILE_TO_SERVER:  file_to_server (chemin_client relative ou absolue) (chemin_serveur 
relative ou absolue)
*	FILE_TO_CLIENT:  file_to_client (chemin_serveur relative ou absolue) (chemin_client 
relative ou absolue)
*	CLOSE : ferme le client

Demarche et version future
	Bien que l'utilisation de la librairie Boost/Asio fût longement étudié, la note du lab 3 
suggéra que ce lab serait une bonne base de départ. La première découverte fût l'utilisation 
d'un différent sous-système pour ne pas montrer la console du serveur. Un temps important 
fût ensuit utilisé pour que le serveur soit accessible par internet mais la solution prinicpale,  le 
port forwarding, était trop compliqué à mettre en œuvre. Le ShellExecute fût la première 
fonction testé, puis CreateProcess avant de finir avec ShellExecuteEx pour les commandes 
natives. Bien que la plus grande partie de mon temps fût passé à déboguer, la plupart des 
fonctions du lab 3 ont été retouché et améliorées pour ce lab final. Une touche particuli;ère à 
été apporté à la vérification côté client.
	Dans une itération future, le logiciel serait accessible par Internet, l'addresse IP du 
serveur serait communiqué à un forum en ligne pour être récupéré par l'attaquant et toutes 
les commandes natives seraient disponible pour le client.

Ressources utilisées
*	La documentations de la librairie filesystem, ShellExecuteEX ainsi que celle des 
autres fonctions, librairies et classes utilisées.
*	https://stackoverflow.com/questions/318236/how-do-you-validate-that-a-string-
is-a-valid-ipv4-address-in-c
*	https://www.codeproject.com/Articles/1842/A-newbie-s-elementary-guide-to-
spawning-processes
*	https://stackoverflow.com/questions/48437377/cmd-commands-in-shellexecute
*	https://stackoverflow.com/questions/12402549/check-if-socket-is-connected-or-
not
*	https://stackoverflow.com/questions/1283721/disable-showing-console-window




































































































































































































PROJET DE CONCEPTION SUR LA COMMUNICATION RÉSEAU 	1





PROJET DE CONCEPTION SUR LA COMMUNICATION RÉSEAU 	1




