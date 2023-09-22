#include "../Transferts.h"

class Client : customSocket {
protected:
	Transfert* t;
	vector<string> fichiers;

public:
	Client();
	bool connexion();
	string  commandes();
	bool gestionDeFichier();
	bool fermerConnection();

protected:
	bool menuGestionFichier();
	string serveurIP();
	void afficherCommande(string in);
	void afficherFichiers();

};