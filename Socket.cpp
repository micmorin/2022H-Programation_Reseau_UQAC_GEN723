#include "Socket.h"

bool customSocket::initialisationWSA()
{
	erreur = WSAStartup(MAKEWORD(2, 2), &donneeDuSocket);
	if (erreur != 0) {
		affichage(*new vector<string>{"Erreur ", to_string(erreur), " lors de l'initialisation WSA."});
		return false;
	}

	ZeroMemory(&apercu, sizeof(apercu));
	apercu.ai_family = AF_UNSPEC;
	apercu.ai_socktype = SOCK_STREAM;
	apercu.ai_protocol = IPPROTO_TCP;

	return true;
}

bool customSocket::intialisationAddrInfo(string argv, const char* Port)
{
	erreur = getaddrinfo(argv.c_str(), Port, &apercu, &resultat);
	if (erreur != 0) {
		affichage(*new vector<string>{ "Erreur ", to_string(erreur), " lors de la lecture de l'addresse." });
		WSACleanup();
		return false;
	}

	return true;
}

bool customSocket::connecterLeSocket()
{
	socketDeConnexion = WSASocket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol,NULL, NULL, NULL);

	if (socketDeConnexion == INVALID_SOCKET) {
		string sortie = "Erreur "; sortie += to_string(erreur); sortie += " lors de la connexion du socket.";
		affichage(*new vector<string>{ "Erreur ", to_string(erreur), " lors de la connexion du socket." });
		freeaddrinfo(resultat);
		WSACleanup();
		return false;
	}

	return true;
}