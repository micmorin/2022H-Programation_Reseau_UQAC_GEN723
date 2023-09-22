#include "Serveur.h"

Serveur::Serveur(string ip)
{
    for (int i = 0; i < CLIENTS; i++) { clients[i] = INVALID_SOCKET; }
    if (initialisationWSA()) { affichage("Intitialisation WSA reussi."); };
    if (intialisationAddrInfo(ip, PORT)) { affichage("Intitialisation AddrInfo reussi."); };
    if (connecterLeSocket()) { affichage("Connection du Socket reussi."); };
    if (liaisonDuSocket()) { affichage("Liaison du Socket reussi."); };
    freeaddrinfo(resultat);
    if (ecouteSurLeSocket()) { affichage("Intitialisation de l'Ecoute reussi."); };
}

bool Serveur::liaisonDuSocket()
{
    erreur = bind(socketDeConnexion, resultat->ai_addr, (int)resultat->ai_addrlen);
    if (erreur == SOCKET_ERROR) {
        affichage(*new vector<string>{ "Erreur ", to_string(erreur), " lors de la liaison du socket." });
        freeaddrinfo(resultat);
        closesocket(socketDeConnexion);
        WSACleanup();
        return false;
    }
    return true;
}

bool Serveur::ecouteSurLeSocket()
{
    erreur = listen(socketDeConnexion, SOMAXCONN);
    if (erreur == SOCKET_ERROR) {
        affichage(*new vector<string>{ "Erreur ", to_string(erreur), " lors de l'ecoute du socket." });
        closesocket(socketDeConnexion);
        WSACleanup();
        return false;
    }
    return true;
}

bool Serveur::accepterClient(int i)
{
    this->clients[i] = accept(socketDeConnexion, NULL, NULL);
    if (this->clients[i] == INVALID_SOCKET) {
        affichage(*new vector<string>{ "Erreur ", to_string(erreur), " lors de l'acceptation du client." });
        closesocket(socketDeConnexion);
        WSACleanup();
        return false;
    }
    new thread(threadDeLaGestionDeClients, &this->clients[i]);
    affichage("- Demande de connection Client recu.");
    return true;
}


bool Serveur::fermerServeur()
{
    closesocket(socketDeConnexion);
    for (int i = 0; i < CLIENTS; i++) { closesocket(clients[i]); }
    WSACleanup();

    affichage("Fermeture du Serveur reussi.");
    return true;
}
