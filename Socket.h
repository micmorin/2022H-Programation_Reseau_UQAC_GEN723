#ifndef WIN32_SOCKET
#define WIN32_SOCKET

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <mutex>
#include <string>
#include <iostream>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define PORT "3210"
#define CLIENTS 1
#define IPSERVEUR "127.0.0.1"

using namespace std; 

class customSocket {
protected:
	WSADATA donneeDuSocket;
	struct addrinfo* resultat = NULL, apercu;
	int erreur;
	SOCKET socketDeConnexion = INVALID_SOCKET;

protected:
	bool initialisationWSA();
	bool intialisationAddrInfo(string argv, const char* Port);
	bool connecterLeSocket();
};

// *** Affichage Multi-Thread *** //

static mutex mutexCOUT;

static void affichage(string s)
{
	mutexCOUT.lock();
	cout << s << endl;
	mutexCOUT.unlock();
}

static void affichage(vector<string> s)
{
	mutexCOUT.lock();
	for(string i : s)
		cout << i;
	cout << endl;
	mutexCOUT.unlock();
}
#endif