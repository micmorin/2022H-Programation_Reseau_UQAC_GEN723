#include "GestionClient.h"

void threadDeLaGestionDeClients(SOCKET* s)
{
    GestionClient* g = new GestionClient(s,current_path());
    g->execute();
}

// *** Fonctions Publiques *** //

GestionClient::GestionClient(SOCKET* s, path p)
{
    this->t = new Transfert(s);
    this->p = p;
}

void GestionClient::execute()
{
    string in;
    bool b;
    do {
        in = "";
        t->envoyerMsg(p.string());
        in = t->recevoirMsg(); // CMD
        b = t->verifySocket();
        if (b)
        {
            path pa;
            string cmd = in.substr(0, in.find_first_of(' '));
            for_each(cmd.begin(), cmd.end(), [](char& c) {
                c = ::toupper(c);
                });
            string arg = in.substr(in.find_first_of(' ')+1);
            ofstream f("out.txt", ios_base::trunc);

            if (cmd == "CLOSE");
            else if (cmd == "CD") {
                try
                {
                    pa = p / arg;
                    pa = canonical(pa); 
                    p = pa;
                }
                catch (exception& ex)
                {
                    f << ex.what();
                }
            }
            else if (cmd == "FILE_TO_SERVER") {
                try {
                    path wdest = weakly_canonical(p / arg.substr(arg.find_first_of(' ') + 1));
                    path dest = canonical(wdest.parent_path());
                    if (wdest.has_filename())
                    {
                        t->envoyerMsg("ACK");
                        t->recevoirFichier(wdest.filename().string(), dest);
                    }
                    else {
                        f << "La source n'a pas de nom de fichier";
                        t->envoyerMsg("ERREUR");
                        t->recevoirMsg(); // ACK
                    }
                }
                catch (exception e) {
                    f << e.what();
                    t->envoyerMsg("ERREUR");
                    t->recevoirMsg(); // ACK
                }
            }
            else if (cmd == "FILE_TO_CLIENT") {
                try {
                    path src = canonical(arg.substr(0, arg.find_first_of(' ')));
                    if (src.has_filename())
                    {
                        t->envoyerMsg("ACK");
                        t->envoyerFichier(src.filename().string(), src.parent_path());
                    }
                    else {
                        f << "La source n'a pas de nom de fichier";
                        t->envoyerMsg("ERREUR");
                        t->recevoirMsg(); // ACK
                    }
                }
                catch (exception e) {
                    f << e.what();
                    t->envoyerMsg("ERREUR");
                    t->recevoirMsg(); // ACK
                }
            }
            else {
                string cmd = "/C cd " + p.string()  + " && " + in + " > out.txt";
                f.close();
                SHELLEXECUTEINFOA ShExecInfo = { 0 };
                ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
                ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                ShExecInfo.hwnd = NULL;
                ShExecInfo.lpVerb = "open";
                ShExecInfo.lpFile = "cmd.exe";
                ShExecInfo.lpParameters = cmd.c_str();
                ShExecInfo.lpDirectory = NULL;
                ShExecInfo.nShow = CREATE_NO_WINDOW;
                ShExecInfo.hInstApp = NULL;

                ShellExecuteExA(&ShExecInfo);
                WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
            }
  
            t->envoyerFichier("out.txt", p);
            t->recevoirMsg(); // ACK
            f.close();
            remove(current_path() / "out.txt");
            remove(p / "out.txt");
        }
    } while (in != "CLOSE" && b);
}

void GestionClient::gererFichiers()
{
    bool fin = false;
    string cmd;
    do {
        t->envoyerListeDeFichiers(p);
        cmd = t->recevoirMsg();
        if (cmd == "FIN")
            fin = true;
        else if (cmd == "LIST");
        else
            if (!t->envoyerFichier(cmd,p))
                t->envoyerMsg("ERREUR");

    } while (!fin);
}
