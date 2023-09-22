#include "Transferts.h"

Transfert::Transfert(SOCKET* s)
{
    this->socket = s;
}

void Transfert::envoyerMsg(string s)
{
    int erreur = send(*socket, s.c_str(), s.size(), 0);

    if (erreur == SOCKET_ERROR) {
        affichage(*new vector<string>{ "Erreur ",to_string(WSAGetLastError()), " lors de l'envoie." });
        closesocket(*socket);
        WSACleanup();
    }
}

void Transfert::envoyerListeDeFichiers(path path)
{
    vector<string> fichiers;

    for (const auto& entree : directory_iterator(path))
        fichiers.push_back(entree.path().filename().string());

    envoyerMsg(to_string(fichiers.size()));
    recevoirMsg(); // ACK

    for (string s : fichiers)
    {
        envoyerMsg(s.c_str());
        recevoirMsg(); // ACK
    }

    envoyerMsg("FIN");
    recevoirMsg(); // ACK

    affichage("Liste de fichiers envoye.");
}

bool Transfert::envoyerFichier(string fichier, path path)
{
    // Declaration
    string chemin = path.string() +"\\" + fichier;
    char* tampon = new char[recuInt];
    bool erreurBool = false;
    int taille = 0;
    int i = taille;

    // Setup
    ifstream fichierStream(chemin, ios::binary | ios::ate);
    if (fichierStream.fail())
        erreurBool = true;
    else
    {
        taille = (int)fichierStream.tellg();
        fichierStream.seekg(0, ios::beg);
        if (taille < 0)
            erreurBool = true;
        i = taille;
    }

    // Begin or Stop
    if (erreurBool) {
        envoyerMsg("ERREUR");
        recevoirMsg(); // ACK
        return false;
    }
    else {
        envoyerMsg("FICHIER");
        if(recevoirMsg() == "ERREUR") // ACK
            return false;
    }
    
    // Taille
    envoyerMsg(to_string(taille));
    recevoirMsg(); // ACK

    while (i != 0) {
        const int tailleStream = __min(i, 1024);
        if (!fichierStream.read(tampon, tailleStream)) { erreurBool = true; break; }
        const int l = envoyerFichierSupport(tampon, tailleStream);
        if (l < 0) { erreurBool = true; break; }
        i -= l;
    }
    delete[] tampon;

    fichierStream.close();

    envoyerMsg("FIN_FICHIER");
    recevoirMsg(); // ACK

    fichier += " Envoyer.";
    affichage(fichier);

    return !erreurBool;
}

int Transfert::envoyerFichierSupport(const char* tampon, int tailleTampon)
{
    int i = 0;
    while (i < tailleTampon) {
        const int l = send(*socket, &tampon[i], __min(1024, tailleTampon - i), 0);
        if (l < 0) { return l; }
        i += l;
    }

    return i;
}

string Transfert::recevoirMsg()
{
    char recu[recuInt];
    int erreur = recv(*socket, recu, recuInt, 0);

    if (erreur > 0) {}
    else if (erreur == 0)
        affichage("Fermeture de la connection.");
    else
    {
        affichage(*new vector<string>{ "Erreur ",to_string(WSAGetLastError()), " lors de la reception." });
    }

    string recuStr = recu;

    return recuStr.substr(0, erreur);
}

vector<string> Transfert::recevoirListeFichiers()
{
    vector<string> fichiers;

    int taille = stoi(recevoirMsg());
    envoyerMsg("ACK");

    for (int i = 0; i < taille; i++)
    {
        fichiers.push_back(recevoirMsg());
        envoyerMsg("ACK");
    }

    if (recevoirMsg() != "FIN")
        affichage("Erreur lors de la reception de la liste de fichiers.");

    envoyerMsg("ACK"); 

    affichage("Liste de fichiers recue.");

    return fichiers;
}

bool Transfert::recevoirFichier(string nom, path path)
{
    // Declaration
    string chemin = path.string() + "\\" + nom;
    char* tampon = new char[recuInt];
    bool erreurBool = false;
    string taille = "0";
    int i = stoi(taille);

    // Setup
    ofstream fichierStream(chemin, ios::binary | ios::trunc);
    if (fichierStream.fail())
        erreurBool = true;

    // Begin or Stop
    taille = recevoirMsg();
    if (taille == "ERREUR") {    // SI ERREUR SERVEUR
        envoyerMsg("ACK");
        return false;
    }   
    else {                      // SI PAS ERREUR SERVEUR   
        envoyerMsg("ACK");
        taille = recevoirMsg();
        try { i = stoi(taille); }
        catch(exception e){ erreurBool = true; } // SI MSG RECU != NOMBRE

        if (erreurBool) {               // SI ERREUR CLIENT
            envoyerMsg("ERREUR");
            return false;
        }
        else                            // SI PAS ERREUR CLIENT
            envoyerMsg("ACK");
    }

    while (i != 0) {
        const int r = recevoirFichierSupport(tampon, __min(i, 1024));
        if ((r < 0) || !fichierStream.write(tampon, r)) { erreurBool = true; break; }
        i -= r;
    }
    delete[] tampon;

    fichierStream.close();

    recevoirMsg(); 
    envoyerMsg("ACK");

    return !erreurBool;
}

int Transfert::recevoirFichierSupport(char* tampon, int tailleTampon)
{
    int i = 0;
    while (i < tailleTampon) {
        const int l = recv(*socket, &tampon[i], __min(1024, tailleTampon - i), 0);
        if (l < 0) { return l; }
        i += l;
    }
    return i;
}

bool Transfert::verifySocket()
{
    char error_code;
    int error_code_size = sizeof(error_code);
    getsockopt(*socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);

    if (error_code == 0)
        return true;
    else
        return false;
}
