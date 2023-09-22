#include "GestionClient.h"

class Serveur : customSocket {
protected:
	SOCKET clients[CLIENTS];

public:
	Serveur(string ip);
	bool liaisonDuSocket();
	bool ecouteSurLeSocket();
	bool accepterClient(int i);
	bool fermerServeur();
};