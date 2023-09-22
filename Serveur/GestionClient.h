#include "../Transferts.h"

void threadDeLaGestionDeClients(SOCKET* s);

class GestionClient {
protected:
	Transfert* t;
	path p;

public:
	GestionClient(SOCKET* s, path p);
	void execute();
	void gererFichiers();
};

