


Laboratoire Final :
Projet de Conception sur la communication r�seau 

Michael Munger - MUNM07039500
Departement d'Informatique et Math�matique
Universit� du Qu�bec � Chicoutimi
6GEN723 : R�seau d'Ordinateur
Professeur : Louis-Andr� Gu�rin
22 Avril 2021








Projet de Conception sur la communication r�seau 

D�buter le Programme
 1.	Le programme utilise Visual Studio (2022) et c++20. Le projet devrait d�j� �tre pr�t � 
utiliser en utilisant 'D�boguer'. 
 a)	Pour v�rifier que la version c++20 est utilis�e, clic droit sur le projet > Proprietes > 
General > norme du language c++. Pour cette verification, il faut l'effectuer, au 
besoin, sur les deux projets :Final Reseau Client et Final Reseau Serveur.
 b)	Pour verifier le sous-systeme du projet Final Reseau Serveur, clic droit sur le projet 
> Proprietes > Editeur dde liens > Systeme > Sous-Systeme.
 c)	Pour verifier que tous le Serveur ET le client ouvrent en m�me temps, clic droit sur 
la SOLUTION > Proprietes > Plusieurs Projet de D�marage > les deux projets sont 
� D�marr�.
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
	Bien que l'utilisation de la librairie Boost/Asio f�t longement �tudi�, la note du lab 3 
sugg�ra que ce lab serait une bonne base de d�part. La premi�re d�couverte f�t l'utilisation 
d'un diff�rent sous-syst�me pour ne pas montrer la console du serveur. Un temps important 
f�t ensuit utilis� pour que le serveur soit accessible par internet mais la solution prinicpale,  le 
port forwarding, �tait trop compliqu� � mettre en �uvre. Le ShellExecute f�t la premi�re 
fonction test�, puis CreateProcess avant de finir avec ShellExecuteEx pour les commandes 
natives. Bien que la plus grande partie de mon temps f�t pass� � d�boguer, la plupart des 
fonctions du lab 3 ont �t� retouch� et am�lior�es pour ce lab final. Une touche particuli;�re � 
�t� apport� � la v�rification c�t� client.
	Dans une it�ration future, le logiciel serait accessible par Internet, l'addresse IP du 
serveur serait communiqu� � un forum en ligne pour �tre r�cup�r� par l'attaquant et toutes 
les commandes natives seraient disponible pour le client.

Ressources utilis�es
*	La documentations de la librairie filesystem, ShellExecuteEX ainsi que celle des 
autres fonctions, librairies et classes utilis�es.
*	https://stackoverflow.com/questions/318236/how-do-you-validate-that-a-string-
is-a-valid-ipv4-address-in-c
*	https://www.codeproject.com/Articles/1842/A-newbie-s-elementary-guide-to-
spawning-processes
*	https://stackoverflow.com/questions/48437377/cmd-commands-in-shellexecute
*	https://stackoverflow.com/questions/12402549/check-if-socket-is-connected-or-
not
*	https://stackoverflow.com/questions/1283721/disable-showing-console-window




































































































































































































PROJET DE CONCEPTION SUR LA COMMUNICATION R�SEAU 	1





PROJET DE CONCEPTION SUR LA COMMUNICATION R�SEAU 	1




