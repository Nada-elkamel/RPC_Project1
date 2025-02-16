1) Préparation de l'environnement:
   - Installation de rpcgen... sur Ubuntu
     
2) Création de fichier de définition de l’interface RPC

   
/* calcul.x : définition de l'interface RPC */
program CAL_BIN_PROG {
    version CAL_VERS_ONE {
        void CALNULL(void) = 0;
        long int PUISS(struct Param) = 1;
        long int DEC2BIN(int) = 2;
    } = 1;
} = 0x20000001;

struct Param {
    int base;
    int exposant;
};


3) Génération des fichiers nécessaires avec rpcgen
rpcgen -a calcul.x
4) Implémentation des fonctions du serveur(calcul_svc.c)


#include "calcul.h"
#include <stdio.h>
#include <math.h>

long int *puiss_1_svc(Param *argp, struct svc_req *rqstp) {
    static long int result;
    result = pow(argp->base, argp->exposant);
    return &result;
}

long int *dec2bin_1_svc(int *n, struct svc_req *rqstp) {
    static long int result = 0;
    int num = *n, place = 1;
    while (num > 0) {
        result += (num % 2) * place;
        num /= 2;
        place *= 10;
    }
    return &result;
}


make -f Makefile.calcul => compiler le serveur (cette commande ne fonctionne plus)
./calcul_svc => démarrer le serveur
rpcinfo -p => vérifier s'il est bien enregistré

5) Implémentation du client (calcul_clnt.c)

#include "calcul.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
    CLIENT *clnt;
    long int *result;
    Param p;
    int num;

    if (argc != 3) {
        printf("Usage: %s base exposant\n", argv[0]);
        return 1;
    }

    p.base = atoi(argv[1]);
    p.exposant = atoi(argv[2]);

    clnt = clnt_create("localhost", CAL_BIN_PROG, CAL_VERS_ONE, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror("Erreur de connexion au serveur");
        return 1;
    }

    result = puiss_1(&p, clnt);
    if (result == NULL) {
        clnt_perror(clnt, "Appel distant échoué");
        return 1;
    }
    printf("Résultat de %d^%d = %ld\n", p.base, p.exposant, *result);

    clnt_destroy(clnt);
    return 0;
}

make -f Makefile.calcul => compiler le client
./calcul_clnt 2 3 => tester le client localement
./calcul_clnt <0x20000001> 2 3 => tester à distance 

