#include "Serveur.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	affichage("////// ** Console Serveur ** //////\n");
	Serveur* s = new Serveur(IPSERVEUR);
	int i = 0;

	do { s->accepterClient(i); i++; } while (true);

	getline(cin, *(new string())); // Appuyer sur Enter pour fermer la fenetre

	s->fermerServeur();
}