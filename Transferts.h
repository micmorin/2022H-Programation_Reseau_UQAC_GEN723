#ifndef TRANSFERT
#define TRANSFERT

#include "Socket.h"
#include <fstream>
#include <filesystem>
#define recuInt 1024

using namespace filesystem;

class Transfert {
private:
	SOCKET* socket;

public:
	Transfert(SOCKET* s);

	void envoyerMsg(string s);
	void envoyerListeDeFichiers(path path);
	bool envoyerFichier(string fichier, path path);
	int  envoyerFichierSupport(const char* tampon, int tailleTampon);

	string recevoirMsg();
	vector<string> recevoirListeFichiers();
	bool recevoirFichier(string nom, path path);
	int  recevoirFichierSupport(char* tampon, int tailleTampon);

	bool verifySocket();
};
#endif