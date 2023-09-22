#include "Client.h"

int main(int argc, char* argv[])
{
	affichage("////// ** Console Client ** //////");

	Client* clients[CLIENTS];

	for (int i = 0; i < CLIENTS; i++)
	{
		affichage("\n------ ** Nouveau Client ** ------\n");
		clients[i] = new Client();
		if (clients[i]->connexion()) {
			affichage("\n...... ** Menu ** ......\n");
			clients[i]->commandes();
		}
		clients[i]->fermerConnection();
		affichage("\n------ ** Fin Client ** ------\n");
	}

	system("pause"); // Appuyer sur Enter pour fermer la fenetre
}